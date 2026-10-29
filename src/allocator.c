#include "allocator.h"
#include "utils.h"
#include "mem.h"
#include "panic.h"

static struct {
  byte* cur;
  byte* end;
} heap = {(byte*)0x00100000, (byte*)0x00400000};

static byte* align_up(size_t alignment);

void* malloc_undead(size_t size, size_t alignment) {
  if (!is_power_of_2(alignment))
    return NULL;
  byte* ptr = align_up(alignment);
  if (ptr == NULL || heap.end <= ptr || heap.end - ptr < size)
    return NULL;
  heap.cur = ptr + size;
  return (void*)ptr;
}

void* calloc_undead(size_t size, size_t alignment) {
  void* ptr = malloc_undead(size, alignment);
  if (ptr)
    memset(ptr, 0, size);
  return ptr;
}

static byte* align_up(size_t alignment) {
  byte* aligned = (byte*)((uintptr_t)heap.cur & ~((uintptr_t)(alignment - 1)));
  if (aligned != heap.cur)
    aligned += alignment;
  return (byte*)aligned;
}