#include "printer.h"
#include "utils.h"
#include "interrupts.h"

void div_zero();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                             TEST: Division By Zero                             \n");
  printf("================================================================================\n");
  sleep(30);

  interrupts_init();
  printf(" Let me divide by zero...");
  sleep(100);
  div_zero();
}