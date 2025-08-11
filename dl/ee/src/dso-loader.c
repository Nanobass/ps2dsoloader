#include <dso-loader.h>
#include <dso.h>

#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

#include <kernel.h>

/**
 * resolve a symbol in the module's symbol table
 * @param module the module containing the symbol
 * @param dynsym_index the index of the symbol in the dynamic symbol table
 * @return a pointer to the symbol's address, or NULL if not found
 * used by the lazy linker
 */
void* dl_resolve(struct module_t* module, uint32_t dynsym_index) {
    Elf32_Sym* symbol = &module->dso_context.dynsym[dynsym_index];
    if(symbol->st_name == STN_UNDEF) {
        printf("undefined symbol: %ld\n", dynsym_index);
        abort();
    }
    const char* name = &module->dso_context.dynstr[symbol->st_name];
    struct symbol_t* resolved = dl_find_global_symbol(name);
    const char* error = dlerror();
    if(!resolved || error) {
        printf("failed to resolve symbol: %s", name);
        if(error) {
            printf(", reason: %s", error);
        }
        printf("\n");
        abort();
    }
    uint32_t got_index = module->dso_context.local_gotno + (dynsym_index - module->dso_context.gotsym);
    uintptr_t* got_base = (uintptr_t*) (module->base + module->dso_context.pltgot);
    got_base[got_index] = (uintptr_t) resolved->address;
    printf("resolved symbol: %s at %p into got entry %ld\n", name, resolved->address, got_index);
    return resolved->address;
}

/**
 * lazy resolver stub stored in the global offset table
 * @note do not call!
 */
void dl_resolve_stub()
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

    dso_allocate_module(ctx);
    dso_read_module_sections(ctx);

    Elf32_Section dynamic_index = 0, dynsym_index = 0, dynstr_index = 0;

    if(dso_find_section_by_type(ctx, &dynamic_index, SHT_DYNAMIC) < 0) {
        dso_error(ctx, "failed to find dynamic section");
    } else {
        printf("dynamic table found at offset 0x%08lX\n", ctx->shdr[dynamic_index].sh_offset);
        ctx->module->dso_context.dynamic = (Elf32_Dyn*) ctx->shdr[dynamic_index].sh_addr;
        ctx->module->dso_context.dynamic_count = ctx->shdr[dynamic_index].sh_size / sizeof(Elf32_Dyn);
    }

    if(dso_find_section_by_type(ctx, &dynsym_index, SHT_DYNSYM) < 0) {
        dso_error(ctx, "failed to find dynamic symbol section");
    } else {
        printf("dynamic symbol table found at offset 0x%08lX\n", ctx->shdr[dynsym_index].sh_offset);
        ctx->module->dso_context.dynsym = (Elf32_Sym*) ctx->shdr[dynsym_index].sh_addr;
        ctx->module->dso_context.dynsym_count = ctx->shdr[dynsym_index].sh_size / sizeof(Elf32_Sym);
    }

    if(!(dynstr_index = ctx->shdr[dynsym_index].sh_link)) {
       dso_error(ctx, "failed to find dynamic string table");
    } else {
        printf("dynamic string table found at offset 0x%08lX\n", ctx->shdr[dynstr_index].sh_offset);
        ctx->module->dso_context.dynstr = (char*) ctx->shdr[dynstr_index].sh_addr;
    }

    size_t needed_count = 0;
    uint32_t needed_index = 0;

    needed_count = dso_count_dynamic_tags(ctx, DT_NEEDED);

    ctx->module->dependencies = (char**) malloc((needed_count + 1) * sizeof(char*));
    if(!ctx->module->dependencies) {
        dso_error(ctx, "failed to allocate memory for dependencies");
    }

    ctx->module->dependencies[needed_count] = NULL;

    for(size_t j = 0; j < ctx->module->dso_context.dynamic_count; j++) {
        Elf32_Dyn* dyn = &ctx->module->dso_context.dynamic[j];

        if(dyn->d_tag >= DT_MIPS_RLD_VERSION && dyn->d_tag <= DT_MIPS_RLD_MAP_REL) {
            printf("%3zu: %-28s 0x%08lX\n", j, mips_dynamic_tag_types[dyn->d_tag - DT_MIPS_RLD_VERSION], dyn->d_un.d_val);
        } else if(dyn->d_tag >= DT_NUM) {
            printf("%3zu: 0x%08lX                   0x%08lX\n", j, dyn->d_tag, dyn->d_un.d_val);
        } else {
            printf("%3zu: %-28s 0x%08lX\n", j, dynamic_tag_types[dyn->d_tag], dyn->d_un.d_val);
        }

        switch(dyn->d_tag) {
            case DT_SONAME:
                ctx->module->name = &ctx->module->dso_context.dynstr[dyn->d_un.d_val];
                break;
            case DT_NEEDED:
                ctx->module->dependencies[needed_index++] = &ctx->module->dso_context.dynstr[dyn->d_un.d_val];
                break;
            case DT_MIPS_RLD_VERSION:
                ctx->module->dso_context.rld_version = dyn->d_un.d_val;
                break;
            case DT_MIPS_FLAGS:
                ctx->module->dso_context.flags = dyn->d_un.d_val;
                break;
            case DT_MIPS_BASE_ADDRESS:
                ctx->module->dso_context.base_address = dyn->d_un.d_val;
                break;
            case DT_MIPS_LOCAL_GOTNO:
                ctx->module->dso_context.local_gotno = dyn->d_un.d_val;
                break;
            case DT_MIPS_SYMTABNO:
                ctx->module->dso_context.symtabno = dyn->d_un.d_val;
                break;
            case DT_MIPS_GOTSYM:
                ctx->module->dso_context.gotsym = dyn->d_un.d_val;
                break;
            case DT_MIPS_RLD_MAP:
                ctx->module->dso_context.rld_map = dyn->d_un.d_val;
                break;
            case DT_PLTGOT:
                ctx->module->dso_context.pltgot = dyn->d_un.d_val;
                break;
        }
    }

    // TODO: implement base address relocation

    if(ctx->module->dso_context.base_address != 0) {
        dso_error(ctx, "base address is not zero");
    }

    // relocate global offset table

    uint32_t got_local_count = ctx->module->dso_context.local_gotno;
    uintptr_t* got_local_base = (uintptr_t*) (ctx->module->base + ctx->module->dso_context.pltgot);
    uint32_t got_global_count = ctx->module->dso_context.dynsym_count - ctx->module->dso_context.gotsym;
    uintptr_t* got_global_base = got_local_base + got_local_count;

    printf("global offset table\n");
    printf("local entries\n");
    printf("#####: value\n");
    for (size_t i = 0; i < got_local_count; i++) {
        printf("%05zu: 0x%08lX\n", i, (unsigned long) got_local_base[i]);
    }
    printf("global entries\n");
    printf("#####: value      symbol\n");
    for (size_t i = 0; i < got_global_count; i++) {

        Elf32_Sym* sym = (Elf32_Sym*) ctx->shdr[dynsym_index].sh_addr + ctx->module->dso_context.gotsym + i;
        const char* name;
        if(sym->st_name != STN_UNDEF) {
            name = &ctx->module->dso_context.dynstr[sym->st_name];
        } else {
            name = "<unnamed>";
        }

        printf("%5lu: 0x%08lX %s\n", i + got_local_count, (unsigned long) got_global_base[i], name);
    }

    printf("relocating local entries\n");
    printf("#####: value        relocated\n");
    for (size_t i = 0; i < got_local_count; i++) {
        uintptr_t relocated = (uintptr_t) ctx->module->base + got_local_base[i];
        printf("%5zu: 0x%08lX -> 0x%08lX\n", i, (unsigned long) got_local_base[i], (unsigned long) relocated);
        got_local_base[i] = relocated;
    }

    printf("relocating global entries\n");
    printf("#####: value        relocated\n");
    for (size_t i = 0; i < got_global_count; i++) {
        uintptr_t relocated = (uintptr_t) ctx->module->base + got_global_base[i];
        printf("%5zu: 0x%08lX -> 0x%08lX\n", i, (unsigned long) got_global_base[i], (unsigned long) relocated);
        got_global_base[i] = relocated;
    }

    // install lazy resolver and module pointer

    got_local_base[0] = (uintptr_t) dl_resolve_stub;
    got_local_base[1] = (uintptr_t) ctx->module; // module pointer (GNU extension)

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

            Elf32_Sym* symbol = &ctx->module->dso_context.dynsym[ELF32_R_SYM(reloc->r_info)];
            Elf32_Shdr* symbol_section = &ctx->shdr[symbol->st_shndx];

            printf("%6zu: %08lX %-14s %03lu: ", j, reloc->r_offset, reloc_types[ELF32_R_TYPE(reloc->r_info)], ELF32_R_SYM(reloc->r_info));

            if((symbol->st_info & 0xF) != STT_SECTION) {
                printf("shared object should only contain STT_SECTION symbols\n");
                dso_error(ctx, "unknown symbol type");
            }

            if(ELF32_R_TYPE(reloc->r_info) != R_MIPS_REL32) {
                printf("shared object should only contain R_MIPS_REL32 relocations\n");
                dso_error(ctx, "unknown relocation type");
            }

            printf("internal reloc to section %i (%s); ", 
                    symbol->st_shndx, 
                    &ctx->shstrtab[symbol_section->sh_name]);

            uintptr_t* reloc_target = (uintptr_t*) (reloc_section->sh_addr + reloc->r_offset);
            uintptr_t relocated;

            // A - EA + S
            if(ELF32_R_SYM(reloc->r_info) < ctx->module->dso_context.gotsym) {
                // local symbol
                // TODO: check this
                relocated = (uintptr_t) ctx->module->base + *reloc_target;
            } else {
                // global symbol
                // TODO: check this
                relocated = (uintptr_t) ctx->module->base + got_global_base[ELF32_R_SYM(reloc->r_info) - ctx->module->dso_context.gotsym] + *reloc_target;
            }

            printf("relocating to 0x%08lX -> 0x%08lX\n", (unsigned long) *reloc_target, (unsigned long) relocated);

            *reloc_target = relocated;

        }        

    }

    // everything is loaded, destroy the load context

    struct module_t* module = dso_destroy_load_context(ctx);

    // count 'exported' symbols

    size_t symbol_count = 0;
    uint32_t symbol_index = 0;
    for(size_t i = 0; i < module->dso_context.dynsym_count; i++) {
        Elf32_Sym* sym = &module->dso_context.dynsym[i];
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
    for(size_t i = 0; i < module->dso_context.dynsym_count; i++) {
        Elf32_Sym* sym = &module->dso_context.dynsym[i];
        char* name;

        if(sym->st_name != STN_UNDEF) {
            name = &module->dso_context.dynstr[sym->st_name];
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

    for(size_t i = 0; i < module->dso_context.dynsym_count; i++) {
        Elf32_Sym* sym = &module->dso_context.dynsym[i];
        if(sym->st_shndx != SHN_UNDEF) continue;
        if(sym->st_name == STN_UNDEF) continue;
        dl_resolve(module, i);
    }
}