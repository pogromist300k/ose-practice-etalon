[BITS 16]

xor AX, AX
mov SS, AX
mov SP, 0x7C00
mov BP, SP
mov AX, 0x07E0
mov DS, AX

sub SP, 4
mov dword[BP - 4], N
pop SI
pop CX            ; CX:SI == N bytes of kernel
add SI, 511
adc CX, 0
shrd SI, CX, 9    ; SI == ceil(N / 512)

inc SI
mov BX, -512
sub AX, 0x1000
mov ES, AX
xor DH, DH
push DX
push 1

next_sector:
  sub SI, 1
  jz  stop
  add BX, 512
  jnz continue
    mov AX, ES
    add AX, 0x1000
    mov ES, AX
continue:
  pop CX          ; CH: cylinder number (C)   CL: sector number (S)
  pop DX          ; DH: head number (H)       DL: drive number
  mov AX, 0x0201  ; AH: 2 (read from drive)   AL: 1 (read one sector 512b)
  inc CL
  cmp CL, 19
  jne read
    mov CL, 1
    add CH, DH
    btc DX, 8
read:
  push DX
  push CX
  int 0x13
  jnc next_sector

error:
  jmp error

stop:
  mov SP, BP
  jmp stop

times 510-($-$$) db 0
dw 0xAA55
