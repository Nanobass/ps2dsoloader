#include <dso-loader.h>
#include <dso.h>

#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

#include <kernel.h>

static const char *local_names[] = {"_init", "_fini", "erl_id", "erl_dependancies", "erl_copyright", "erl_version", "_start", 0};

static uint32_t align(uint32_t x, uint8_t align) {
#ifdef FORCE_ALIGN
    if (align < 16)
	align = 16;
#endif
    align--;
    if (x & align) {
        x |= align;
        x++;
    }
    return x;
}

static void* erl_resolve(struct module_t* module, const char* sym) {
    for(struct module_t* iterator = dl_module_root(); iterator; iterator = iterator->next) {
        struct symbol_t* symbol = dl_module_find_symbol(iterator, sym);
        if (symbol) {
            dl_add_dependency(module, iterator);
            return symbol->address;
        }
    }
    struct symbol_t* symbol = dl_find_global_symbol(sym);
    if (symbol) {
        dl_add_dependency(module, NULL);
        return symbol->address;
    }
    return NULL;
}

static int apply_reloc(uint8_t *reloc, int type, uint32_t addr) {
    uint32_t u_current_data;
    int32_t s_current_data;
    uint32_t newstate;

    if (((uint32_t)reloc) & 0x3) {
        printf("unaligned reloc (%p) type=%d!\n", reloc, type);
    }

    memcpy(&u_current_data, reloc, 4);
    memcpy(&s_current_data, reloc, 4);

    switch (type) {
        case R_MIPS_32:
            newstate = s_current_data + addr;
            break;
        case R_MIPS_26:
            newstate = (u_current_data & 0xfc000000) 
                | (((u_current_data & 0x03ffffff) + (addr >> 2)) & 0x3ffffff);
            break;
        case R_MIPS_HI16:
            newstate = (u_current_data & 0xffff0000) 
                | ((((s_current_data << 16) >> 16) + (addr >> 16) + (((addr & 0xffff) >= 0x8000) && !(u_current_data & 0xf) ? 1 : 0)) & 0xffff);
            break;
        case R_MIPS_LO16:
            newstate = (u_current_data & 0xffff0000) 
                | ((((s_current_data << 16) >> 16) + (addr & 0xffff)) & 0xffff);
            break;
        default:
            printf("unknown relocation type %d at %p\n", type, reloc);
            return -1;
    }

    memcpy(reloc, &newstate, 4);

    printf("changed data at %08X from %08lX to %08lX.\n", (unsigned int) reloc, u_current_data, newstate);
    return 0;
}

struct module_t* dl_load_erl(FILE* file)
{
    struct elf_load_context_t* ctx = dso_create_load_context(file);
    if (!ctx) {
        dl_raise("failed to create load context");
        return NULL;
    }
    
    int rv = setjmp(ctx->error);
    if(rv) {
        struct module_t* module = dso_destroy_load_context(ctx);
        if(module) dl_free_module(module);
        dl_raise((const char*) rv);
        return NULL;
    }
    
    dso_read_elf_header(ctx, ET_REL);

    dso_read_section_headers(ctx);

    size_t module_size = 0;
    for(Elf32_Section i = 1; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        if(section->sh_flags & SHF_ALLOC) {
            // align the section address after the last section
            module_size = align(module_size, section->sh_addralign);
            section->sh_addr = module_size;
            module_size += section->sh_size;
        }
    }

    dso_print_section_headers(ctx);

    dso_allocate_module(ctx, module_size);
    dso_read_module_sections(ctx);

    Elf32_Section symtab_index = 0, symstr_index = 0;
    if(dso_find_section_by_type(ctx, &symtab_index, SHT_SYMTAB) < 0) {
        dso_error(ctx, "failed to find symbol table");
    } else {
        printf("symbol table found at offset 0x%08lX\n", ctx->shdr[symtab_index].sh_offset);
        symstr_index = ctx->shdr[symtab_index].sh_link;
        printf("symbol string table found at offset 0x%08lX\n", ctx->shdr[symstr_index].sh_offset);
    }

    dso_allocate_extra_section(ctx, symtab_index);
    dso_allocate_extra_section(ctx, symstr_index);

    Elf32_Sym* symtab = (Elf32_Sym*) ctx->shdr[symtab_index].sh_addr;
    char* strtab = (char*) ctx->shdr[symstr_index].sh_addr;

    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        const char* name;
        if(section->sh_name != SHN_UNDEF) {
            name = &ctx->shstrtab[section->sh_name];
        } else {
            name = "<unnamed>";
        }

        if(section->sh_type != SHT_REL &&
            section->sh_type != SHT_RELA) {
            printf("skipping section %s (type %ld)\n", name, section->sh_type);
            continue;
        } else if(!(ctx->shdr[section->sh_info].sh_flags & SHF_ALLOC) && !(ctx->shdr[section->sh_info].sh_flags & SHF_EXTRA_ALLOCATION)) {
            printf("section %02d (%s): contains relocations for unloaded section\n", i, name);
            continue;
        } else {
            printf("section %02d (%s): contains relocations\n", i, name);
        }

        dso_allocate_extra_section(ctx, i);

        printf("######: offset   type symbol\n");
        for(size_t j = 0; j < section->sh_size / section->sh_entsize; j++) {

            Elf32_Rel* reloc = (Elf32_Rel*) (section->sh_addr + j * section->sh_entsize);
            Elf32_Rel* next_reloc = NULL;
            
            size_t addend = 0;
            if(section->sh_type == SHT_RELA) {
                addend = ((Elf32_Rela*)reloc)->r_addend;
            }

            uint32_t sym_index = ELF32_R_SYM(reloc->r_info);
            uint32_t next_sym_index = 0;
            bool has_next_reloc = 0;

            if(j + 1 < section->sh_size / section->sh_entsize) {
                next_reloc = (Elf32_Rel*)(section->sh_addr + (j + 1) * section->sh_entsize);
                next_sym_index = ELF32_R_SYM(next_reloc->r_info);
                has_next_reloc = 1;
            }

            printf("%6zu: %08lX %4s %3lu: ", j, reloc->r_offset, 
                (section->sh_type == SHT_RELA) ? "RELA" : 
                (section->sh_type == SHT_REL) ? "REL" : "UNKNOWN", sym_index);

            Elf32_Sym* elf_symbol = &symtab[sym_index];
            Elf32_Sym* next_elf_symbol = NULL;
            if(has_next_reloc) {
                next_elf_symbol = &symtab[next_sym_index];
            }
            const char* symbol_name = &strtab[elf_symbol->st_name];
            void* symbol_address = NULL;
            switch(elf_symbol->st_info & 0xf) {
                case STT_NOTYPE:
                    printf("external symbol reloc to '%s' ", symbol_name);
                    symbol_address = erl_resolve(ctx->module, symbol_name);
                    if (!symbol_address) {
                        printf(" (not found in global symbols)\n");
                        dso_error(ctx, "unresolved external");
                    } else {
                        printf(" (found at %p); ", symbol_address);
                        if(apply_reloc((uint8_t*)ctx->shdr[section->sh_info].sh_addr + reloc->r_offset, ELF32_R_TYPE(reloc->r_info), (uint32_t)symbol_address + addend) < 0) {
                            dso_error(ctx, "failed to apply relocation to STT_NOTYPE symbol");
                        }
                        printf("\n");
                    }
                    break;
                case STT_SECTION:
                    printf("internal section reloc to %i; ", elf_symbol->st_shndx);

                    if(ELF32_R_TYPE(reloc->r_info) == R_MIPS_HI16 && (has_next_reloc && (ELF32_R_TYPE(next_reloc->r_info) == R_MIPS_LO16)) /* high and low fit together */
                        && (ctx->shdr[elf_symbol->st_shndx].sh_addr == ctx->shdr[next_elf_symbol->st_shndx].sh_addr) /* sections match */
                        && (*(uint16_t*)((uint8_t*)ctx->shdr[section->sh_info].sh_addr + next_reloc->r_offset) + 
                            (((uint32_t)(ctx->shdr[elf_symbol->st_shndx].sh_addr) + addend) & 0x0000ffff)) >= 0x8000 /* high part is valid */
                    ) {
                        // apply high and low relocations together
                        uint32_t data = *(uint32_t*)((uint8_t*)ctx->shdr[section->sh_info].sh_addr + reloc->r_offset);
                        *(uint32_t*)((uint8_t*)ctx->shdr[section->sh_info].sh_addr + reloc->r_offset) = data + !(data & 0xf);
                        printf("special ");
                    }

                    if(apply_reloc(
                        (uint8_t*)ctx->shdr[section->sh_info].sh_addr + reloc->r_offset, 
                        ELF32_R_TYPE(reloc->r_info), 
                        (uint32_t)ctx->shdr[elf_symbol->st_shndx].sh_addr + addend) < 0
                    ) {
                        dso_error(ctx, "failed to apply relocation to STT_SECTION symbol");
                    }

                    break;
                case STT_OBJECT:
                case STT_FUNC:
                    printf("internal symbol reloc to '%s' ", symbol_name);
                    for (size_t k = 0; k < ctx->shdr[symtab_index].sh_size / sizeof(Elf32_Sym); k++) {
                        Elf32_Sym* sym = &symtab[k];
                        const char* name = &strtab[sym->st_name];
                        if (strcmp(name, symbol_name) == 0) {
                            symbol_address = (void*)((uint32_t)ctx->shdr[sym->st_shndx].sh_addr + sym->st_value);
                            printf("(local at %p); ", symbol_address);
                            break;
                        }
                    }
                    if (!symbol_address) {
                        symbol_address = erl_resolve(ctx->module, symbol_name);
                        printf("(global at %p); ", symbol_address);
                    }
                    if (!symbol_address) {
                        printf("(not found)\n");
                        dso_error(ctx, "unresolved external");
                    } else {
                        if(apply_reloc(
                            (uint8_t*)ctx->shdr[section->sh_info].sh_addr + reloc->r_offset, 
                            ELF32_R_TYPE(reloc->r_info), 
                            (uint32_t)symbol_address + addend) < 0
                        ) {
                            dso_error(ctx, "failed to apply relocation to STT_FUNC or STT_OBJECT symbol");
                        }
                    }
                    break;
                case STT_FILE:
                    break;
                default:
                    dso_error(ctx, "unknown symbol type");
            }
        }        

        dso_free_extra_section(ctx, i);
    }

    size_t symbol_count = 0;
    
    printf("module symbols\n");
    printf("######: size     address  type           bind        index name\n");
    for (size_t i = 0; i < ctx->shdr[symtab_index].sh_size / sizeof(Elf32_Sym); i++) {
        Elf32_Sym* sym = &symtab[i];
        if(ELF32_ST_TYPE(sym->st_info) != STT_FUNC && ELF32_ST_TYPE(sym->st_info) != STT_OBJECT) continue;
        if(sym->st_name == STN_UNDEF) continue;
        const char* name = &strtab[sym->st_name];

        for (const char **local_name = local_names; *local_name; local_name++) {
            if (strcmp(*local_name, name) == 0) {
                sym->st_info = ELF32_ST_INFO(STB_LOCAL, ELF32_ST_TYPE(sym->st_info));
                break;
            }
        }

        printf("%6zu: %08lX %08lX %-14s %-10s %6u %s\n", i, sym->st_size, sym->st_value,
                symbol_types[ELF32_ST_TYPE(sym->st_info) > STT_LOPROC ? STT_LOPROC : ELF32_ST_TYPE(sym->st_info)],
                binding_types[ELF32_ST_BIND(sym->st_info) > STB_LOPROC ? STB_LOPROC : ELF32_ST_BIND(sym->st_info)],
                sym->st_shndx, name);

        symbol_count++;
    }

    ctx->module->symbol_count = symbol_count;
    ctx->module->symbols = malloc(symbol_count * sizeof(struct symbol_t));
    if (!ctx->module->symbols) {
        dso_error(ctx, "out of memory for module symbols");
    }

    uint32_t j = 0;
    for (size_t i = 0; i < ctx->shdr[symtab_index].sh_size / sizeof(Elf32_Sym); i++) {
        Elf32_Sym* sym = &symtab[i];
        if(ELF32_ST_TYPE(sym->st_info) != STT_FUNC && ELF32_ST_TYPE(sym->st_info) != STT_OBJECT) continue;
        if(sym->st_name == STN_UNDEF) continue;
        const char* name = &strtab[sym->st_name];
        ctx->module->symbols[j].name = strdup(name);
        ctx->module->symbols[j].address = (void*)((uint32_t)ctx->shdr[sym->st_shndx].sh_addr + sym->st_value);
        ctx->module->symbols[j].info = sym->st_info;
        j++;
    }

    struct symbol_t* symbol = NULL;
    symbol = dl_module_find_symbol(ctx->module, "erl_id");
    if (!symbol) {
        dso_error(ctx, "module does not contain erl_id symbol");
    } else {
        ctx->module->name = *(char**)symbol->address;
    }

    symbol = dl_module_find_symbol(ctx->module, "erl_dependancies");
    if (!symbol) {
        dso_error(ctx, "module does not contain erl_dependancies symbol");
    } else {
        char** dependencies = (char**)symbol->address;
        size_t dependency_count = 0;
        for(char** i = dependencies; *i; i++) {
            dependency_count++;
        }
        ctx->module->dependencies = malloc((dependency_count + 1) * sizeof(char*));
        if (!ctx->module->dependencies) {
            dso_error(ctx, "out of memory for module dependencies");
        }
        for (size_t i = 0; i < dependency_count; i++) {
            ctx->module->dependencies[i] = dependencies[i];
        }
        ctx->module->dependencies[dependency_count] = NULL;
    }

    struct module_t* module = dso_destroy_load_context(ctx);

    FlushCache(2);
    FlushCache(0);

    return module;
}