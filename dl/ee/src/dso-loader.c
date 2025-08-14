#include <dso-loader.h>

#include <dl.h>
#include <dso.h>
#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

#include <kernel.h>

/**
 * DSO context structure
 */
struct dso_context_t {
    size_t dynsym_count;
    Elf32_Sym* dynsym;
    char* dynstr;

    uintptr_t* got_base;
    uint32_t got_count;
    uint32_t local_got_count;
    uint32_t gotsym;

    uintptr_t* init_array;
    uint32_t init_count;
    uintptr_t* fini_array;
    uint32_t fini_count;

};

/**
 * get the DSO context from a module
 * @param module the module to get the context from
 * @return a pointer to the DSO context
 */
#define get_dso_context(module) ((struct dso_context_t*) module->extra)

/**
 * resolve a symbol in the module's symbol table
 * @param module the module containing the symbol
 * @param dynsym_index the index of the symbol in the dynamic symbol table
 * @return a pointer to the symbol's address, or NULL if not found
 * used by the lazy linker
 */
void* dso_loader_resolve(struct module_t* module, uint32_t dynsym_index) {
    struct dso_context_t* ctx = get_dso_context(module);
    Elf32_Sym* symbol = &ctx->dynsym[dynsym_index];
    const char* name = &ctx->dynstr[symbol->st_name];
    struct symbol_t* resolved = NULL;

    for(char** dependency = module->dependencies; *dependency; dependency++) {
        struct module_t* dep_module = dl_get_module(*dependency);
        if(dep_module) {
            resolved = dl_module_find_symbol(dep_module, name);
            if(resolved) {
                dl_add_dependency(module, dep_module);
                break;
            }
        }
    }

    if(!resolved) {
        resolved = dl_find_global_symbol(name);
        dl_add_dependency(module, NULL);
    }
    if(!resolved) {
        printf("failed to resolve symbol: %s\n", name);
        abort();
    }
    uint32_t got_index = ctx->local_got_count + (dynsym_index - ctx->gotsym);
    ctx->got_base[got_index] = (uintptr_t) resolved->address;
    printf("resolved symbol: %s at %p into got entry %ld\n", name, resolved->address, got_index);
    return resolved->address;
}

/**
 * lazy resolver stub stored in the global offset table
 * @note do not call!
 */
static void resolve_stub()
{
    asm volatile (
        "addiu   $sp,$sp,-32\n"
        "sd      $a0,24($sp)\n"
        "sd      $a1,16($sp)\n"
        "sd      $t3,8($sp)\n"
        "sd      $v0,0($sp)\n"
        "move    $a1, $t8\n"
        "lw      $a0, -32748($gp)\n"
        "jal     dso_loader_resolve\n"
        "move    $t3,$v0\n"
        "ld      $a0,24($sp)\n"
        "ld      $a1,16($sp)\n"
        "ld      $ra,8($sp)\n"
        "ld      $v0,0($sp)\n"
        "addiu   $sp,$sp,32\n"
        "jr      $t3\n"
    );
}

static void init(struct module_t* module) {
    struct dso_context_t* dso_ctx = get_dso_context(module);
    for(uint32_t i = 0; i < dso_ctx->init_count; i++) {
        uintptr_t init_func = dso_ctx->init_array[i];
        if(init_func) {
            ((void (*)(void))init_func)();
        }
    }
}

static void fini(struct module_t* module) {
    struct dso_context_t* dso_ctx = get_dso_context(module);
    for(uint32_t i = 0; i < dso_ctx->fini_count; i++) {
        uintptr_t fini_func = dso_ctx->fini_array[i];
        if(fini_func) {
            ((void (*)(void))fini_func)();
        }
    }
}

struct module_t* dl_load_dso(FILE* file) {
    struct elf_load_context_t* ctx = dso_create_load_context(file);
    if (!ctx) {
        dl_raise("failed to create load context");
        return NULL;
    }
    
    int rv = setjmp(ctx->error);
    if(rv) {
        dl_raise((const char*) rv);
        struct module_t* module = dso_destroy_load_context(ctx);
        if(module) dl_free_module(module);
        return NULL;
    }

    dso_read_elf_header(ctx, ET_DYN);
    
    dso_read_program_headers(ctx);
    dso_print_program_headers(ctx);

    dso_read_section_headers(ctx);
    dso_print_section_headers(ctx);

    dso_allocate_module(ctx, sizeof(struct dso_context_t), DL_MT_DSO);
    dso_read_module_sections(ctx);

    struct dso_context_t* dso_ctx = get_dso_context(ctx->module);

    Elf32_Section dynamic_index = 0, dynsym_index = 0, dynstr_index = 0;

    if(dso_find_section_by_type(ctx, &dynamic_index, SHT_DYNAMIC) < 0) {
        dso_error(ctx, "failed to find dynamic section");
    }

    if(dso_find_section_by_type(ctx, &dynsym_index, SHT_DYNSYM) < 0) {
        dso_error(ctx, "failed to find dynamic symbol section");
    } else {
        dso_ctx->dynsym = (Elf32_Sym*) ctx->shdr[dynsym_index].sh_addr;
        dso_ctx->dynsym_count = ctx->shdr[dynsym_index].sh_size / sizeof(Elf32_Sym);
    }

    if(!(dynstr_index = ctx->shdr[dynsym_index].sh_link)) {
       dso_error(ctx, "failed to find dynamic string table");
    } else {
        dso_ctx->dynstr = (char*) ctx->shdr[dynstr_index].sh_addr;
    }

    dso_print_dynamic_tags(ctx);

    uint32_t needed_index = 0;     
    size_t needed_count = dso_count_dynamic_tags(ctx, DT_NEEDED);

    ctx->module->dependencies = (char**) malloc((needed_count + 1) * sizeof(char*));
    if(!ctx->module->dependencies) {
        dso_error(ctx, "failed to allocate memory for dependencies");
    }
    ctx->module->dependencies[needed_count] = NULL;

    Elf32_Dyn* dyn = (Elf32_Dyn*)ctx->shdr[dynamic_index].sh_addr;
    for(; dyn->d_tag != DT_NULL; dyn++) {
        switch(dyn->d_tag) {
            case DT_SONAME: {
                char* soname = &dso_ctx->dynstr[dyn->d_un.d_val];
                char* slash = strchr(soname, '/');
                if (!slash) {
                    ctx->module->name = soname;
                } else {
                    // Count segments
                    needed_count++;
                    for (char* p = slash + 1; *p; p++) {
                        if (*p == '/') needed_count++;
                    }
                    // Free previous dependencies
                    if (ctx->module->dependencies) free(ctx->module->dependencies);
                    ctx->module->dependencies = (char**)malloc((needed_count + 1) * sizeof(char*));
                    if (!ctx->module->dependencies) {
                        dso_error(ctx, "failed to allocate memory for dependencies");
                    }
                    ctx->module->dependencies[needed_count] = NULL;
                    char* p = soname;
                    ctx->module->name = p;
                    int idx = 0;
                    while ((slash = strchr(p, '/'))) {
                        *slash = '\0';
                        p = slash + 1;
                        ctx->module->dependencies[idx++] = p;
                    }
                }
                break;
            }
            case DT_NEEDED:
                ctx->module->dependencies[needed_index++] = &dso_ctx->dynstr[dyn->d_un.d_val];
                break;
            case DT_INIT_ARRAY:
                dso_ctx->init_array = (uintptr_t*) (ctx->module->base + dyn->d_un.d_val);
                break;
            case DT_INIT_ARRAYSZ:
                dso_ctx->init_count = dyn->d_un.d_val / sizeof(uintptr_t);
                break;
            case DT_FINI_ARRAY:
                dso_ctx->fini_array = (uintptr_t*) (ctx->module->base + dyn->d_un.d_val);
                break;
            case DT_FINI_ARRAYSZ:
                dso_ctx->fini_count = dyn->d_un.d_val / sizeof(uintptr_t);
                break;
            case DT_MIPS_LOCAL_GOTNO:
                dso_ctx->local_got_count = dyn->d_un.d_val;
                break;
            case DT_MIPS_GOTSYM:
                dso_ctx->gotsym = dyn->d_un.d_val;
                break;
            case DT_PLTGOT:
                dso_ctx->got_base = (uintptr_t*) (ctx->module->base + dyn->d_un.d_val);
                break;
            case DT_MIPS_BASE_ADDRESS:
                // TODO: implement base address relocation
                if(dyn->d_un.d_val != 0) {
                    dso_error(ctx, "base address is not zero");
                }
                break;
        }   
    }

    if(!dso_ctx->got_base) {
        dso_error(ctx, "no global offset table found");
    }
    
    dso_ctx->got_count = dso_ctx->local_got_count + dso_ctx->dynsym_count - dso_ctx->gotsym;

    // relocate global offset table
    printf("global offset table\n");
    printf("relocating local entries\n");
    printf("#####: value       relocated\n");
    for (size_t i = 0; i < dso_ctx->local_got_count; i++) {
        uintptr_t relocated = (uintptr_t) ctx->module->base + dso_ctx->got_base[i];
        printf("%5zu: %08lX -> %08lX\n", i, (unsigned long) dso_ctx->got_base[i], (unsigned long) relocated);
        dso_ctx->got_base[i] = relocated;
    }

    printf("relocating global entries\n");
    printf("#####: value       relocated symbol\n");
    for (size_t i = dso_ctx->local_got_count; i < dso_ctx->got_count; i++) {
        Elf32_Sym* sym = &dso_ctx->dynsym[i - dso_ctx->local_got_count + dso_ctx->gotsym];
        const char* name = dso_symbol_name(ctx, dso_ctx->dynstr, sym);
        uintptr_t relocated = (uintptr_t) ctx->module->base + dso_ctx->got_base[i];
        printf("%5zu: %08lX -> %08lX  %s\n", i, (unsigned long) dso_ctx->got_base[i], (unsigned long) relocated, name);
        dso_ctx->got_base[i] = relocated;
    }

    // install lazy resolver and module pointer

    dso_ctx->got_base[0] = (uintptr_t) resolve_stub;
    dso_ctx->got_base[1] = (uintptr_t) ctx->module; // module pointer (GNU extension)

    // find and relocate sections

    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        const char* name = dso_section_name(ctx, i);

        if(section->sh_type != SHT_REL) continue;

        printf("section %d (%s) at %p: contains relocations\n", i, name, (void*) section->sh_addr);

        if(section->sh_entsize != sizeof(Elf32_Rel)) {
            printf("invalid relocation entry size for section %s\n", name);
            dso_error(ctx, "invalid relocation entry size");
            return NULL;
        }

        printf("######: offset   type          symbol                value         relocated\n");
        for(size_t j = 0; j < section->sh_size / sizeof(Elf32_Rel); j++) {
            Elf32_Rel* reloc = &((Elf32_Rel*)section->sh_addr)[j];
            if(ELF32_R_TYPE(reloc->r_info) == R_MIPS_NONE) continue;
            Elf32_Sym* symbol = &dso_ctx->dynsym[ELF32_R_SYM(reloc->r_info)];
            const char* name = dso_symbol_name(ctx, dso_ctx->dynstr, symbol);

            printf("%6zu: %08lX %-14s %-20s ", j, reloc->r_offset, reloc_types[ELF32_R_TYPE(reloc->r_info)], name);

            if(ELF32_R_TYPE(reloc->r_info) != R_MIPS_REL32) {
                printf("shared object should only contain R_MIPS_REL32 relocations\n");
                dso_error(ctx, "unknown relocation type");
            }
            
            // A - EA + S
            if(ELF32_R_SYM(reloc->r_info) < dso_ctx->gotsym) {
                uintptr_t* target = (uintptr_t*) (ctx->module->base + reloc->r_offset);
                // TODO: figure out proper A - EA here
                uintptr_t relocated = (uintptr_t) ctx->module->base + *target;
                printf("0x%08lX -> 0x%08lX\n", (unsigned long) *target, (unsigned long) relocated);
                *target = relocated;
            } else {
                uintptr_t* target = (uintptr_t*) (ctx->module->base + reloc->r_offset);
                uintptr_t relocated = dso_ctx->got_base[dso_ctx->local_got_count + ELF32_R_SYM(reloc->r_info) - dso_ctx->gotsym] - symbol->st_value + *target;
                printf("0x%08lX -> 0x%08lX\n", (unsigned long) *target, (unsigned long) relocated);
                *target = relocated;
            }

        }        

    }

    // everything is loaded, destroy the load context

    struct module_t* module = dso_destroy_load_context(ctx);

    // count 'exported' symbols

    size_t symbol_count = 0;
    uint32_t symbol_index = 0;
    for(size_t i = 0; i < dso_ctx->dynsym_count; i++) {
        Elf32_Sym* sym = &dso_ctx->dynsym[i];
        if(sym->st_shndx) symbol_count++;
    }

    module->symbol_count = symbol_count;
    module->symbols = (struct symbol_t*) malloc(symbol_count * sizeof(struct symbol_t));
    if (!module->symbols) {
        dl_free_module(module);
        dl_raise("out of memory for module symbols");
        return NULL;
    }

    // install init & fini

    module->init = init;
    module->fini = fini;

    // copy 'exported' symbols

    for(size_t i = 1; i < dso_ctx->dynsym_count; i++) {
        Elf32_Sym* sym = &dso_ctx->dynsym[i];
        char* name = (char*) dso_symbol_name(ctx, dso_ctx->dynstr, sym);

        sym->st_value = (uintptr_t) module->base + (uintptr_t) sym->st_value;

        if(sym->st_shndx) {
            struct symbol_t* symbol = &module->symbols[symbol_index++];
            symbol->name = name;
            symbol->address = (void*) sym->st_value;
            symbol->info = sym->st_info | SI_CCHAR_NAME;
        }
    }

    dso_print_symbol_table(ctx, dso_ctx->dynsym, dso_ctx->dynsym_count, dso_ctx->dynstr);

    printf("module name: %s\n", module->name);
    for(char** dependency = module->dependencies; *dependency; dependency++) {
        printf("  dependency: %s\n", *dependency);
    }

    // request dependencies

    for(char** dependency = module->dependencies; *dependency; dependency++) {
        struct module_t* dep_module = dl_get_module(*dependency);
        if(!dep_module) dep_module = dl_load_module(*dependency);
        if(dep_module) {
            dl_add_dependency(module, dep_module);
        } else {
            dl_raise("failed to load dependency");
            return NULL;
        }
    }

    // resolve non-function symbols

    for(size_t i = 1; i < get_dso_context(module)->dynsym_count; i++) {
        Elf32_Sym* sym = &get_dso_context(module)->dynsym[i];
        if(sym->st_shndx != SHN_UNDEF) continue;
        if(ELF32_ST_TYPE(sym->st_info) == STT_FUNC) continue;
        dso_loader_resolve(module, i);
    }

    // new code, new cache

    FlushCache(2);
    FlushCache(0);

    return module;
}

void dl_resolve_dso(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return;
    }

    for(size_t i = 1; i < get_dso_context(module)->dynsym_count; i++) {
        Elf32_Sym* sym = &get_dso_context(module)->dynsym[i];
        if(sym->st_shndx) continue;
        dso_loader_resolve(module, i);
    }
}