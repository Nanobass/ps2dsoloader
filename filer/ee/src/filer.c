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

/* libc */

/* libkernel */
#include <kernel.h>
#include <iopcontrol.h>

#include <math3d.h>

//========================================
// Project Includes
//========================================

//========================================
// Definitions
//========================================

#define EXPORT __attribute__((visibility("default")))

extern char data[];

extern int printf(const char* format, ...);

#define mprintf(...) printf("filer: " __VA_ARGS__)

EXPORT int filer_reset_iop() {
    mprintf("resetting IOP...\n");
    while(!SifIopReset("", 0x80000000));
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
    mprintf("shutting down filer... %s\n", data);
    return 0;
}

EXPORT int _start(int argc, char *argv[]) {
    mprintf("started\n");
    VECTOR a = {0, 1, 0, 1};
    VECTOR b = {1, 0, 0, 0};
    VECTOR c;
    vector_add(c, a, b);
    mprintf("vector_add result: %f %f %f %f\n", c[0], c[1], c[2], c[3]);
    return 0;
}