#ifndef INCLUDE_GUARD_ALLOCATOR_H
#define INCLUDE_GUARD_ALLOCATOR_H

#include "types.h"

typedef enum {
  ALLOC_ERR_ALIGNMENT,
  ALLOC_ERR_OOM
} AllocError;

void* malloc_undead(size_t size, size_t alignment);
void* calloc_undead(size_t size, size_t alignment);
AllocError get_alloc_error();

#endif