#ifndef INCLUDE_GUARD_ALLOCATOR_H
#define INCLUDE_GUARD_ALLOCATOR_H

#include "types.h"

void* malloc_undead(size_t size, size_t alignment);
void* calloc_undead(size_t size, size_t alignment);

#endif