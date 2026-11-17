#include "cpu.h"

void test();

void kernel_entry() {
  test();
  halt();
}
