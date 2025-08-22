#pragma once

extern char * program_header_types[];
extern char * section_types[];
extern char * dynamic_tag_types[];
extern char * mips_dynamic_tag_types[];
extern char * symbol_types[];
extern char * binding_types[];
extern char * reloc_types[];

#define DL_DBG_NONE 0
#define DL_DBG_GENERIC (1 << 0)
#define DL_DBG_EHDR (1 << 1)
#define DL_DBG_PHDR (1 << 2)
#define DL_DBG_SHDR (1 << 3)
#define DL_DBG_DYN (1 << 4)
#define DL_DBG_REL (1 << 5)
#define DL_DBG_GOT (1 << 6)
#define DL_DBG_SYM (1 << 7)
#define DL_DBG_DEPENDANCY (1 << 8)

void dl_debug_add_group(int group);
void dl_debug_remove_group(int group);
void dl_debug_clear_group();
int dl_debug_printf(int level, const char *fmt, ...);