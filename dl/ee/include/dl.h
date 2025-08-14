#pragma once

#include <dlfcn.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <setjmp.h>

#include <elf.h>

#define DL_MT_UNDEF 0
#define DL_MT_ERL 1
#define DL_MT_DSO 2
#define DL_MT_NUM 3

#define SI_CCHAR_NAME (1 << 31)

struct module_t;

typedef int (*_start_t)(int, char**);
typedef void (*_exit_t)();

typedef void (*_init_t)(struct module_t*);
typedef void (*_fini_t)(struct module_t*);

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

    _init_t init;
    _fini_t fini;

    int type;

    void* extra;

    size_t size;
    uint8_t base[];
};

struct dependency_t {
    struct module_t* provider;
    struct module_t* depender;
    size_t count;
    struct dependency_t* next;
};

/**
 * raise an error
 * @param msg the error message
 */
void dl_raise(const char* msg);

/**
 * set the module path, string is copied
 * @param path the module path
 */
void dl_set_module_path(const char* path);

const char* dl_module_path();

struct module_t* dl_load_module(const char* filename);

void dl_resolve_module(struct module_t* module);

bool dl_is_module_present(const char* name);

struct module_t* dl_get_module(const char* name);

/**
 * allocate a new module
 * @param size the size of the module
 * @return a pointer to the new module, or NULL on failure
 */
struct module_t* dl_allocate_module(size_t size, int type);

/**
 * free a module
 * @param module the module to free
 * @return 0 on success, -1 on failure
 */
int dl_free_module(struct module_t* module);

int dl_module_init(struct module_t* module);

int dl_module_fini(struct module_t* module);

struct module_t* dl_module_root();

/**
 * find a symbol by name in a module
 * @param module the module to search in
 * @param name the name of the symbol to find
 * @return the symbol if found, NULL otherwise
 */
struct symbol_t* dl_module_find_symbol(struct module_t* module, const char* name);

int dl_add_dependency(struct module_t* depender, struct module_t* provider);
int dl_remove_dependency(struct module_t* depender, struct module_t* provider);
int dl_remove_depender(struct module_t* depender);
void dl_print_dependencies();

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

void dl_sort_global_symbols();

/**
 * dump all global symbols
 */
void dl_dump_global_symbols();
