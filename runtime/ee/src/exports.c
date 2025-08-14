#include <exports.h>

#include <stdlib.h>
#include <dl.h>

extern struct export_list_t libc_exports[];
extern struct export_list_t libcdvd_exports[];
extern struct export_list_t libcglue_exports[];
extern struct export_list_t libkernel_exports[];
extern struct export_list_t liblua_exports[];
extern struct export_list_t libm_exports[];
extern struct export_list_t libpthread_exports[];
extern struct export_list_t libpthreadglue_exports[];

struct static_library_t {
    struct export_list_t* exports;
    const char* name;
};

struct static_library_t* static_libraries[] = {
    &(struct static_library_t){ libc_exports, "libc" },
    &(struct static_library_t){ libcdvd_exports, "libcdvd" },
    &(struct static_library_t){ libcglue_exports, "libcglue" },
    &(struct static_library_t){ libkernel_exports, "libkernel" },
    &(struct static_library_t){ liblua_exports, "liblua" },
    &(struct static_library_t){ libm_exports, "libmath" },
    &(struct static_library_t){ libpthread_exports, "libpthread" },
    &(struct static_library_t){ libpthreadglue_exports, "libpthreadglue" },
    0
};

void exports_add_global_symbols()
{
    for (struct static_library_t** lib = static_libraries; *lib; lib++) {
        struct module_t* module = dl_allocate_module(0, DL_MT_UNDEF);
        if (!module) {
            dl_raise("Failed to allocate module");
            return;
        }
        size_t count = 0;
        for (struct export_list_t* entry = (*lib)->exports; entry->pointer; entry++) {
            count++;
        }
        module->symbol_count = count;
        module->symbols = malloc(sizeof(struct symbol_t) * count);
        for(uint32_t i = 0; i < count; i++) {
            module->symbols[i].name = (*lib)->exports[i].name;
            module->symbols[i].address = (*lib)->exports[i].pointer;
            module->symbols[i].info = ELF32_ST_INFO(STB_GLOBAL, STT_FUNC) | SI_CCHAR_NAME;
            module->symbols[i].module = module;
        }
        module->name = (char*) (*lib)->name;
        module->dependencies = NULL;
        dl_add_dependency(NULL, module);
        dl_add_global_symbols(module);
    }
}