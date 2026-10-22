#include "vga.h"
#include "mem.h"

#define VGA_START ((volatile word*)0x000B8000)

static word vga_color = 0x0F00;

void vga_set_color(VgaColor bg, VgaColor fg) {
  vga_color = bg << 12 | fg << 8;
}

void vga_clear_screen() {
  memsetw((void*)VGA_START, vga_color | ' ', VGA_ROWS*VGA_COLS);
}

void vga_print_char(int c, byte x, byte y) {
  *(VGA_START + y*VGA_COLS + x) = vga_color | (byte)c;
}

void vga_scroll_down() {
  memmove((void*)VGA_START, (void*)(VGA_START + VGA_COLS), 2*(VGA_ROWS - 1)*VGA_COLS);
  memsetw((void*)(VGA_START + (VGA_ROWS - 1)*VGA_COLS), vga_color | ' ', VGA_COLS);
}