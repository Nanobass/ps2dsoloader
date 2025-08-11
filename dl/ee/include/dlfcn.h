#pragma once

#define RTLD_LAZY 0x0001
#define RTLD_NOW 0x0002
#define RTLD_GLOBAL 0x0004
#define RTLD_LOCAL 0x0008

void* dlopen(const char* filename, int flags);
void* dlsym(void* handle, const char* symbol);
int dlclose(void* handle);
const char* dlerror(void);