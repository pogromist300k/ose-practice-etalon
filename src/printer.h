#ifndef INCLUDE_GUARD_PRINTER_H
#define INCLUDE_GUARD_PRINTER_H

#include <stdarg.h>
#include "def.h"
#include "vga.h"

void printer_init();
void printer_init_color(VgaColor bg, VgaColor fg);
size_t cursor_x();
size_t cursor_y();
void cursor_set_x(size_t x);
void cursor_set_y(size_t y);
void printf(const char* fmt, ...);
void vprintf(const char* fmt, va_list args);

#endif
