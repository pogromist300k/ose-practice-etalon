#include "interrupts.h"
#include "printer.h"
#include "utils.h"

void div_zero();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                             TEST: Division By Zero                             \n");
  printf("================================================================================\n");
  sleep_visual(50);

  interrupts_init(INTERRUPT_GATE);
  printf(" Let me divide by zero...");
  sleep_visual(100);
  div_zero();
}
