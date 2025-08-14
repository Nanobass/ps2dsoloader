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

#include <stdio.h>

//========================================
// PS2SDK Includes
//========================================

/* liblua */
#include <lua.h>
#include <lauxlib.h>

//========================================
// Project Includes
//========================================

//========================================
// Definitions
//========================================

#define EXPORT __attribute__((visibility("default")))

int foo(lua_State* L)
{
  lua_Integer a = luaL_checkinteger(L, 1);
  lua_Integer b = luaL_checkinteger(L, 2);
  lua_pushinteger(L, a + b);
  return 1;
}

int bar(lua_State* L)
{
  lua_Integer a = luaL_checkinteger(L, 1);
  lua_Integer b = luaL_checkinteger(L, 2);
  lua_pushinteger(L, a * b);
  return 1;
}


luaL_Reg const foolib[] = {
  { "foo", foo },
  { "bar", bar },
  { 0, 0 }
};


EXPORT int luaopen_libfiler(lua_State* L)
{
  luaL_newlib(L, foolib);
  return 1;
}