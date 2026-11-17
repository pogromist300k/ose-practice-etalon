#ifndef INCLUDE_GUARD_INTERRUPTS_H
#define INCLUDE_GUARD_INTERRUPTS_H

typedef enum {
  INTERRUPT_GATE = 0b110,
  TRAP_GATE      = 0b111
} GateType;

typedef enum {
  LEVEL = 0b00
} PL;

void interrupts_init(GateType type);

// TMPTMPTMPTMPTMPTMPTMPTMPTMPTMP
extern void(*timer_handler)();
extern void(*keyboard_handler)();

#endif
