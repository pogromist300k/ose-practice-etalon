#include "utils.h"
#include "printer.h"

#define CYCLES_PER_S 250000000

void loop(unsigned cycles);

void sleep(unsigned s) {
  while (s--)
    loop(CYCLES_PER_S);
}

void sleep_visual(unsigned s) {
  while (s) {
    printf(" %-5u", s--);
    loop(CYCLES_PER_S);
    cursor_set_x(cursor_x() - 6);
  }
  printf("  ");
  cursor_set_x(cursor_x() - 2);
}

bool is_power_of_2(unsigned num) {
  return num != 0 && (num & (num - 1)) == 0;
}

unsigned bit_set(unsigned num, byte bit) {
  return num | (1 << bit);
}

unsigned bit_reset(unsigned num, byte bit) {
  return num & ~(1 << bit);
}

unsigned bit_get(unsigned num, byte bit) {
  return (num >> bit) & 1;
}
