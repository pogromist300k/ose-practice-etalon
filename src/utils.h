#ifndef INCLUDE_GUARD_UTILS_H
#define INCLUDE_GUARD_UTILS_H

#include "def.h"

void endless_loop();
void loop(size_t cycles);
void sleep(word ms);
void sleep_visual(word cycles);
bool is_power_of_2(unsigned num);
unsigned bit_set(unsigned num, byte bit);
unsigned bit_clear(unsigned num, byte bit);

#endif
