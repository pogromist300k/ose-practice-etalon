#include "printer.h"
#include "allocator.h"
#include "utils.h"

#define SIZE 1
#define ALIGNMENT 16
#define COUNT 2

void test() {
  printer_init_color(VGA_LIGHT_BLUE, VGA_WHITE);
  printf("================================================================================\n");
  printf("                             TEST: Allocation Basic                             \n");
  printf("================================================================================\n");
  sleep(30);

  byte* start = (byte*)malloc_undead(SIZE, ALIGNMENT);
  printf(" %p\n", start);
  for (size_t _ = 1; _ < COUNT; _++) {
    sleep(1);
    printf(" %p\n", malloc_undead(SIZE, ALIGNMENT));
  }
  byte* end = (byte*)malloc_undead(1, 1);
  size_t allocated = (size_t)(end - start);
  printf(" Bytes allocated: %u >= %u (%s)", allocated, COUNT * SIZE, allocated >= COUNT * SIZE ? "TRUE" : "FALSE");
}