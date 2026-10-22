#include "allocator.h"
#include "utils.h"
#include "mem.h"

static AllocError error;

static struct {
  byte* cur;
  byte* end;
} heap = {(byte*)0x00100000, (byte*)0x00400000};

static byte* align_up(byte* ptr, size_t a);

AllocError get_alloc_error() {
  return error;
}

void* malloc_undead(size_t size, size_t alignment) {
  if (!is_power_of_2(alignment)) {
    error = ALLOC_ERR_ALIGNMENT;
    return NULL;
  }
  byte* ptr = align_up(heap.cur, alignment);
  if (ptr && ptr < heap.end && size <= heap.end - ptr) {
    heap.cur = ptr + size;
    return (void*)ptr;
  }
  error = ALLOC_ERR_OOM;
  return NULL;
}

void* calloc_undead(size_t size, size_t alignment) {
  void* ptr = malloc_undead(size, alignment);
  if (ptr)
    memset(ptr, 0, size);
  return ptr;
}

static byte* align_up(byte* ptr, size_t a) {
  byte* aligned = (byte*)((uintptr_t)ptr & ~((uintptr_t)(a - 1)));
  if (aligned != ptr)
    aligned += a;
  return (byte*)aligned;
}