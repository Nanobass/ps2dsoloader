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
#include <stdio.h>

/* ps2sdk */
#include <kernel.h>

#include <dl.h>
#include <exports.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char* argv[]) {
    exports_add_global_symbols();
    
    dl_set_module_path("erx");

    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        const char* error_msg = lua_tostring(L, -1);
        printf("lua error: %s\n", error_msg);
        lua_pop(L, 1);
    }
    lua_close(L);

    dl_print_dependencies();
    dl_remove_depender(NULL);

    SleepThread();
    return 0;
}