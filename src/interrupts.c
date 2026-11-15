#include "def.h"
#include "allocator.h"
#include "string.h"
#include "cpu.h"
#include "panic.h"
#include "vector_pushers.h"

#define ID_NUM        256
#define ID_SIZE       8
#define IDT_ALIGNMENT 8

typedef enum {
  INTERRUPT_GATE = 0b110,
  TRAP_GATE      = 0b111
} Type;

typedef enum {
  LEVEL = 0b00
} PL;

#pragma pack(push, 1)

typedef struct {
  u16  offset_0_15  : 16;
  u16  selector     : 16;
  u8   reserved     :  5;
  u8   fixed_37_39  :  3;
  Type type         :  3;
  u8   D            :  1;
  u8   fixed_44     :  1;
  PL   DPL          :  2;
  u8   P            :  1;
  u16  offset_48_63 : 16;
} ID;

typedef struct {
  u16 limit : 16;
  u32 base  : 32;
} IDTD;

#pragma pack(pop)

typedef struct {
  u32 EDI;
  u32 ESI;
  u32 EBP;
  u32 ESP;
  u32 EBX;
  u32 EDX;
  u32 ECX;
  u32 EAX;
  u32 GS;
  u32 FS;
  u32 ES;
  u32 DS;
  u32 vector;
  u32 err_code;
  u32 EIP;
  u32 CS;
  u32 EFLAGS;
} Context;

static const char context_fmt[] = 
  " Unhandled interrupt #%u at %#06x:%#010x\n\n"
  " EAX | %#010x | EBX | %#010x | ECX | %#010x | EDX | %#010x\n"
  " ESP | %#010x | EBP | %#010x | ESI | %#010x | EDI | %#010x\n"
  " DS  | %#06x     | ES  | %#06x     | FS  | %#06x     | GS  | %#06x\n\n"
  " Error Code | %-s\n\n"
  " EFLAGS | %#034b";

void cpu_lidt(IDTD* idtd);

static bool has_err_code(u32 vector) {
  switch(vector) {
    case 8:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 17:
    case 21:
      return true;
    default:
      return false;
  }
}

void interrupt_handler(Context* ctx) {
  char err_code_str[DIGITS_MAX_10 + 1];
  kernel_panic(context_fmt, 
    ctx->vector, ctx->CS, ctx->EIP,
    ctx->EAX, ctx->EBX, ctx->ECX, ctx->EDX,
    ctx->ESP, ctx->EBP, ctx->ESI, ctx->EDI,
    ctx->DS, ctx->ES, ctx->FS, ctx->GS,
    (has_err_code(ctx->vector)) ? uint_to_str(ctx->err_code, err_code_str, BASE_10) : "None",
    ctx->EFLAGS
  );
}

void interrupts_init() {
  void(*pushers[ID_NUM])() = PUSHERS_ARR;
  ID* idt = malloc_undead(ID_NUM * ID_SIZE, IDT_ALIGNMENT);
  for (size_t i = 0; i < ID_NUM; i++) {
    idt[i] = (ID){
      .offset_0_15  = (u16)((uintptr_t)pushers[i]),
      .selector     = CODE_SELECTOR,
      .type         = INTERRUPT_GATE,
      .D            = 1,
      .DPL          = LEVEL,
      .P            = 1,
      .offset_48_63 = (u16)(((uintptr_t)pushers[i] >> 16)),
    };
  }
  cpu_lidt(&(IDTD){
    .limit = ID_NUM * ID_SIZE - 1,
    .base  = (u32)(uintptr_t)idt
  });
}