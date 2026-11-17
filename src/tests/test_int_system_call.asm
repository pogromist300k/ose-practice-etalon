[BITS 32]

[GLOBAL sys_call]
sys_call:
  mov  EAX, 0xAAAAAAAA
  mov  EBX, 0xBBBBBBBB
  mov  ECX, 0xCCCCCCCC
  mov  EDX, 0xDDDDDDDD
  int  228
  ret
