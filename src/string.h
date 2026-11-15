#ifndef INCLUDE_GUARD_STRING_H
#define INCLUDE_GUARD_STRING_H

#include "def.h"

#define BASE_2        2
#define BASE_10       10
#define BASE_16       16
#define DIGITS_MAX_2  32
#define DIGITS_MAX_10 10
#define DIGITS_MAX_16 8
#define DIGITS_PTR    8

size_t strlen(const char* str);
char* strrev(char* str);
char* uint_to_str(unsigned num, char* buff, byte base);

#endif