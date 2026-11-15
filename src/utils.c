#include "utils.h"

#define CYCLES_PER_MS (1 << 17)

void cpu_wait(size_t cycles);

void sleep(word ms) {
  if (0 < ms && ms < 1 << 15)
    cpu_wait(ms * CYCLES_PER_MS);
}

bool is_power_of_2(unsigned num) {
  return num != 0 && (num & (num - 1)) == 0;
}