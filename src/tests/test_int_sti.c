#include "interrupts.h"
#include "printer.h"
#include "utils.h"
#include "cpu.h"

void div_zero();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                            TEST: Set Interrupt Flag                            \n");
  printf("================================================================================\n");

  interrupts_init(INTERRUPT_GATE);
  printf(" sti()...");
  sleep_visual(10);
  sti();
  sleep_visual(10);
}
