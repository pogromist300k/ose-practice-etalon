#ifndef INCLUDE_GUARD_PANIC_H
#define INCLUDE_GUARD_PANIC_H

#include <stdarg.h>
#include "types.h"

void kernel_panic(const char* fmt, ...);
void vkernel_panic(const char* fmt, va_list args);

#endif