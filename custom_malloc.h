// custom_malloc.h
#ifndef CUSTOM_MALLOC_H
#define CUSTOM_MALLOC_H

#include <stdlib.h>

void *custom_malloc(size_t size);

#define malloc(size) custom_malloc(size)

#endif // CUSTOM_MALLOC_H
