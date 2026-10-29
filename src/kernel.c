#include <stdarg.h>
#include "cpu.h"
#include "mem.h"
#include "vga.h"
#include "printer.h"
#include "allocator.h"
#include "panic.h"
#include "utils.h"

char username[] = "Irina";

void kernel_entry() {
  sleep(50);
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("  Hi, %s\n", username);
  sleep(50);
  printf("  Let's allocate!\n");
  for (size_t i = 1; true; i+=1000) {
    byte* ptr = malloc_undead(i, 4);
    if (ptr == NULL)
      break;
    sleep(15);
    printf("  %p\n", ptr);
  }
  sleep(50);
  kernel_panic("Allocation is unavailable: bad alignment or out of memory");
}