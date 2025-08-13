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
#include <export-elf.h>

char data[512];

int main(int argc, char* argv[]) {

    // load main elf symbol table
    FILE* file = fopen(argv[0], "rb");
    if (!file) {
        perror("fopen");
        abort();
    }
    dl_load_elf_symbols(file);
    fclose(file);

    file = fopen("libmath3d.erl", "rb");
    if (!file) {
        perror("libmath3d");
        abort();
    }
    struct module_t* libmath3d = dl_load_erl(file);
    if(dlerror()) SleepThread();
    dl_add_global_symbols(libmath3d);
    dl_add_dependency(NULL, libmath3d);
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

    dl_sort_global_symbols();
    dl_dump_global_symbols();

    char a[256];
    snprintf(a, sizeof(a), "start returned: %d\n", ret);

    float x = 2;
    float b = cosf(x);
    b = sinf(b);

    return 0;
}