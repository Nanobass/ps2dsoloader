#include <export-elf.h>

#include <dso.h>
#include <dso-loader.h>

int dl_load_elf_symbols(FILE* file) {
    struct elf_load_context_t* ctx = dso_create_load_context(file);
    if (!ctx) {
        dl_raise("failed to create load context");
        return -1;
    }
    
    int rv = setjmp(ctx->error);
    if(rv) {
        struct module_t* module = dso_destroy_load_context(ctx);
        if(module) dl_free_module(module);
        dl_raise((const char*) rv);
        return -1;
    }
    
    dso_read_elf_header(ctx, ET_EXEC);

    dso_read_section_headers(ctx);
    dso_print_section_headers(ctx);

    Elf32_Section symtab = 0, symstr = 0;
    if(dso_find_section_by_type(ctx, &symtab, SHT_SYMTAB) < 0) {
        dso_error(ctx, "failed to find symbol table");
    } else {
        printf("symbol table found at offset 0x%08lX\n", ctx->shdr[symtab].sh_offset);
        symstr = ctx->shdr[symtab].sh_link;
        printf("symbol string table found at offset 0x%08lX\n", ctx->shdr[symstr].sh_offset);
    }

    dso_allocate_extra_section(ctx, symtab);
    dso_allocate_extra_section(ctx, symstr);

    for(uint32_t i = 0; i < ctx->shdr[symtab].sh_size / sizeof(Elf32_Sym); i++) {
        Elf32_Sym* sym = (Elf32_Sym*) ctx->shdr[symtab].sh_addr + i;
        if(sym->st_name == STN_UNDEF) continue;
        if(ELF32_ST_BIND(sym->st_info) == STB_LOCAL && ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE) continue;
        if(ELF32_ST_TYPE(sym->st_info) != STT_FUNC && ELF32_ST_TYPE(sym->st_info) != STT_OBJECT && ELF32_ST_TYPE(sym->st_info) != STT_NOTYPE) continue;
        if(ELF32_ST_BIND(sym->st_info) != STB_GLOBAL && ELF32_ST_BIND(sym->st_info) != STB_WEAK) continue;
        const char* name = (const char*) ctx->shdr[symstr].sh_addr + sym->st_name;
        dl_add_global_symbol(name, (void*) sym->st_value, sym->st_info);
    }

    dso_destroy_load_context(ctx);
    return 0;
}