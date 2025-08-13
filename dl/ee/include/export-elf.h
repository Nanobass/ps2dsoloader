#pragma once

#include <stdio.h>

/**
 * load the symbol table of the main executable
 * @param file file pointer to the main elf
 * @return 0 on success, -1 on failure
 */
int dl_load_elf_symbols(FILE* file);