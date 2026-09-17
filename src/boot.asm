[BITS 16]

xor AX, AX
mov SS, AX
mov SP, 0x7C00
mov AX, 0x07E0
mov DS, AX

sub AX, 0x20
mov ES, AX
xor BX, BX
mov CX, 1         
xor DH, DH       
mov SI, (N + 511) / 512 + 1  ; SI == number of sectors for read + 1 

next_sector:
  sub SI, 1
  jz  stop
  mov AX, ES
  add AX, 0x20
  mov ES, AX
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
  jmp error

stop:
  jmp stop

times 510-($-$$) db 0
dw 0xAA55
