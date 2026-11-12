#include "allocator.h"
#include "utils.h"
#include "mem.h"
#include "panic.h"

#define HEAP_START ((byte*)0x00100000)
#define HEAP_END   ((byte*)0x00400000)

static byte* heap = HEAP_START;

static const char bad_alignment_fmt[] = " Allocation failed: alignment %u is not a power of 2";
static const char oom_fmt[] = " Allocation failed: tried to allocate %u bytes, but only left %u bytes";

static byte* align_up(size_t alignment) {
  byte* aligned = (byte*)((uintptr_t)heap & (uintptr_t)-alignment);
  if (aligned != heap)
    aligned += alignment;
  return (byte*)aligned;
}

void* malloc_undead(size_t size, size_t alignment) {
  if (!is_power_of_2(alignment))
    kernel_panic(bad_alignment_fmt, alignment);
  byte* ptr = align_up(alignment);
  if (HEAP_END <= ptr || HEAP_END - ptr < size)
    kernel_panic(oom_fmt, size, HEAP_END <= ptr ? 0 : (uintptr_t)(HEAP_END - ptr));
  heap = ptr + size;
  return (void*)ptr;
}

void* calloc_undead(size_t size, size_t alignment) {
  void* ptr = malloc_undead(size, alignment);
  memset(ptr, 0, size);
  return ptr;
}