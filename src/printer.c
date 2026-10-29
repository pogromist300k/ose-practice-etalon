#include "printer.h"
#include "vga.h"

#define DIGITS_MAX 10
#define NIBBLES_MAX 8

static struct {
  size_t x;
  size_t y;
} cursor;

static void newline();
static void print_char_move_cursor(int c);
static void print_int(int num);
static void print_dec(unsigned num);
static void print_hex(unsigned num);
static void print_pointer(void* ptr);
static size_t fill_hex_buff(unsigned num, char* buff);
static bool specifier_handler(char spec, va_list* args);

void printer_init() {
  vga_clear_screen();
  cursor.x = cursor.y = 0;
}

void printer_init_color(VgaColor bg, VgaColor fg) {
  vga_set_color(bg, fg);
  printer_init();
}

//------------------------CURSOR (PUBLIC)-------------------------

void printer_set_cursor(size_t x, size_t y) {
  cursor.x = x % VGA_COLS;
  cursor.y = y % VGA_ROWS;
}

size_t printer_get_cursor_x() {
  return cursor.x;
}

size_t printer_get_cursor_y() {
  return cursor.y;
}

//------------------------PRINTF (PUBLIC)-------------------------

void printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

void vprintf(const char* fmt, va_list args) {
  size_t i = 0;
  char c;
  while (c = fmt[i++]) {
    if (c == '%')
      if (specifier_handler(fmt[i++], &args))
        continue;
      else
        return;
    print_char_move_cursor(c); 
  }
}

//-----------------------------CHARS------------------------------

static void newline() {
  if (cursor.y == VGA_ROWS - 1)
    vga_scroll_down();
  else
    cursor.y++;
  cursor.x = 0;
}

static void print_char_move_cursor(int c) {
  if (c == '\n')
    newline();
  else if (c == '\r')
    cursor.x = 0;
  else {
    vga_print_char(c, cursor.x, cursor.y);
      if (++cursor.x == VGA_COLS)
        newline();
  }
}

//----------------------------NUMBERS-----------------------------

static void print_int(int num) {
  if (num < 0)
    print_char_move_cursor('-');
  print_dec((num < 0) ? -(unsigned)num : (unsigned)num);
}

static void print_dec(unsigned num) {
  char buff[DIGITS_MAX];
  size_t i = DIGITS_MAX;
  do {
    buff[--i] = '0' + num % 10;
    num /= 10;
  } while (num);
  for (; i < DIGITS_MAX; i++)
    print_char_move_cursor(buff[i]);
}

static void print_hex(unsigned num) {
  char buff[NIBBLES_MAX];
  for (size_t i = fill_hex_buff(num, buff); i < NIBBLES_MAX; i++)
    print_char_move_cursor(buff[i]);
}

static void print_pointer(void* ptr) {
  char buff[NIBBLES_MAX] = {'0', '0', '0', '0', '0', '0', '0', '0'};
  print_char_move_cursor('0');
  print_char_move_cursor('x');
  fill_hex_buff((uintptr_t)ptr, buff);
  for (size_t i = 0; i < NIBBLES_MAX; i++)
    print_char_move_cursor(buff[i]);
}

static size_t fill_hex_buff(unsigned num, char* buff) {
  size_t i = NIBBLES_MAX;
  do {
    byte offset = num % 16;
    buff[--i] = offset < 10 ? '0' + offset : 'A' + offset - 10;
    num /= 16;
  } while(num);
  return i;
}

//---------------------------SPECIFIERS---------------------------

static bool specifier_handler(char spec, va_list* args) {
  switch(spec) {
    case 'd':
      print_int(va_arg(*args, int));
      return true;
    case 'u':
      print_dec(va_arg(*args, unsigned));
      return true;
    case 'x':
      print_hex(va_arg(*args, unsigned));
      return true;
    case 'p':
      print_pointer(va_arg(*args, void*));
      return true;
    case 'c':
      print_char_move_cursor(va_arg(*args, int));
      return true;
    case 's': {
      const char* s = va_arg(*args, char*);
      if (s == NULL)
        s = "(null)";
      for (size_t i = 0; s[i]; i++)
        print_char_move_cursor(s[i]);
      return true;
    }
    case '%':
      print_char_move_cursor('%');
      return true;
    default:
      print_char_move_cursor('%');
      print_char_move_cursor(spec);
      return false;
  }
}