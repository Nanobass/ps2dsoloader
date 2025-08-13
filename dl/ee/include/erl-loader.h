#pragma once

#include <dl.h>

#include <stdio.h>

/**
 * load an ERL object from a file
 * @param file file pointer to the ERL file
 * @return a pointer to the loaded ERL, or NULL on failure
 */
struct module_t* dl_load_erl(FILE* file);

