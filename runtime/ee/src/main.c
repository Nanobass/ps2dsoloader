//=============================================================================
// _____     ___ ____  <insert cool logo here>
//  ____|   |    ____| <insert cool logo here>
// |     ___|   |____  <insert cool logo here>
// ---------------------------------------------------
//
// File:        main.c
//
// Description: 
//
//=============================================================================

/* standard library */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <setjmp.h>

/* ps2sdk */
#include <kernel.h>

#include <dso-loader.h>
#include <dso.h>

int main(int argc, char* argv[]) {

    // load main elf symbol table

    FILE* file = fopen(argv[0], "rb");
    if (!file) {
        perror("fopen");
        abort();
    }

    struct elf_load_context_t* ctx = dso_create_load_context(file);
    if (!ctx) {
        puts("failed to create load context");
        abort();
    }
    
    int rv = setjmp(ctx->error);
    if(rv) {
        struct module_t* module = dso_destroy_load_context(ctx);
        if(module) dl_free_module(module);
        puts((const char*) rv);
        abort();
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
        if(ELF32_ST_TYPE(sym->st_info) != STT_FUNC && ELF32_ST_TYPE(sym->st_info) != STT_OBJECT) continue;
        if(ELF32_ST_BIND(sym->st_info) != STB_GLOBAL && ELF32_ST_BIND(sym->st_info) != STB_WEAK) continue;
        const char* name = (const char*) ctx->shdr[symstr].sh_addr + sym->st_name;
        dl_add_global_symbol(name, (void*) sym->st_value, sym->st_info);
    }

    dso_destroy_load_context(ctx);

    fclose(file);

    // load dynamic object

    struct module_t* handle = dlopen("libfiler.so", RTLD_NOW | RTLD_GLOBAL);
    const char* error = dlerror();
    if(error) {
        printf("dlopen failed: %s\n", error);
        abort();
    }

    _start_t _start = (_start_t)dlsym(handle, "_start");
    error = dlerror();
    if(error) {
        printf("dlsym failed: %s\n", error);
        abort();
    }

    int ret = _start(argc, argv);

    printf("start returned: %d\n", ret);

    dlclose(handle);
    return 0;
}