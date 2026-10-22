#ifndef INCLUDE_GUARD_PRINTER_H
#define INCLUDE_GUARD_PRINTER_H

#include <stdarg.h>
#include "types.h"
#include "vga.h"

void printer_set_cursor(byte x, byte y);
byte printer_get_cursor_x();
byte printer_get_cursor_y();
void printer_init();
void printer_init_color(VgaColor bg, VgaColor fg);
void printf(const char* fmt, ...);
void vprintf(const char* fmt, va_list args);

#endif