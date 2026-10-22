[BITS 16]

%define CODE 0x0008
%define DATA 0x0010

;========================LOAD KERNEL========================

cli
mov CX, 1                    ; CH: cylinder number (C)  CL: sector number (S)
xor DH, DH                   ; DH: head number (H)      DL: drive number
mov AX, 0x07C0               ;
mov ES, AX                   ; ES:BX buffer
xor BX, BX                   ;
mov SI, (N + 511) / 512 + 1  ; SI == number of sectors to read + 1
mov SS, BX
mov SP, 0x7C00

next_sector:
  sub SI, 1
  jz  switch_pm
  mov AX, ES       ;
  add AX, 0x20     ; buffer += 512b
  mov ES, AX       ;
  inc CL
  cmp CL, 19
  jne read
    mov CL, 1      ; CH: cylinder number (C)  CL: sector number (S)
    add CH, DH
    btc DX, 8      ; DH: head number (H)      DL: drive number
read:
  mov AX, 0x0201   ; AH: 2 (read from drive)  AL: 1 (read one sector 512b)
  int 0x13         ; C == error happend
  jnc next_sector

error:
  jmp $

;=================SWITCH TO PROTECTED MODE==================

switch_pm:
lgdt [GDT_descriptor]

cld

mov EAX, CR0
bts EAX, 0
mov CR0, EAX

jmp CODE:next
next:

[BITS 32]

mov AX, DATA
mov DS, AX
mov ES, AX
mov SS, AX
mov FS, AX
mov GS, AX

[EXTERN kernel_entry]
call kernel_entry

;=================GLOBAL DESCRIPTORS TABLE==================

GDT_descriptor:
  dw 23
  dd GDT

align 8

GDT:
  dq 0
  dq 0x00CF9A000000FFFF
  dq 0x00CF92000000FFFF

;=========================UTILITIES=========================

[GLOBAL spin_wait]
; void spin_wait(size_t cycles)
spin_wait:
  mov  ecx, dword[esp + 4]
  test ecx, ecx
  jz  .ret
 .wait:
    pause
    loop .wait
 .ret:
  ret

;--------------------------MEMORY---------------------------

[GLOBAL memmove]
; void* memmove(void* dst, const void* src, size_t n)
memmove:
  push edi
  push esi
  mov  edi, dword[esp + 12]
  mov  esi, dword[esp + 16]
  mov  ecx, dword[esp + 20]
  push edi
  cmp  edi, esi
  jb  .move
  lea  edi, [edi + ecx - 1]
  lea  esi, [esi + ecx - 1]
  std
 .move:
  rep  movsb
  cld
  pop  eax
  pop  esi
  pop  edi
  ret

[GLOBAL memset]
; void* memset(void* dst, int b, size_t n)
memset:
  push edi
  mov  edi, dword[esp +  8]
  mov   al,  byte[esp + 12]
  mov  ecx, dword[esp + 16]
  push edi
  rep  stosb
  pop  eax
  pop  edi
  ret

[GLOBAL memsetw]
; void* memsetw(void* dst, int w, size_t n)
memsetw:
  push edi
  mov  edi, dword[esp +  8]
  mov   ax,  word[esp + 12]
  mov  ecx, dword[esp + 16]
  push edi
  rep  stosw
  pop  eax
  pop  edi
  ret

times 510-($-$$) db 0
dw 0xAA55