;======================= LOAD KERNEL =======================

[BITS 16]

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

;================ SWITCH TO PROTECTED MODE =================

switch_pm:
lgdt [GDT_descriptor]

cld

mov EAX, CR0
bts EAX, 0
mov CR0, EAX

jmp CODE_SELECTOR:next
next:

[BITS 32]

mov AX, DATA_SELECTOR
mov DS, AX
mov ES, AX
mov SS, AX
mov FS, AX
mov GS, AX

[EXTERN kernel_entry]
; void kernel_entry()
call kernel_entry

;================ GLOBAL DESCRIPTORS TABLE =================

GDT_descriptor:
  dw 23
  dd GDT

align 8

GDT:
  dq 0
  dq 0x00CF9A000000FFFF
  dq 0x00CF92000000FFFF

;======================== UTILITIES ========================

[GLOBAL loop]
; void loop(size_t cycles)
loop:
  mov ECX, dword[ESP + 4]
  test ECX, ECX
  jz .ret
 .loop:
    loop .loop
 .ret:
  ret

[GLOBAL endless_loop]
; void endless_loop()
endless_loop:
  jmp endless_loop

;-------------------------- PORTS --------------------------

[GLOBAL in]
; byte in(word port)
in:
  mov DX, word[ESP + 4]
  in  AL, DX
  ret

[GLOBAL out]
; void out(word port, byte value)
out:
  mov DX, word[ESP + 4]
  mov AL, byte[ESP + 8]
  out DX, AL
  ret

;--------------------------- CPU ---------------------------

[GLOBAL cli]
; void cli()
cli:
  cli
  ret

[GLOBAL sti]
; void sti()
sti:
  sti
  ret

[GLOBAL halt]
; void hlt()
halt:
  cli
  hlt

;------------------------- MEMORY --------------------------

[GLOBAL memmove]
; void* memmove(void* dst, const void* src, size_t n)
memmove:
  push EDI
  push ESI
  mov  EDI, dword[ESP + 12]
  mov  ESI, dword[ESP + 16]
  mov  ECX, dword[ESP + 20]
  push EDI
  cmp  EDI, ESI
  jb  .move
  lea  EDI, [EDI + ECX - 1]
  lea  ESI, [ESI + ECX - 1]
  std
 .move:
  rep  movsb
  cld
  pop  EAX
  pop  ESI
  pop  EDI
  ret

[GLOBAL memset]
; void* memset(void* dst, int b, size_t n)
memset:
  push EDI
  mov  EDI, dword[ESP +  8]
  mov   AL,  byte[ESP + 12]
  mov  ECX, dword[ESP + 16]
  push EDI
  rep  stosb
  pop  EAX
  pop  EDI
  ret

[GLOBAL memsetw]
; void* memsetw(void* dst, int w, size_t n)
memsetw:
  push EDI
  mov  EDI, dword[ESP +  8]
  mov   AX,  word[ESP + 12]
  mov  ECX, dword[ESP + 16]
  push EDI
  rep  stosw
  pop  EAX
  pop  EDI
  ret

times 510-($-$$) db 0
dw 0xAA55
