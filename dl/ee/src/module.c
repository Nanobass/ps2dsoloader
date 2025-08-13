#include <dso-loader.h>

#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

#include <kernel.h>

static struct module_t* modules = NULL, *modules_tail = NULL;

struct module_t* dl_allocate_module(size_t size) {
    struct module_t* module = (struct module_t*)malloc(sizeof(struct module_t) + size);
    if (!module) {
        return NULL;
    }
    memset(module, 0, sizeof(struct module_t) + size);
    module->size = size;
    if(!modules) {
        modules = module;
        modules_tail = module;
    } else {
        modules_tail->next = module;
        modules_tail = module;
    }
    return module;
}

int dl_free_module(struct module_t* module) {
    struct module_t* current = modules;
    struct module_t* previous = NULL;

    while (current) {
        if (current == module) {
            if (previous) {
                previous->next = current->next;
            } else {
                modules = current->next;
            }
            if (modules_tail == current) {
                modules_tail = previous;
            }
            if(current->symbols) free(current->symbols);
            if(current->dependencies) free(current->dependencies);
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    dl_raise("module not found");
    return -1;
}

struct module_t* dl_module_root() {
    return modules;
}

struct symbol_t* dl_module_find_symbol(struct module_t* module, const char* name) {
    if (!module || !name) {
        dl_raise("invalid module or name");
        return NULL;
    }

    for(uint32_t i = 0; i < module->symbol_count; i++) {
        struct symbol_t* symbol = &module->symbols[i];
        if (!strcmp(symbol->name, name)) {
            return symbol;
        }
    }

    return NULL;
}
