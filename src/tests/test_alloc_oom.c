#include "printer.h"
#include "allocator.h"
#include "utils.h"

#define SIZE       1488
#define ALIGNMENT  1
#define HEAP_START ((byte*)0x00100000)
#define HEAP_END   ((byte*)0x00400000)
#define HEAP_SIZE  (size_t)(HEAP_END - HEAP_START)

void test() {
  printer_init_color(VGA_LIGHT_BLUE, VGA_WHITE);
  printf("================================================================================\n");
  printf("                         TEST: Allocation Out of Memory                         \n");
  printf("================================================================================\n");
  sleep(30);

  size_t allocated = 0;
  while (allocated <= HEAP_SIZE - SIZE) {
    printf(" %p\n", malloc_undead(SIZE, ALIGNMENT));
    allocated += SIZE;
  }
  printf("\n Now triggering panic..."
         "\n   >> malloc_undead(%u, %u);", SIZE, ALIGNMENT);
  sleep(100);
  malloc_undead(SIZE, ALIGNMENT);
}