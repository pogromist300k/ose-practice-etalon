[BITS 32]

[GLOBAL div_zero]
div_zero:
  mov  EAX, 0xAAAAAAAA
  mov  EBX, 0xBBBBBBBB
  mov  ECX, 0xCCCCCCCC
  mov  EDX, 0xDDDDDDDD
  push 0
  div  byte[ESP]
