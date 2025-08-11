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

//========================================
// Project Includes
//========================================

//========================================
// Definitions
//========================================

#define EXPORT __attribute__((visibility("default")))

extern int printf(const char* format, ...);

#define mprintf(...) printf("filer: " __VA_ARGS__)

EXPORT int filer_reset_iop() {
    mprintf("resetting IOP...\n");
    return 0;
}

EXPORT int filer_device_control(const char* device_name, int cmd, int len, void* buf) {
    mprintf("controlling device %s with cmd %d, len %d\n", device_name, cmd, len);
    return 0;
}

EXPORT int filer_module_control(const char* module_name, int cmd, int len, void* buf) {
    mprintf("controlling module %s with cmd %d, len %d\n", module_name, cmd, len);
    return 0;
}

EXPORT int filer_shutdown() {
    mprintf("shutting down filer...\n");
    return 0;
}

EXPORT int _start(int argc, char *argv[]) {
    mprintf("started\n");
    return 0;
}