#ifndef INCLUDE_GUARD_VGA_H
#define INCLUDE_GUARD_VGA_H

#include "types.h"

#define VGA_ROWS 25
#define VGA_COLS 80

typedef enum {
  VGA_BLACK         = 0x0,
  VGA_BLUE          = 0x1,
  VGA_GREEN         = 0x2,
  VGA_CYAN          = 0x3,
  VGA_RED           = 0x4,
  VGA_MAGENTA       = 0x5,
  VGA_BROWN         = 0x6,
  VGA_GRAY          = 0x7,
  VGA_DARK_GRAY     = 0x8,
  VGA_LIGHT_BLUE    = 0x9,
  VGA_LIGHT_GREEN   = 0xA,
  VGA_LIGHT_CYAN    = 0xB,
  VGA_LIGHT_RED     = 0xC,
  VGA_LIGHT_MAGENTA = 0xD,
  VGA_YELLOW        = 0xE,
  VGA_WHITE         = 0xF
} VgaColor;

void vga_set_color(VgaColor bg, VgaColor fg);
void vga_clear_screen();
void vga_print_char(int c, byte x, byte y);
void vga_scroll_down();

#endif