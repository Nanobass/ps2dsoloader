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
#include <malloc.h>
#include <unistd.h>
#include <setjmp.h>

/* ps2sdk */
#include <kernel.h>

#include <dl.h>

#include <dso-loader.h>
#include <erl-loader.h>
#include <export-elf.h>

void check_error() {
   const char* error = dlerror();
    if(error) {
        printf("dlerror: %s\n", error);
        abort();
    }
}

int main(int argc, char* argv[]) {

    // load main elf symbol table
    FILE* file = fopen(argv[0], "rb");
    if (!file) {
        perror("fopen");
        abort();
    }
    dl_load_elf_symbols(file);
    fclose(file);

    struct module_t* erl = dlopen("erl/libfileXio.erl", RTLD_NOW | RTLD_GLOBAL);
    check_error();

    // load dynamic object
    struct module_t* filer = dlopen("libfiler.so", RTLD_NOW | RTLD_GLOBAL);
    check_error();

    _start_t _start = (_start_t)dlsym(filer, "_start");
    check_error();
    int ret = _start(argc, argv);
    printf("start returned: %d\n", ret);

    dlclose(filer);
    dlclose(erl);

    SleepThread();
    return 0;
}