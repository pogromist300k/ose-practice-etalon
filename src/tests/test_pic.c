#include "pic.h"
#include "interrupts.h"
#include "ports.h"
#include "cpu.h"
#include "printer.h"
#include "utils.h"

#define EXPERIMENT 1
#define AEOI       false

static unsigned count;

static void tmp_timer_handler() {}

static void tmp_keyboard_handler() {}

void test() {
  printer_init_color(VGA_LIGHT_MAGENTA, VGA_WHITE);
  printf("================================================================================\n");
  printf("                                TEST: PIC 8259 #%-2u                              \n", EXPERIMENT);
  printf("================================================================================\n");
  sleep_visual(50);

  timer_handler    = tmp_timer_handler;
  keyboard_handler = tmp_keyboard_handler;

  interrupts_init(INTERRUPT_GATE);

  pic_init(AEOI);
  pic_enable(PIC_TIMER);
  pic_enable(PIC_KEYBOARD);

  sti();
  endless_loop();
}
