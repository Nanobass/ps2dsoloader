#include <dl.h>

#include <dso-loader.h>
#include <erl-loader.h>

#include <string.h>
#include <stdlib.h>

static char module_path[128];

void dl_set_module_path(const char* path) {
    strncpy(module_path, path, sizeof(module_path) - 1);
}

const char* dl_module_path() {
    return module_path;
}

struct module_t* dl_load_module(const char* filename)
{
    char path[256];

    FILE* file_handle = NULL;
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s/%s", dl_module_path(), filename);
        file_handle = fopen(path, "rb");    
    }
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s/%s.so", dl_module_path(), filename);
        file_handle = fopen(path, "rb");    
    }
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s/%s.erl", dl_module_path(), filename);
        file_handle = fopen(path, "rb");
    }
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s", filename);
        file_handle = fopen(path, "rb");    
    }
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s.so", filename);
        file_handle = fopen(path, "rb");    
    }
    if(!file_handle) {
        snprintf(path, sizeof(path), "%s.erl", filename);
        file_handle = fopen(path, "rb");
    }
    if (!file_handle) {
        dl_raise("cannot open file");
        return NULL;
    }

    struct module_t* module = NULL;
    const char* ext = strrchr(path, '.');
    if(!strcmp(ext, ".so")) {
        module = dl_load_dso(file_handle);
    } else if(!strcmp(ext, ".erl")) {
        module = dl_load_erl(file_handle);
    } else {
        dl_raise("unsupported file type");
    }
    
    fclose(file_handle);

    dl_print_memory_usage();

    return module;
}

void dl_resolve_module(struct module_t* module)
{
    switch (module->type)
    {
    case DL_MT_DSO:
        dl_resolve_dso(module);
        break;
    }
}

bool dl_is_module_present(const char* name) {
    return dl_get_module(name) != NULL;
}

struct module_t* dl_get_module(const char* name)
{
    struct module_t* module = dl_module_root();
    while (module) {
        if (!strcmp(module->name, name)) {
            return module;
        }
        module = module->next;
    }
    return NULL;
}

size_t dl_get_memory_total(size_t* moduleTotal, size_t* symbolTotal, size_t* stringTotal) {
    size_t total = 0;

    if (moduleTotal) *moduleTotal = 0;
    if (symbolTotal) *symbolTotal = 0;
    if (stringTotal) *stringTotal = 0;

    for(struct module_t* module = dl_module_root(); module; module = module->next) {
        if (moduleTotal) *moduleTotal += sizeof(struct module_t) + module->size;
        total += sizeof(struct module_t) + module->size;

        if (symbolTotal) *symbolTotal += module->symbol_count * sizeof(struct symbol_t);
        total += module->symbol_count * sizeof(struct symbol_t);

        for (uint32_t i = 0; i < module->symbol_count; i++) {
            if (!(module->symbols[i].info & SI_CCHAR_NAME)) {
                size_t name_length = strlen(module->symbols[i].name) + 1;
                if (stringTotal) *stringTotal += name_length;
                total += name_length;
            }
        }
    }

    return total;
}

void dl_print_memory_usage() {
    size_t moduleTotal = 0, symbolTotal = 0, stringTotal = 0;
    size_t total = dl_get_memory_total(&moduleTotal, &symbolTotal, &stringTotal);
    printf("memory usage:\n");
    printf("  modules: %zu bytes\n", moduleTotal);
    printf("  symbols: %zu bytes\n", symbolTotal);
    printf("  strings: %zu bytes\n", stringTotal);
    printf("  total  : %zu bytes\n", total);
}

uint32_t dl_align_address(uint32_t x, uint8_t align) {
    align--;
    if (x & align) {
        x |= align;
        x++;
    }
    return x;
}