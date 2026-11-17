#include "interrupts.h"
#include "printer.h"
#include "utils.h"

void sys_call();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                              TEST: System Calling                              \n");
  printf("================================================================================\n");
  sleep_visual(50);

  interrupts_init(INTERRUPT_GATE);
  printf(" Let's make a system call...");
  sleep_visual(100);
  sys_call();
}
