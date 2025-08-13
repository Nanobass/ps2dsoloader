#pragma once

#include <dl.h>

#include <stdio.h>

/**
 * load a shared object from a file
 * @param file the file pointer for the shared object
 * @return a pointer to the loaded module, or NULL on failure
 */
struct module_t* dl_load_dso(FILE* file);

/**
 * force resolves all symbols in a module
 * @param module the module to resolve
 */
void dl_resolve_dso(struct module_t* module);