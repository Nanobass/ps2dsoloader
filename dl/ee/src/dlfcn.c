#include <dso-loader.h>

#include <stdlib.h>
#include <stdio.h>

const char* dl_last_error = NULL;

void dl_raise(const char* msg) {
    if (msg) {
        dl_last_error = msg;
    } else {
        dl_last_error = "unknown error";
    }
    printf("dl error: %s\n", dl_last_error);
}

void* dlopen(const char* filename, int flags) {
    (void) flags;

    FILE* elf_handle = fopen(filename, "rb");
    if (!elf_handle) {
        dl_raise("cannot open file");
        return NULL;
    }
    struct module_t* module = dl_load_module(elf_handle);
    fclose(elf_handle);
    if(!module) {
        return NULL;
    }

    if(flags & RTLD_NOW) {
        dl_resolve_module(module);
    }

    if(flags & RTLD_GLOBAL) {
        dl_add_global_symbols(module);
    }

    dl_add_dependency(NULL, module);

    return module;
}

void* dlsym(void* handle, const char* symbol) {
    if(!symbol) {
        dl_raise("invalid symbol name");
        return NULL;
    }
    struct symbol_t* sym = NULL;
    if(!handle) {
        sym = dl_find_global_symbol(symbol);
    } else {
        sym = dl_module_find_symbol((struct module_t*)handle, symbol);
    }
    if(sym) {
        return sym->address;
    } else {
        dl_raise("symbol not found");
        return NULL;
    }
}

int dlclose(void* handle) {
    if(!handle) {
        dl_raise("invalid handle");
        return -1;
    }
    return dl_remove_dependency(NULL, (struct module_t*)handle);
}

const char* dlerror(void) {
    const char* error = dl_last_error;
    dl_last_error = NULL;
    return error;
}