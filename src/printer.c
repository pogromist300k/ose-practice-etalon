#include "printer.h"
#include "string.h"
#include "mem.h"

#define WIDTH_MAX 256

typedef struct {
  const char* prefix;
  const char* digits;
  size_t width;
  bool zeros;
  bool left_align;
} PrintNumParams;

static struct {
  size_t x;
  size_t y;
} cursor;

static void newline();
static void print_char_move_cursor(char c);
static void print_str(const char* s);
static void print_num(const PrintNumParams* p);

void printer_init() {
  vga_clear_screen();
  cursor.x = cursor.y = 0;
}

void printer_init_color(VgaColor bg, VgaColor fg) {
  vga_set_color(bg, fg);
  printer_init();
}

//---------------------------- PRINTF ----------------------------

void printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

void vprintf(const char* fmt, va_list args) {
  char c;

  for (size_t i = 0; (c = fmt[i]); i++) {

    if (c != '%') {
      print_char_move_cursor(c);
      continue; 
    }

    bool left_align = false;
    bool prefix     = false;
    bool zeros      = false;
    size_t width    = 0;

    for (c = fmt[++i]; c == '-' || c == '#' || c == '0'; c = fmt[++i]) {
      if (c == '-')
        left_align = true;
      else if (c == '#')
        prefix = true;
      else if (c == '0')
        zeros = true;
    }

    for (; '0' <= c && c <= '9'; c = fmt[++i])
      width = width*10 + (size_t)(c - '0');

    if (WIDTH_MAX < width)
      width = WIDTH_MAX;

    switch(c) {
      case 'd': {
        char digits[DIGITS_MAX_10 + 1];
        int num = va_arg(args, int);
        unsigned unum = (num < 0) ? -(unsigned)num : (unsigned)num;
        print_num(&(PrintNumParams){
          .prefix     = (num < 0) ? "-" : "",
          .digits     = uint_to_str(unum, digits, BASE_10),
          .width      = width,
          .zeros      = zeros,
          .left_align = left_align,
        });
        break;
      }
      case 'u': {
        char digits[DIGITS_MAX_10 + 1];
        print_num(&(PrintNumParams){
          .prefix     = "",
          .digits     = uint_to_str(va_arg(args, unsigned), digits, BASE_10),
          .width      = width,
          .zeros      = zeros,
          .left_align = left_align,
        });
        break;
      }
      case 'x': {
        char digits[DIGITS_MAX_16 + 1];
        print_num(&(PrintNumParams){
          .prefix     = (prefix) ? "0x" : "",
          .digits     = uint_to_str(va_arg(args, unsigned), digits, BASE_16),
          .width      = width,
          .zeros      = zeros,
          .left_align = left_align,
        });
        break;
      }
      case 'b': {
        char digits[DIGITS_MAX_2 + 1];
        print_num(&(PrintNumParams){
          .prefix     = (prefix) ? "0b" : "",
          .digits     = uint_to_str(va_arg(args, unsigned), digits, BASE_2),
          .width      = width,
          .zeros      = zeros,
          .left_align = left_align,
        });
        break;
      }
      case 'p': {
        char digits[2*DIGITS_PTR + 1];
        memset(digits, '0', DIGITS_PTR);
        uint_to_str((uintptr_t)va_arg(args, void*), &digits[DIGITS_PTR], BASE_16);
        print_num(&(PrintNumParams){
          .prefix     = "0x",
          .digits     = &digits[strlen(&digits[DIGITS_PTR])],
          .width      = width,
          .zeros      = false,
          .left_align = left_align,
        });
        break;
      }
      case 'c': {
        if (width == 0) {
          print_char_move_cursor(va_arg(args, int));
          break;
        }
        char buff[WIDTH_MAX + 1];
        memset(buff, ' ', width - 1);
        buff[width - 1] = va_arg(args, int);
        buff[width] = '\0';
        if (left_align)
          strrev(buff);
        print_str(buff);
        break;
      }
      case 's': {
        const char* s = va_arg(args, char*);
        if (s == NULL)
          s = "(null)";
        size_t sw = strlen(s);
        size_t fw = (width > sw) ? width - sw : 0;
        if (fw == 0) {
          print_str(s);
          break;
        }
        char filler[WIDTH_MAX + 1];
        memset(filler, ' ', fw);
        filler[fw] = '\0';
        if (left_align) {
          print_str(s);
          print_str(filler);
        } else {
          print_str(filler);
          print_str(s);
        }
        break;
      }
      case '%':
        print_char_move_cursor('%');
        break;
      default:
        print_char_move_cursor('%');
        print_char_move_cursor(c);
        return;
    }
  }
}

//---------------------------- CHARS -----------------------------

static void newline() {
  if (cursor.y == VGA_ROWS - 1)
    vga_scroll_down();
  else
    cursor.y++;
  cursor.x = 0;
}

static void print_char_move_cursor(char c) {
  if (c == '\n')
    newline();
  else if (c == '\r')
    cursor.x = 0;
  else {
    if (cursor.x == VGA_COLS)
      newline();
    vga_print_char(c, cursor.x++, cursor.y);
  }
}

static void print_str(const char* s) {
  for (; *s; s++)
    print_char_move_cursor(*s);
}

//--------------------------- NUMBERS ----------------------------

static void print_num(const PrintNumParams* params) {
  size_t pw = strlen(params->prefix);                              // prefix width
  size_t dw = strlen(params->digits);                              // digits width
  size_t tw = (params->width > pw + dw) ? params->width : pw + dw; // total  width
  size_t fw = tw - (pw + dw);                                      // filler width
  char buff[WIDTH_MAX + 1];
  buff[tw] = '\0';
  if (params->left_align) {
    memmove(buff, params->prefix, pw);
    memmove(&buff[pw], params->digits, dw);
    memset(&buff[pw + dw], ' ', fw);
  } else {
    size_t digits_i = tw - dw;
    memset(buff, (params->zeros) ? '0' : ' ', digits_i);
    memmove(&buff[digits_i], params->digits, dw);
    memmove((params->zeros) ? buff : &buff[digits_i - pw], params->prefix, pw);
  }
  print_str(buff);
}