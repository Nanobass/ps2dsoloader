//=============================================================================
// _____     ___ ____  # insert another cool logo here
//  ____|   |    ____| # insert another cool logo here
// |     ___|   |____  # insert another cool logo here
// ---------------------------------------------------
//
// File:        filer.cpp
//
// Description: 
//
//=============================================================================

//========================================
// System Includes
//========================================

#include <exception>

//========================================
// PS2SDK Includes
//========================================

/* liblua */
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}

//========================================
// Project Includes
//========================================

/* sol */

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//========================================
// Definitions
//========================================

#define EXPORT __attribute__((visibility("default")))

void* __dso_handle;

extern "C" EXPORT int luaopen_luasystem(lua_State* L) noexcept try {
    sol::state_view lua(L);

    auto table = lua.create_table();
    table["foo"] = [](int a, int b) { return a + b; };
    table["bar"] = [](int a, int b) { return a * b; };
    table.push();

    return 1;
} catch (std::exception& e) {
    return luaL_error(L, "%s", e.what());
}