#ifndef INCLUDE_GUARD_UTILS_H
#define INCLUDE_GUARD_UTILS_H

#include "def.h"

void endless_loop();
void sleep(unsigned s);
void sleep_visual(unsigned s);
bool is_power_of_2(unsigned num);
unsigned bit_set(unsigned num, byte bit);
unsigned bit_reset(unsigned num, byte bit);
unsigned bit_get(unsigned num, byte bit);

#endif
