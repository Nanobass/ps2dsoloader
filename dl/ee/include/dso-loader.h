#pragma once

#include <dlfcn.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <setjmp.h>

#include <elf.h>

struct symbol_t {
    union {
        struct module_t* module; // for local symbol
        struct symbol_t* next;   // for global symbol
    };
    char* name;
    uint32_t info;
    void* address;
};

struct module_t {
    struct module_t* next;
    struct symbol_t* symbols;
    size_t symbol_count;

    char* name;
    char** dependencies;

    void* extra;

    size_t size;
    uint8_t base[];
};

struct dependency_t {
    struct module_t* provider;
    struct module_t* depender;
    struct dependency_t* prev;
    struct dependency_t* next;
};

typedef int (*_start_t)(int, char**);
typedef void (*_exit_t)();

/**
 * load a shared object from a file
 * @param file the file pointer for the shared object
 * @return a pointer to the loaded module, or NULL on failure
 */
struct module_t* dl_load_module(FILE* file);

/**
 * force resolves all symbols in a module
 * @param module the module to resolve
 */
void dl_resolve_module(struct module_t* module);

/**
 * raise an error
 * @param msg the error message
 */
void dl_raise(const char* msg);

/**
 * allocate a new module
 * @param size the size of the module
 * @return a pointer to the new module, or NULL on failure
 */
struct module_t* dl_allocate_module(size_t size);

/**
 * free a module
 * @param module the module to free
 * @return 0 on success, -1 on failure
 */
int dl_free_module(struct module_t* module);

/**
 * find a symbol by name in a module
 * @param module the module to search in
 * @param name the name of the symbol to find
 * @return the symbol if found, NULL otherwise
 */
struct symbol_t* dl_module_find_symbol(struct module_t* module, const char* name);

int dl_add_dependency(struct module_t* depender, struct module_t* provider);
int dl_remove_dependency(struct module_t* depender, struct module_t* provider);

/**
 * add a global symbol
 * @param name the name of the symbol
 * @param address the address of the symbol
 * @param info the symbol's information
 * @return 0 on success, -1 on failure
 */
int dl_add_global_symbol(const char* name, void* address, uint32_t info);

/**
 * remove a global symbol
 * @param name the name of the symbol
 * @param info the symbol's information
 */
void dl_remove_global_symbol(const char* name, uint32_t info);

/**
 * add global symbols from a module
 * @param module the module to add symbols from
 * @return 0 on success, -1 on failure
 */
int dl_add_global_symbols(struct module_t* module);

/**
 * remove global symbols from a module
 * @param module the module to remove symbols from
 */
void dl_remove_global_symbols(struct module_t* module);

/**
 * find a symbol by name in a module
 * @param module the module to search in
 * @param name the name of the symbol to find
 * @return the symbol if found, NULL otherwise
 */
struct symbol_t* dl_find_global_symbol(const char* name);

/**
 * dump all global symbols
 */
void dl_dump_global_symbols();
