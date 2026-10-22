#ifndef INCLUDE_GUARD_MEM_H
#define INCLUDE_GUARD_MEM_H

#include "types.h"

void* memmove(void* dst, const void* src, size_t n);
void* memset(void* dst, int b, size_t n);
void* memsetw(void* dst, int w, size_t n);

#endif