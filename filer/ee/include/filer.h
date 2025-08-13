#pragma once

extern int filer_reset_iop();
extern int filer_device_control(const char* device_name, int cmd, int len, void* buf);
extern int filer_module_control(const char* module_name, int cmd, int len, void* buf);
extern int filer_hello();
extern int filer_init();
extern int filer_shutdown();

typedef int (*filer_reset_iop_t)();
typedef int (*filer_device_control_t)(const char* device_name, int cmd, int len, void* buf);
typedef int (*filer_module_control_t)(const char* module_name, int cmd, int len, void* buf);
typedef int (*filer_hello_t)();
typedef int (*filer_init_t)();
typedef int (*filer_shutdown_t)();