#include "printer.h"
#include "utils.h"
#include "interrupts.h"

void sys_call();

void test() {
  printer_init_color(VGA_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                              TEST: System Calling                              \n");
  printf("================================================================================\n");
  sleep(30);

  interrupts_init();
  printf(" Let's make a system call...");
  sleep(100);
  sys_call();
}