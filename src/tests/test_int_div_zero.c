#include "interrupts.h"
#include "printer.h"
#include "utils.h"

void div_zero();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                             TEST: Division By Zero                             \n");
  printf("================================================================================\n");

  interrupts_init(INTERRUPT_GATE);
  printf(" Let me divide by zero...");
  sleep_visual(10);
  div_zero();
}
