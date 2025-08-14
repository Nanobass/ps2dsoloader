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