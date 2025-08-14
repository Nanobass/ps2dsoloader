#include <dl.h>

#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

struct global_symbol_block_t {
    struct global_symbol_block_t* next;
    struct symbol_t* symbols;
    size_t symbol_count;
};

static struct global_symbol_block_t* global_symbol_blocks = NULL, *global_symbol_blocks_tail = NULL;

static int dl_add_global_symbol_block(struct symbol_t* symbols, size_t symbol_count)
{
    struct global_symbol_block_t* block = (struct global_symbol_block_t*)malloc(sizeof(struct global_symbol_block_t));
    if (!block) {
        dl_raise("out of memory for global symbol block");
        return -1;
    }
    
    block->symbols = symbols;
    block->symbol_count = symbol_count;
    block->next = NULL;

    if (!global_symbol_blocks) {
        global_symbol_blocks = block;
        global_symbol_blocks_tail = block;
    } else {
        global_symbol_blocks_tail->next = block;
        global_symbol_blocks_tail = block;
    }

    return 0;
}

static int dl_remove_global_symbol_block(struct symbol_t* symbols) {
    struct global_symbol_block_t* current = global_symbol_blocks;
    struct global_symbol_block_t* previous = NULL;

    while (current) {
        if (current->symbols == symbols) {
            if (previous) {
                previous->next = current->next;
            } else {
                global_symbol_blocks = current->next;
            }
            if (global_symbol_blocks_tail == current) {
                global_symbol_blocks_tail = previous;
            }

            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }

    return -1;
}

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

    if (dl_add_global_symbol_block(symbol, 1) < 0) {
        free(symbol->name);
        free(symbol);
        return -1;
    }

    printf("global symbol added: %-40s %-10s %-10s\n", name, symbol_types[ELF32_ST_TYPE(info)], binding_types[ELF32_ST_BIND(info)]);

    return 0;
}

void dl_remove_global_symbol(const char* name, uint32_t info)
{
    if (!name) {
        dl_raise("invalid name");
        return;
    }

    struct global_symbol_block_t* current = global_symbol_blocks;
    struct global_symbol_block_t* previous = NULL;
    while (current) {
        if (current->symbol_count == 1 && !strcmp(current->symbols->name, name) && current->symbols->info == info) {
            if (previous) {
                previous->next = current->next;
            } else {
                global_symbol_blocks = current->next;
            }
            if (global_symbol_blocks_tail == current) {
                global_symbol_blocks_tail = previous;
            }

            struct symbol_t* current_symbol = current->symbols;
            free(current);
            printf("global symbol removed: %-40s %-10s %-10s\n", name, symbol_types[ELF32_ST_TYPE(info)], binding_types[ELF32_ST_BIND(info)]);
            free(current_symbol->name);
            free(current_symbol);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int dl_add_global_symbols(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return -1;
    }
    printf("global module added: %s\n", module->name);
    dl_add_global_symbol_block(module->symbols, module->symbol_count);
    return 0;
}

void dl_remove_global_symbols(struct module_t* module)
{
    if (!module) {
        dl_raise("invalid module");
        return;
    }
    dl_remove_global_symbol_block(module->symbols);
    printf("global module removed: %s\n", module->name);
}

struct symbol_t* dl_find_global_symbol(const char* name) {
    struct symbol_t* symbol = NULL;
    for(struct global_symbol_block_t* block = global_symbol_blocks; block; block = block->next) {
        for(size_t i = 0; i < block->symbol_count; i++) {
            if (strcmp(block->symbols[i].name, name) == 0) {
                if(!symbol) {
                    symbol = &block->symbols[i];
                    continue;
                }
                if(ELF32_ST_BIND(symbol->info) == STB_WEAK && ELF32_ST_BIND(block->symbols[i].info) == STB_WEAK) {
                printf("warning: multiple weak symbols found for '%s', using first one\n", name);
                continue;
                }
                if(ELF32_ST_BIND(symbol->info) == STB_WEAK && ELF32_ST_BIND(block->symbols[i].info) == STB_GLOBAL) {
                    symbol = &block->symbols[i];
                    return symbol;
                }
            }
        }
    }
    return symbol;
}

void dl_dump_global_symbols() {
    printf("global symbols:\n");
    for (struct global_symbol_block_t* block = global_symbol_blocks; block; block = block->next) {
        for (size_t i = 0; i < block->symbol_count; i++) {
            printf("  %s: %p (info: %ld)\n", block->symbols[i].name, block->symbols[i].address, block->symbols[i].info);
        }
    }
}