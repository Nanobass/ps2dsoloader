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
    printf("adding dependency: %s -> %s; ", modulename(depender), modulename(provider));
    struct dependency_t* current = dependencies;
    while (current) {
        if (current->depender == depender && current->provider == provider) {
            current->count++;
            printf("count: %d\n", current->count);
            return 0;
        }
        current = current->next;
    }
    printf("allocated\n");

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
    printf("deleting dependency: %s -> %s; ", modulename(depender), modulename(provider));

    struct dependency_t* current = dependencies;
    struct dependency_t* previous = NULL;

    while (current) {
        if (current->depender == depender && current->provider == provider) {

            if(current->count > 1) {
                current->count--;
                printf("count: %d\n", current->count);
                return 0;
            }
            printf("deallocated\n");

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
                dl_free_module(current->provider);
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
            printf("deleting dependency: %s -> %s; count: %d\n", modulename(depender), modulename(current->provider), current->count);

            if (previous) {
                previous->next = current->next;
            } else {
                dependencies = current->next;
            }

            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}