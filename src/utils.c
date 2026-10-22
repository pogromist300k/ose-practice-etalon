#include "utils.h"

#define CYCLES_PER_MS 65536

bool is_power_of_2(size_t num) {
  return num != 0 && (num & (num - 1)) == 0;
}

void spin_wait(size_t cycles);

void sleep(word ms) {
  spin_wait(ms * CYCLES_PER_MS);
}