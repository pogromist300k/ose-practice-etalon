#ifndef INCLUDE_GUARD_STRING_H
#define INCLUDE_GUARD_STRING_H

#include "defs.h"

size_t strlen(const char* str);
char* strrev(char* str);
char* uint_to_str(unsigned num, char* buff, byte base);

#endif