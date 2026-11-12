#include "printer.h"

char world[] = "world";

void test() {
  printer_init_color(VGA_LIGHT_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                               TEST: Hello World                                \n");
  printf("================================================================================\n");
  printf("Hello, %8s%c\n", world, '!');
}