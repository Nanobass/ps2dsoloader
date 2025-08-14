#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <setjmp.h>

#include <elf.h>

#define SHF_EXTRA_ALLOCATION 0x10000

struct elf_load_context_t {
    FILE* file; 
    jmp_buf error;
    struct module_t* module;
    Elf32_Ehdr ehdr;
    Elf32_Phdr* phdr;
    Elf32_Shdr* shdr;
    const char* shstrtab;
};

struct elf_load_context_t* dso_create_load_context(FILE* file);
struct module_t* dso_destroy_load_context(struct elf_load_context_t* ctx);
void __attribute__((noreturn)) dso_error(struct elf_load_context_t* ctx, const char* msg);

void dso_read_elf_header(struct elf_load_context_t* ctx, uint16_t type);
void dso_read_program_headers(struct elf_load_context_t* ctx);
void dso_read_section_headers(struct elf_load_context_t* ctx);

void dso_print_program_headers(struct elf_load_context_t* ctx);
void dso_print_section_headers(struct elf_load_context_t* ctx);
void dso_print_dynamic_tags(struct elf_load_context_t* ctx);
void dso_print_symbol_table(struct elf_load_context_t* ctx, Elf32_Sym* symtab, size_t sym_count, const char* strtab);

void dso_allocate_module(struct elf_load_context_t* ctx, size_t extra, int type);
void dso_read_module_sections(struct elf_load_context_t* ctx);

void dso_allocate_extra_section(struct elf_load_context_t* ctx, Elf32_Section index);
void dso_free_extra_section(struct elf_load_context_t* ctx, Elf32_Section index);
void dso_free_extra_sections(struct elf_load_context_t* ctx);

int dso_find_section_by_name(struct elf_load_context_t* ctx, Elf32_Section* section, const char* name);
int dso_find_section_by_type(struct elf_load_context_t* ctx, Elf32_Section* section, uint32_t type);
int dso_find_dynamic_tag(struct elf_load_context_t* ctx, Elf32_Dyn** tag, Elf32_Section dynamic, int type);
int dso_count_dynamic_tags(struct elf_load_context_t* ctx, int type);

void* dso_section_address(struct elf_load_context_t* ctx, Elf32_Section section);
const char* dso_section_name(struct elf_load_context_t* ctx, Elf32_Section section);
const char* dso_symbol_name(struct elf_load_context_t* ctx, const char* strtab, Elf32_Sym* symbol);