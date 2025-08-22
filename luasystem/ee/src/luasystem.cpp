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

/* libstdc++ */
#include <exception>

//========================================
// PS2SDK Includes
//========================================

/* libkernel */
#include <kernel.h>
#include <iopcontrol.h>
#include <loadfile.h>

/* libfileXio */
#define NEWLIB_PORT_AWARE
#include <fileXio_rpc.h>

/* libc */
#include <unistd.h>

//========================================
// Project Includes
//========================================

/* sol */
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//========================================
// Definitions
//========================================

/* very ugly hack */
void* __dso_handle;

void reset_iop() {
    while(!SifIopReset("", 0x80000000));
    while(!SifIopSync());
}

void load_irx(const char* path, int arglen = 0, const char* args = nullptr) {
    char buf[256];
    getcwd(buf, sizeof(buf));
    sprintf(buf + strlen(buf), "/irx/%s", path);
    int id = SifLoadModule(buf, arglen, args);
    if(id < 0) {
        throw std::runtime_error("failed to load iop module");
    }
}

void launch_elf(const char* path, int argc, char* argv[]) {
}

namespace api {

void initializeSystem(bool resetiop) {
    if (resetiop) {
        reset_iop();
    }
}

void initializeFileXio() {
    load_irx("iomanX.irx");
    load_irx("fileXio.irx");
    fileXioInit();
}

void launchElf(const std::string& path) {
    char* argv[] = { const_cast<char*>(path.c_str()), nullptr };
    launch_elf(path.c_str(), 1, argv);
}

int currentTimeMillis() {
    return clock() * 1000 / CLOCKS_PER_SEC;
}

}

extern "C" __attribute__((visibility("default"))) int luaopen_luasystem(lua_State* L) noexcept try {
    sol::state_view lua(L);

    auto table = lua.create_table();
    table["initializeSystem"] = &api::initializeSystem;
    table["initializeFileXio"] = &api::initializeFileXio;
    table["launchElf"] = &api::launchElf;
    table["currentTimeMillis"] = &api::currentTimeMillis;
    table.push();

    return 1;
} catch (std::exception& e) {
    return luaL_error(L, "%s", e.what());
}