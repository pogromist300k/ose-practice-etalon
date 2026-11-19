#ifndef INCLUDE_GUARD_PIC_H
#define INCLUDE_GUARD_PIC_H

#include "def.h"

#define PIC_VECTORS 32

typedef enum {
  PIC_TIMER    = 0,
  PIC_KEYBOARD = 1,
} PicDevice;

void pic_init(bool AEOI);
void pic_EOI(PicDevice device);
void pic_enable(PicDevice device);
void pic_disable(PicDevice device);

#endif
