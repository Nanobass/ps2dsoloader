#include <dso-loader.h>
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
void* dl_resolve(struct module_t* module, uint32_t dynsym_index) {
    struct dso_context_t* ctx = get_dso_context(module);
    Elf32_Sym* symbol = &ctx->dynsym[dynsym_index];
    if(symbol->st_name == STN_UNDEF) {
        printf("undefined symbol: %ld\n", dynsym_index);
        abort();
    }
    const char* name = &ctx->dynstr[symbol->st_name];
    struct symbol_t* resolved = dl_find_global_symbol(name);
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
static void dl_resolve_stub()
{
    asm volatile (
        "addiu   $sp,$sp,-32\n"
        "sd      $a0,24($sp)\n"
        "sd      $a1,16($sp)\n"
        "sd      $t3,8($sp)\n"
        "sd      $v0,0($sp)\n"
        "move    $a1, $t8\n"
        "lw      $a0, -32748($gp)\n"
        "jal     dl_resolve\n"
        "move    $t3,$v0\n"
        "ld      $a0,24($sp)\n"
        "ld      $a1,16($sp)\n"
        "ld      $ra,8($sp)\n"
        "ld      $v0,0($sp)\n"
        "addiu   $sp,$sp,32\n"
        "jr      $t3\n"
    );
}

struct module_t* dl_load_module(FILE* file) {
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

    dso_allocate_module(ctx, sizeof(struct dso_context_t));
    dso_read_module_sections(ctx);

    struct dso_context_t* dso_ctx = get_dso_context(ctx->module);

    Elf32_Section dynamic_index = 0, dynsym_index = 0, dynstr_index = 0;

    if(dso_find_section_by_type(ctx, &dynamic_index, SHT_DYNAMIC) < 0) {
        dso_error(ctx, "failed to find dynamic section");
    } else {
        printf("dynamic section found at offset 0x%08lX\n", ctx->shdr[dynamic_index].sh_offset);
    }

    if(dso_find_section_by_type(ctx, &dynsym_index, SHT_DYNSYM) < 0) {
        dso_error(ctx, "failed to find dynamic symbol section");
    } else {
        printf("dynamic symbol table found at offset 0x%08lX\n", ctx->shdr[dynsym_index].sh_offset);
        dso_ctx->dynsym = (Elf32_Sym*) ctx->shdr[dynsym_index].sh_addr;
        dso_ctx->dynsym_count = ctx->shdr[dynsym_index].sh_size / sizeof(Elf32_Sym);
    }

    if(!(dynstr_index = ctx->shdr[dynsym_index].sh_link)) {
       dso_error(ctx, "failed to find dynamic string table");
    } else {
        printf("dynamic string table found at offset 0x%08lX\n", ctx->shdr[dynstr_index].sh_offset);
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
            case DT_SONAME:
                ctx->module->name = &dso_ctx->dynstr[dyn->d_un.d_val];
                break;
            case DT_NEEDED:
                ctx->module->dependencies[needed_index++] = &dso_ctx->dynstr[dyn->d_un.d_val];
                break;
            case DT_MIPS_LOCAL_GOTNO:
                dso_ctx->local_got_count = dyn->d_un.d_val;
                break;
            case DT_MIPS_GOTSYM:
                dso_ctx->gotsym = dyn->d_un.d_val;
                break;
            case DT_PLTGOT:
                dso_ctx->got_base = (uintptr_t*) (ctx->module->base + dyn->d_un.d_val);
                printf("PLTGOT found at 0x%08lX\n", (unsigned long) ctx->module->base);
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

    printf("dso context: %p\n", dso_ctx->got_base);

    printf("global offset table\n");
    printf("local entries\n");
    printf("#####: value\n");
    for (size_t i = 0; i < dso_ctx->local_got_count; i++) {
        printf("%05zu: 0x%08lX\n", i, (unsigned long) dso_ctx->got_base[i]);
    }
    printf("global entries\n");
    printf("#####: value      symbol\n");
    for (size_t i = dso_ctx->local_got_count; i < dso_ctx->got_count; i++) {

        Elf32_Sym* sym = &((Elf32_Sym*) ctx->shdr[dynsym_index].sh_addr)[i];
        const char* name;
        if(sym->st_name != STN_UNDEF) {
            name = &dso_ctx->dynstr[sym->st_name];
        } else {
            name = "<unnamed>";
        }

        printf("%5u: 0x%08lX %s\n", i, (unsigned long) dso_ctx->got_base[i], name);
    }

    printf("relocating local entries\n");
    printf("#####: value        relocated\n");
    for (size_t i = 0; i < dso_ctx->local_got_count; i++) {
        uintptr_t relocated = (uintptr_t) ctx->module->base + dso_ctx->got_base[i];
        printf("%5zu: 0x%08lX -> 0x%08lX\n", i, (unsigned long) dso_ctx->got_base[i], (unsigned long) relocated);
        dso_ctx->got_base[i] = relocated;
    }

    printf("relocating global entries\n");
    printf("#####: value        relocated\n");
    for (size_t i = dso_ctx->local_got_count; i < dso_ctx->got_count; i++) {
        uintptr_t relocated = (uintptr_t) ctx->module->base + dso_ctx->got_base[i];
        printf("%5zu: 0x%08lX -> 0x%08lX\n", i, (unsigned long) dso_ctx->got_base[i], (unsigned long) relocated);
        dso_ctx->got_base[i] = relocated;
    }

    // install lazy resolver and module pointer

    dso_ctx->got_base[0] = (uintptr_t) dl_resolve_stub;
    dso_ctx->got_base[1] = (uintptr_t) ctx->module; // module pointer (GNU extension)

    // find and relocate sections

    printf("finding relocatable sections\n");
    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        const char* name;

        if(section->sh_name != SHN_UNDEF) {
            name = &ctx->shstrtab[section->sh_name];
        } else {
            name = "<unnamed>";
        }

        if(section->sh_type != SHT_REL) {
            continue;
        }

        printf("section %02d (%s) at 0x%08lX: contains relocations for section %li\n", i, name, (unsigned long) section->sh_addr, section->sh_info);

        if(section->sh_entsize != sizeof(Elf32_Rel)) {
            printf("invalid relocation entry size for section %s\n", name);
            dso_error(ctx, "invalid relocation entry size");
            return NULL;
        }

        Elf32_Rel* reloc_data = (Elf32_Rel*) (section->sh_addr);

        printf("reloc_data: 0x%08lX\n", (unsigned long) reloc_data);

        Elf32_Shdr* reloc_section = &ctx->shdr[section->sh_info];

        printf("######: offset   type           symbol\n");
        for(size_t j = 0; j < section->sh_size / sizeof(Elf32_Rel); j++) {
            Elf32_Rel* reloc = &reloc_data[j];

            if(ELF32_R_TYPE(reloc->r_info) == R_MIPS_NONE) {
                continue;
            }

            printf("%6zu: %08lX %-14s %03lu: ", j, reloc->r_offset, reloc_types[ELF32_R_TYPE(reloc->r_info)], ELF32_R_SYM(reloc->r_info));

            if(ELF32_R_TYPE(reloc->r_info) != R_MIPS_REL32) {
                printf("shared object should only contain R_MIPS_REL32 relocations\n");
                dso_error(ctx, "unknown relocation type");
            }

            uintptr_t* reloc_target = (uintptr_t*) (reloc_section->sh_addr + reloc->r_offset);
            uintptr_t relocated;

            // A - EA + S
            if(ELF32_R_SYM(reloc->r_info) < dso_ctx->gotsym) {
                // local symbol
                // TODO: check this
                relocated = (uintptr_t) ctx->module->base + *reloc_target;
            } else {
                // global symbol
                // TODO: check this
                relocated = (uintptr_t) ctx->module->base + 
                    dso_ctx->got_base[dso_ctx->local_got_count + ELF32_R_SYM(reloc->r_info) - dso_ctx->gotsym] + 
                    *reloc_target;
            }

            printf("relocating 0x%08lX -> 0x%08lX\n", (unsigned long) *reloc_target, (unsigned long) relocated);

            *reloc_target = relocated;

        }        

    }

    // everything is loaded, destroy the load context

    struct module_t* module = dso_destroy_load_context(ctx);

    // count 'exported' symbols

    size_t symbol_count = 0;
    uint32_t symbol_index = 0;
    for(size_t i = 0; i < dso_ctx->dynsym_count; i++) {
        Elf32_Sym* sym = &dso_ctx->dynsym[i];
        if(
            sym->st_shndx != SHN_UNDEF && 
            sym->st_name != STN_UNDEF && 
            (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT || ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
        ) symbol_count++;
    }

    module->symbol_count = symbol_count;
    module->symbols = (struct symbol_t*) malloc(symbol_count * sizeof(struct symbol_t));
    if (!module->symbols) {
        dl_free_module(module);
        dl_raise("out of memory for module symbols");
        return NULL;
    }

    // print symbols and copy 'exported' symbols

    printf("module symbols\n");
    printf("######: size     address  type           bind        index name\n");
    for(size_t i = 0; i < dso_ctx->dynsym_count; i++) {
        Elf32_Sym* sym = &dso_ctx->dynsym[i];
        char* name;

        if(sym->st_name != STN_UNDEF) {
            name = &dso_ctx->dynstr[sym->st_name];
        } else {
            name = "<unnamed>";
        }

        sym->st_value = (uintptr_t) module->base + (uintptr_t) sym->st_value;

        if(
            sym->st_shndx != SHN_UNDEF && 
            sym->st_name != STN_UNDEF && 
            (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT || ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
        ) {
            struct symbol_t* symbol = &module->symbols[symbol_index++];
            symbol->name = name;
            symbol->address = (void*) sym->st_value;
            symbol->info = sym->st_info;
        }

        printf("%6zu: %08lX %08lX %-14s %-10s %6u %s\n", i, sym->st_size, sym->st_value,
                symbol_types[ELF32_ST_TYPE(sym->st_info) > STT_LOPROC ? STT_LOPROC : ELF32_ST_TYPE(sym->st_info)],
                binding_types[ELF32_ST_BIND(sym->st_info) > STB_LOPROC ? STB_LOPROC : ELF32_ST_BIND(sym->st_info)],
                sym->st_shndx, name);
    }

    // new code, new cache

    FlushCache(2);
    FlushCache(0);

    // print module name and dependencies

    printf("module name: %s\n", module->name);
    for(size_t i = 0; module->dependencies[i]; i++) {
        printf("  dependency: %s\n", module->dependencies[i]);
    }

    return module;
}

void dl_resolve_module(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return;
    }

    for(size_t i = 0; i < get_dso_context(module)->dynsym_count; i++) {
        Elf32_Sym* sym = &get_dso_context(module)->dynsym[i];
        if(sym->st_shndx != SHN_UNDEF) continue;
        if(sym->st_name == STN_UNDEF) continue;
        dl_resolve(module, i);
    }
}