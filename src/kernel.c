#include <stdarg.h>
#include "cpu.h"
#include "mem.h"
#include "vga.h"
#include "printer.h"
#include "allocator.h"
#include "panic.h"
#include "utils.h"

void kernel_entry() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("Hi, %d\n", 42);
  cpu_halt();
}