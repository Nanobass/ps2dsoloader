#include <dl.h>

#include <stdlib.h>
#include <string.h>

static struct dependency_t* dependencies = NULL, *dependencies_tail = NULL;

static const char* modulename(struct module_t* module) {
    if(!module) return "GLOBAL";
    if(!module->name) return "<unnamed>";
    return module->name;
}

int dl_add_dependency(struct module_t* depender, struct module_t* provider)
{
    dl_debug_printf(DL_DBG_DEPENDANCY, "adding dependency: %s -> %s; ", modulename(depender), modulename(provider));
    struct dependency_t* current = dependencies;
    while (current) {
        if (current->depender == depender && current->provider == provider) {
            current->count++;
            dl_debug_printf(DL_DBG_DEPENDANCY, "count: %d\n", current->count);
            return 0;
        }
        current = current->next;
    }
    dl_debug_printf(DL_DBG_DEPENDANCY, "allocated\n");

    struct dependency_t* dependency = (struct dependency_t*)malloc(sizeof(struct dependency_t));
    if (!dependency) {
        dl_raise("out of memory for dependency");
        return -1;
    }

    dependency->depender = depender;
    dependency->provider = provider;
    dependency->count = 1;
    dependency->next = NULL;

    if (!dependencies) {
        dependencies = dependency;
        dependencies_tail = dependency;
    } else {
        dependencies_tail->next = dependency;
        dependencies_tail = dependency;
    }

    return 0;
}

int dl_remove_dependency(struct module_t* depender, struct module_t* provider)
{
    dl_debug_printf(DL_DBG_DEPENDANCY, "deleting dependency: %s -> %s; ", modulename(depender), modulename(provider));

    struct dependency_t* current = dependencies;
    struct dependency_t* previous = NULL;

    while (current) {
        if (current->depender == depender && current->provider == provider) {

            if(current->count > 1) {
                current->count--;
                dl_debug_printf(DL_DBG_DEPENDANCY, "count: %d\n", current->count);
                return 0;
            }
            dl_debug_printf(DL_DBG_DEPENDANCY, "deallocated\n");

            if (previous) {
                previous->next = current->next;
            } else {
                dependencies = current->next;
            }

            int provider_count = 0;
            for(struct dependency_t* current_provider = dependencies; current_provider; current_provider = current_provider->next) {
                if (current_provider->provider == current->provider) provider_count++;
            }

            if (provider_count == 0) {
                // calls dl_remove_depender internally
                if(current->provider != NULL) dl_free_module(current->provider);
            }

            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

int dl_remove_depender(struct module_t* depender)
{
    struct dependency_t* current = dependencies;
    struct dependency_t* previous = NULL;

    while (current) {
        if (current->depender == depender) {
            dl_debug_printf(DL_DBG_DEPENDANCY, "deleting dependency: %s -> %s; deallocated count: %d\n", modulename(depender), modulename(current->provider), current->count);

            if (previous) {
                previous->next = current->next;
            } else {
                dependencies = current->next;
            }

            int provider_count = 0;
            for(struct dependency_t* current_provider = dependencies; current_provider; current_provider = current_provider->next) {
                if (current_provider->provider == current->provider) provider_count++;
            }

            if (provider_count == 0) {
                if(current->provider != NULL) dl_free_module(current->provider);
            }

            free(current);

            // current and previous may point to garbled data, because we call this recursivly
            // unfortunately, we have to iterate again
            current = dependencies;
        } else {
            previous = current;
            current = current->next;
        }
    }
    return -1;
}

void dl_print_dependencies() {
    struct dependency_t* current = dependencies;
    while (current) {
        dl_debug_printf(DL_DBG_DEPENDANCY, "dependency: %s -> %s; count: %d\n", modulename(current->depender), modulename(current->provider), current->count);
        current = current->next;
    }
}