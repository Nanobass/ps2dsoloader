#include <dso-loader.h>

#include <stdlib.h>
#include <string.h>

struct dependency_t* dependencies = NULL;

int dl_add_dependency(struct module_t* depender, struct module_t* provider)
{
    struct dependency_t* dependency = (struct dependency_t*)malloc(sizeof(struct dependency_t));
    if (!dependency) {
        dl_raise("out of memory for dependency");
        return -1;
    }

    dependency->depender = depender;
    dependency->provider = provider;
    dependency->next = NULL;

    if (!dependencies) {
        dependencies = dependency;
    } else {
        struct dependency_t* current = dependencies;
        while (current->next) {
            current = current->next;
        }
        current->next = dependency;
    }

    return 0;
}

int dl_remove_dependency(struct module_t* depender, struct module_t* provider)
{
    struct dependency_t* current = dependencies;
    struct dependency_t* previous = NULL;

    while (current) {
        if (current->depender == depender && current->provider == provider) {

            printf("deleting dependency: %s -> %s\n", current->depender ? current->depender->name : "GLOBAL", current->provider ? current->provider->name : "GLOBAL");

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

    dl_raise("dependency not found");
    return -1;
}
