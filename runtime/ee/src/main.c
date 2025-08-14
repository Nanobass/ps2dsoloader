//=============================================================================
// _____     ___ ____  <insert cool logo here>
//  ____|   |    ____| <insert cool logo here>
// |     ___|   |____  <insert cool logo here>
// ---------------------------------------------------
//
// File:        main.c
//
// Description: 
//
//=============================================================================

/* standard library */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <unistd.h>
#include <setjmp.h>

/* ps2sdk */
#include <kernel.h>

#include <dl.h>
#include <export-elf.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void check_error() {
   const char* error = dlerror();
    if(error) {
        printf("dlerror: %s\n", error);
        abort();
    }
}

int main(int argc, char* argv[]) {

    // load main elf symbol table
    FILE* file = fopen(argv[0], "rb");
    if (!file) {
        perror("fopen");
        abort();
    }
    dl_load_elf_symbols(file);
    fclose(file);

    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        const char* error_msg = lua_tostring(L, -1);
        printf("lua error: %s\n", error_msg);
        lua_pop(L, 1);
    }
    lua_close(L);

    SleepThread();
    return 0;
}