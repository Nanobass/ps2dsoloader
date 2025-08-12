#include <dso-loader.h>
#include <dso.h>

#include <debug-info.h>

#include <stdlib.h>
#include <string.h>

struct elf_load_context_t* dso_create_load_context(FILE* file)
{
    struct elf_load_context_t* ctx = malloc(sizeof(struct elf_load_context_t));
    if (!ctx) {
        return NULL;
    }
    ctx->file = file;
    ctx->module = NULL;
    memset(&ctx->ehdr, 0, sizeof(Elf32_Ehdr));
    ctx->phdr = NULL;
    ctx->shdr = NULL;
    ctx->shstrtab = NULL;
    return ctx;
}

struct module_t* dso_destroy_load_context(struct elf_load_context_t* ctx)
{
    printf("destroying load context\n");
    if (!ctx) return NULL;
    dso_free_extra_sections(ctx);
    if (ctx->shdr) free(ctx->shdr);
    if (ctx->phdr) free(ctx->phdr);
    struct module_t* module = ctx->module;
    free(ctx);
    return module;
}

void dso_error(struct elf_load_context_t* ctx, const char* msg)
{
    longjmp(ctx->error, (int) msg);
}

void dso_read_elf_header(struct elf_load_context_t* ctx, uint16_t type)
{
    if (fread(&ctx->ehdr, sizeof(Elf32_Ehdr), 1, ctx->file) != 1) {
        dso_error(ctx, "failed to read elf header");
    }

    printf("elf header:\n");
    printf("  magic:   %02x %02x %02x %02x\n",
           ctx->ehdr.e_ident[EI_MAG0],
           ctx->ehdr.e_ident[EI_MAG1],
           ctx->ehdr.e_ident[EI_MAG2],
           ctx->ehdr.e_ident[EI_MAG3]);
    printf("  class:   %d\n", ctx->ehdr.e_ident[EI_CLASS]);
    printf("  data:    %d\n", ctx->ehdr.e_ident[EI_DATA]);
    printf("  version: %d\n", ctx->ehdr.e_ident[EI_VERSION]);
    printf("  os/abi:  %d\n", ctx->ehdr.e_ident[EI_OSABI]);
    printf("  type:    %d\n", ctx->ehdr.e_type);
    printf("  machine: %d\n", ctx->ehdr.e_machine);
    printf("  version: %ld\n", ctx->ehdr.e_version);
    printf("  entry:   0x%08lX\n", ctx->ehdr.e_entry);
    printf("  ph_offset: 0x%08lX\n", ctx->ehdr.e_phoff);
    printf("  sh_offset: 0x%08lX\n", ctx->ehdr.e_shoff);
    printf("  flags:   0x%08lX\n", ctx->ehdr.e_flags);
    printf("  eh_size: %d\n", ctx->ehdr.e_ehsize);
    printf("  ph_ent_size: %d\n", ctx->ehdr.e_phentsize);
    printf("  ph_num:  %d\n", ctx->ehdr.e_phnum);
    printf("  sh_ent_size: %d\n", ctx->ehdr.e_shentsize);
    printf("  sh_num:  %d\n", ctx->ehdr.e_shnum);
    printf("  sh_strndx: %d\n", ctx->ehdr.e_shstrndx);

    if (ctx->ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
        ctx->ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ctx->ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
        ctx->ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        dso_error(ctx, "not a valid elf file");
    }

    if(ctx->ehdr.e_ident[EI_CLASS] != ELFCLASS32) {
        dso_error(ctx, "only 32-bit elf files are supported");
    }

    if(ctx->ehdr.e_ident[EI_DATA] != ELFDATA2LSB) {
        dso_error(ctx, "only little-endian elf files are supported");
    }

    if(ctx->ehdr.e_ident[EI_VERSION] != EV_CURRENT) {
        dso_error(ctx, "unsupported elf version");
    }

    if(ctx->ehdr.e_ident[EI_OSABI] != ELFOSABI_NONE) {
        dso_error(ctx, "unsupported abi");
    }

    if (ctx->ehdr.e_type != type) {
        dso_error(ctx, "invalid type");
    }

    if (ctx->ehdr.e_machine != EM_MIPS) {
        dso_error(ctx, "unsupported architecture");
    }

    if(ctx->ehdr.e_shentsize != sizeof(Elf32_Shdr)) {
        dso_error(ctx, "invalid section header size");
    }
}

void dso_read_program_headers(struct elf_load_context_t* ctx)
{
    ctx->phdr = (Elf32_Phdr*) malloc(ctx->ehdr.e_phnum * sizeof(Elf32_Phdr));
    if (!ctx->phdr) {
        dso_error(ctx, "out of memory for program headers");
    }

    fseek(ctx->file, ctx->ehdr.e_phoff, SEEK_SET);
    if (fread(ctx->phdr, sizeof(Elf32_Phdr), ctx->ehdr.e_phnum, ctx->file) != ctx->ehdr.e_phnum) {
        dso_error(ctx, "failed to read program headers");
    }
}

void dso_read_section_headers(struct elf_load_context_t* ctx)
{
    ctx->shdr = (Elf32_Shdr*) malloc(ctx->ehdr.e_shnum * sizeof(Elf32_Shdr));
    if (!ctx->shdr) {
        dso_error(ctx, "out of memory for sections");
    }

    fseek(ctx->file, ctx->ehdr.e_shoff, SEEK_SET);
    if (fread(ctx->shdr, sizeof(Elf32_Shdr), ctx->ehdr.e_shnum, ctx->file) != ctx->ehdr.e_shnum) {
        dso_error(ctx, "failed to read section headers");
    }

    dso_allocate_extra_section(ctx, ctx->ehdr.e_shstrndx);
    ctx->shstrtab = (char*) ctx->shdr[ctx->ehdr.e_shstrndx].sh_addr;
}

void dso_print_program_headers(struct elf_load_context_t* ctx)
{
    printf("program headers\n");
    printf("##: type       flags      offset     vaddr      paddr      filesz     memsz      align\n");
    for(int i = 0; i < ctx->ehdr.e_phnum; i++) {
        Elf32_Phdr* phdr = &ctx->phdr[i];
        printf("%2d: %-10s 0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%02lX\n",
                i, 
                program_header_types[phdr->p_type < PT_NUM ? phdr->p_type : PT_NUM], 
                phdr->p_flags, 
                phdr->p_offset, 
                phdr->p_vaddr, 
                phdr->p_paddr, 
                phdr->p_filesz, 
                phdr->p_memsz, 
                phdr->p_align
        );
    }
}

void dso_print_section_headers(struct elf_load_context_t* ctx)
{
    printf("sections\n");
    printf("###: type           flags      offset     addr       size       addralign name\n");
    for (int i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        const char* section_name;
        if(section->sh_name != SHN_UNDEF) {
            section_name = &ctx->shstrtab[section->sh_name];
        } else {
            section_name = "<unnamed>";
        }

        printf("%3d: %-14s 0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%02lX      %s\n",
               i,
               section_types[section->sh_type < SHT_NUM ? section->sh_type : SHT_NUM],
               section->sh_flags,
               section->sh_offset,
               section->sh_addr,
               section->sh_size,
               section->sh_addralign,
               section_name
        );
    }
}

void dso_print_dynamic_tags(struct elf_load_context_t* ctx)
{
    printf("dynamic tags\n");
    printf("###: tag                          value\n");

    Elf32_Section dynamic_index = 0;
    if(dso_find_section_by_type(ctx, &dynamic_index, SHT_DYNAMIC) < 0) {
        dso_error(ctx, "failed to find dynamic section");
    }

    Elf32_Shdr* section = &ctx->shdr[dynamic_index];
    if(!(section->sh_flags & SHF_ALLOC) && !(section->sh_flags & SHF_EXTRA_ALLOCATION)) dso_error(ctx, "dynamic section is not allocated");
    if(section->sh_type != SHT_DYNAMIC) dso_error(ctx, "dynamic section is not of type SHT_DYNAMIC");

    Elf32_Dyn* dyn = (Elf32_Dyn*)section->sh_addr;
    int j = 0;
    for(; dyn->d_tag != DT_NULL; dyn++) {
        if(dyn->d_tag >= DT_MIPS_RLD_VERSION && dyn->d_tag <= DT_MIPS_RLD_MAP_REL) {
            printf("%3zu: %-28s 0x%08lX\n", j, mips_dynamic_tag_types[dyn->d_tag - DT_MIPS_RLD_VERSION], dyn->d_un.d_val);
        } else if(dyn->d_tag >= DT_NUM) {
            printf("%3zu: 0x%08lX                   0x%08lX\n", j, dyn->d_tag, dyn->d_un.d_val);
        } else {
            printf("%3zu: %-28s 0x%08lX\n", j, dynamic_tag_types[dyn->d_tag], dyn->d_un.d_val);
        }
        j++;
    }
}

void dso_allocate_module(struct elf_load_context_t* ctx, size_t extra)
{
    size_t module_size = 0;
    for(int i = 0; i < ctx->ehdr.e_phnum; i++) {
        Elf32_Phdr* phdr = &ctx->phdr[i];
        if(phdr->p_type == PT_LOAD) {
            if(phdr->p_paddr != phdr->p_vaddr) {
                dso_error(ctx, "virtual memory unsupported");
            }
            uintptr_t end = phdr->p_vaddr + phdr->p_memsz;
            if(module_size < end) {
                module_size = end;
            }
        }
    }

    module_size += extra;

    printf("module size: 0x%08X\n", module_size);
    ctx->module = dl_allocate_module(module_size);
    if(extra) {
        ctx->module->extra = ctx->module->base + module_size - extra;
    } else {
        ctx->module->extra = NULL;
    }
    if (!ctx->module) {
        dso_error(ctx, "failed to allocate module");
    }
    printf("module base allocated at %p extra at %p\n", ctx->module->base, ctx->module->extra);
}

void dso_read_module_sections(struct elf_load_context_t* ctx)
{
    for (int i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        if(section->sh_flags & SHF_ALLOC) {
            if(section->sh_addr + section->sh_size > ctx->module->size) {
                dso_error(ctx, "section extends beyond module size");
            }
            section->sh_addr = (Elf32_Addr) ctx->module->base + section->sh_addr;
            switch(section->sh_type) {
                case SHT_NOBITS:
                    memset((void*) section->sh_addr, 0, section->sh_size);
                break;
                default:
                    fseek(ctx->file, section->sh_offset, SEEK_SET);
                    if (fread((void*)section->sh_addr, 1, section->sh_size, ctx->file) != section->sh_size) {
                        dso_error(ctx, "failed to read section data");
                    }
                break;
            }
        }
    }
}

void dso_allocate_extra_section(struct elf_load_context_t* ctx, Elf32_Section index)
{
    Elf32_Shdr* section = &ctx->shdr[index];
    section->sh_flags |= SHF_EXTRA_ALLOCATION;
    section->sh_addr = (Elf32_Addr) malloc(section->sh_size);
    if (!section->sh_addr) {
        dso_error(ctx, "out of memory for section name tables");
    }

    fseek(ctx->file, section->sh_offset, SEEK_SET);
    if (fread((void*)section->sh_addr, 1, section->sh_size, ctx->file) != section->sh_size) {
        dso_error(ctx, "failed to read section name tables");
    }
}

void dso_free_extra_section(struct elf_load_context_t* ctx, Elf32_Section index)
{
    Elf32_Shdr* section = &ctx->shdr[index];
    if (section->sh_flags & SHF_EXTRA_ALLOCATION) {
        free((void*) section->sh_addr);
        section->sh_addr = 0;
    } else {
        dso_error(ctx, "section is not an extra allocation");
    }
}

void dso_free_extra_sections(struct elf_load_context_t* ctx)
{
    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section = &ctx->shdr[i];
        if (section->sh_flags & SHF_EXTRA_ALLOCATION) {
            free((void*) section->sh_addr);
            section->sh_addr = 0;
        }
    }
}

int dso_find_section_by_name(struct elf_load_context_t* ctx, Elf32_Section* section, const char* name)
{
    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section0 = &ctx->shdr[i];
        if(section0->sh_name == SHN_UNDEF) continue;
        const char* section_name = &ctx->shstrtab[section0->sh_name];
        if(!strcmp(section_name, name)) {
            if(section) *section = i;
            return 0;
        }
    }
    return -1;
}

int dso_find_section_by_type(struct elf_load_context_t* ctx, Elf32_Section* section, uint32_t type)
{
    for(Elf32_Section i = 0; i < ctx->ehdr.e_shnum; i++) {
        Elf32_Shdr* section0 = &ctx->shdr[i];
        if(section0->sh_type == type) {
            if(section) *section = i;
            return 0;
        }
    }
    return -1;
}

int dso_find_dynamic_tag(struct elf_load_context_t* ctx, Elf32_Dyn** tag, Elf32_Section dynamic, int type)
{
    Elf32_Shdr* section = &ctx->shdr[dynamic];
    if(!(section->sh_flags & SHF_ALLOC) && !(section->sh_flags & SHF_EXTRA_ALLOCATION)) return -2;
    if(section->sh_type != SHT_DYNAMIC) return -3;

    Elf32_Dyn* dyn = (Elf32_Dyn*)section->sh_addr;
    for(; dyn->d_tag != DT_NULL; dyn++) {
        if(dyn->d_tag == type) {
            if(tag) *tag = dyn;
            return 0;
        }
    }
    return -1;
}

int dso_count_dynamic_tags(struct elf_load_context_t* ctx, int type)
{
    Elf32_Section dynamic_index = 0;
    if(dso_find_section_by_type(ctx, &dynamic_index, SHT_DYNAMIC) < 0) {
        return -1;
    }

    Elf32_Shdr* section = &ctx->shdr[dynamic_index];
    if(!(section->sh_flags & SHF_ALLOC) && !(section->sh_flags & SHF_EXTRA_ALLOCATION)) return -2;
    if(section->sh_type != SHT_DYNAMIC) return -3;

    Elf32_Dyn* dyn = (Elf32_Dyn*)section->sh_addr;
    int count = 0;
    for(; dyn->d_tag != DT_NULL; dyn++) {
        if(dyn->d_tag == type) {
            count++;
        }
    }
    return count;
}