#include "printer.h"
#include "allocator.h"
#include "utils.h"

#define SIZE 1
#define START_ALIGNMENT 1
#define END_ALIGNMENT 2 << 19
#define BAD_ALIGNMENT 42

void test() {
  printer_init_color(VGA_LIGHT_BLUE, VGA_WHITE);
  printf("================================================================================\n");
  printf("                         TEST: Allocation Bad Alignment                         \n");
  printf("================================================================================\n");
  sleep(30);

  for (size_t a = START_ALIGNMENT; a <= END_ALIGNMENT; a *= 2) {
    printf(" Alignment: %-7u | Address: %#032b\n", a, (uintptr_t)malloc_undead(SIZE, a));
    sleep(5);
  }
  printf("\n Now triggering panic with bad alignment..."
         "\n   >> malloc_undead(%u, %u);", SIZE, BAD_ALIGNMENT);
  sleep(70);
  malloc_undead(SIZE, BAD_ALIGNMENT); 
}