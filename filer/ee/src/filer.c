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
#include <kernel.h>
#include <loadfile.h>

#define NEWLIB_PORT_AWARE
#include <fileXio_rpc.h>

//========================================
// Project Includes
//========================================

//========================================
// Definitions
//========================================

#define EXPORT __attribute__((visibility("default")))

extern char data[];

const char* id = "libfiler";

extern int printf(const char* format, ...);

#define mprintf(...) printf("filer: " __VA_ARGS__)

EXPORT int filer_reset_iop() {
    mprintf("resetting IOP...\n");
    SifLoadModule("host0:/irx/iomanX.irx", 0, NULL);
    SifLoadModule("host0:/irx/fileXio.irx", 0, NULL);
    fileXioInit();
    fileXioSetRWBufferSize(128 * 1024);
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

EXPORT int filer_hello() {
    mprintf("hello world\n");
    return 0;
}

EXPORT __attribute__((constructor)) int filer_init() {
    mprintf("initializing filer... %s\n", id);
    return 0;
}

EXPORT __attribute__((destructor)) int filer_shutdown() {
    mprintf("shutting down filer... %s\n", id);
    fileXioExit();
    return 0;
}

EXPORT int _start(int argc, char *argv[]) {
    mprintf("started\n");
    mprintf("id: %p\n", &id);
    mprintf("id: %p\n", id);
    mprintf("id: %s\n", id);
    return 0;
}