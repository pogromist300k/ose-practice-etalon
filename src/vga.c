#include "vga.h"
#include "mem.h"

#define PLACE_SIZE 2
#define START      ((word*)0x000B8000)
#define ADDR(x, y) (START + (y)*VGA_COLS + x)

static word vga_color = 0x0F;

void vga_set_color(VgaColor bg, VgaColor fg) {
  vga_color = bg << 4 | fg;
}

void vga_clear_screen() {
  memsetw(START, vga_color << 8 | ' ', VGA_ROWS*VGA_COLS);
}

void vga_print_char(byte c, size_t x, size_t y) {
  *ADDR(x%VGA_COLS, y%VGA_ROWS) = vga_color << 8 | c;
}

void vga_scroll_down() {
  memmove(ADDR(0, 0), ADDR(0, 1), PLACE_SIZE*(VGA_ROWS-1)*VGA_COLS);
  memsetw(ADDR(0, VGA_ROWS-1), vga_color << 8 | ' ', VGA_COLS);
}
