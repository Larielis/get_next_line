#include "custom_malloc.h"


static int malloc_counter = 0;
static int malloc_fail_after = 9;

void *custom_malloc(size_t size)
{
    malloc_counter++;
    if (malloc_counter > malloc_fail_after)
    {
        return NULL;
    }

    #undef malloc
    void *ptr = malloc(size);
    #define malloc custom_malloc

    return ptr;
}

