#ifndef INCLUDE_GUARD_CPU_H
#define INCLUDE_GUARD_CPU_H

static inline void cpu_cli() { 
  __asm__ volatile ("cli");
}

static inline void cpu_halt() {
  cpu_cli();
  __asm__ volatile ("1: hlt; jmp 1b");
}

#endif