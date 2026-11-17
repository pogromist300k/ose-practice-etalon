#include "vga.h"
#include "mem.h"

#define VGA_START ((word*)0x000B8000)

static word vga_color = 0x0F;

void vga_set_color(VgaColor bg, VgaColor fg) {
  vga_color = bg << 4 | fg;
}

void vga_clear_screen() {
  memsetw((void*)VGA_START, vga_color << 8 | ' ', VGA_ROWS*VGA_COLS);
}

void vga_print_char(byte c, size_t x, size_t y) {
  x %= VGA_COLS;
  y %= VGA_ROWS;
  *(VGA_START + y*VGA_COLS + x) = vga_color << 8 | c;
}

void vga_scroll_down() {
  memmove((void*)VGA_START, (void*)(VGA_START + VGA_COLS), 2*(VGA_ROWS-1)*VGA_COLS);
  memsetw((void*)(VGA_START + (VGA_ROWS-1)*VGA_COLS), vga_color << 8 | ' ', VGA_COLS);
}
