#include <dso-loader.h>

#include <stdlib.h>
#include <string.h>

struct symbol_t* global_symbols = NULL, *global_symbols_tail = NULL;

int dl_add_global_symbol(const char* name, void* address, uint32_t info)
{
    if (!name || !address) {
        dl_raise("invalid name or address");
        return -1;
    }

    struct symbol_t* symbol = (struct symbol_t*)malloc(sizeof(struct symbol_t));
    if (!symbol) {
        dl_raise("out of memory for global symbol");
        return -1;
    }

    symbol->name = strdup(name);
    if (!symbol->name) {
        free(symbol);
        dl_raise("out of memory for global symbol name");
        return -1;
    }
    symbol->address = address;
    symbol->info = info;
    symbol->next = NULL;

    if (!global_symbols) {
        global_symbols = symbol;
        global_symbols_tail = symbol;
    } else {
        global_symbols_tail->next = symbol;
        global_symbols_tail = symbol;
    }

    printf("global symbol added: info: %ld symbol: %s\n", info, name);

    return 0;
}

void dl_remove_global_symbol(const char* name, uint32_t info)
{
    if (!name) {
        dl_raise("invalid name");
        return;
    }

    struct symbol_t* current = global_symbols;
    struct symbol_t* previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0 && current->info == info) {
            if (previous) {
                previous->next = current->next;
            } else {
                global_symbols = current->next;
            }
            if (global_symbols_tail == current) {
                global_symbols_tail = previous;
            }

            printf("global symbol removed: %s at %p (info: %ld)\n", current->name, current->address, current->info);

            free(current->name);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    dl_raise("global symbol not found");
}

int dl_add_global_symbols(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return -1;
    }

    for(uint32_t i = 0; i < module->symbol_count; i++) {
        if (dl_add_global_symbol(module->symbols[i].name, module->symbols[i].address, module->symbols[i].info) < 0) {
            return -1;
        }
    }
    return 0;
}

void dl_remove_global_symbols(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return;
    }

    for(uint32_t i = 0; i < module->symbol_count; i++) {
        dl_remove_global_symbol(module->symbols[i].name, module->symbols[i].info);
    }
}

struct symbol_t* dl_find_global_symbol(const char* name)
{
    struct symbol_t* symbol = NULL;
    for(struct symbol_t* current = global_symbols; current; current = current->next) {
        if (strcmp(current->name, name) == 0) {
            if(!symbol) {
                symbol = current;
                continue;
            }
            if(ELF32_ST_BIND(symbol->info) == STB_WEAK && ELF32_ST_BIND(current->info) == STB_WEAK) {
                printf("warning: multiple weak symbols found for '%s', using first one\n", name);
                continue;
            }
            if(ELF32_ST_BIND(symbol->info) == STB_WEAK && ELF32_ST_BIND(current->info) == STB_GLOBAL) {
                symbol = current;
                return symbol;
            }
        }
    }
    return symbol;
}

void dl_dump_global_symbols() {
    struct symbol_t* current = global_symbols;
    printf("global symbols:\n");
    while (current) {
        printf("  %s: %p (info: %ld)\n", current->name, current->address, current->info);
        current = current->next;
    }
}