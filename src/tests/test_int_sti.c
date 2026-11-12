#include "printer.h"
#include "utils.h"
#include "cpu.h"
#include "interrupts.h"

void div_zero();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                            TEST: Set Interrupt Flag                            \n");
  printf("================================================================================\n");
  sleep(30);

  interrupts_init();
  printf(" sti()...");
  sleep(50);
  cpu_sti();
  cpu_halt();
}