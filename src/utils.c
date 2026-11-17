#include "utils.h"
#include "printer.h"

#define CYCLES_PER_MS (1 << 17)

void sleep(word ms) {
  if (0 < ms && ms < 1 << 15)
    loop(ms * CYCLES_PER_MS);
}

void sleep_visual(word cycles) {
  for (word i = cycles; i > 0; i--) {
    sleep(1);
    printf(" %-5u", i);
    printer_set_cursor(printer_get_cursor_x() - 6, printer_get_cursor_y());
  }
  printf("  ");
  printer_set_cursor(printer_get_cursor_x() - 2, printer_get_cursor_y());
}

bool is_power_of_2(unsigned num) {
  return num != 0 && (num & (num - 1)) == 0;
}

unsigned bit_set(unsigned num, byte bit) {
  return num | (1 << bit);
}

unsigned bit_clear(unsigned num, byte bit) {
  return num & ~(1 << bit);
}
