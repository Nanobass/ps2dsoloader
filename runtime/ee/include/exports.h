#pragma once

struct export_list_t {
    char * name;
    void * pointer;
};

extern struct export_list_t* export_list[];

void exports_add_global_symbols();