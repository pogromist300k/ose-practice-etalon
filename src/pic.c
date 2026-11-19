#include "pic.h"
#include "ports.h"
#include "utils.h"

#define IRQS_NUM         8
#define IRQ_SLAVE        2
#define ICWS_NUM         4
#define ICW1             0x11
#define ICW2_MASTER      PIC_VECTORS
#define ICW2_SLAVE       (PIC_VECTORS + IRQS_NUM)
#define ICW3_MASTER      (1 << IRQ_SLAVE)
#define ICW3_SLAVE       IRQ_SLAVE
#define CMD_PORT_MASTER  0x20
#define CMD_PORT_SLAVE   0xA0
#define DATA_PORT_MASTER 0x21
#define DATA_PORT_SLAVE  0xA1
#define EOI              0x20
#define DELAY_PORT       0x80
#define DELAY_CYCLES     1337

static byte devices_master = 0xDF;
static byte devices_slave  = 0xFF;

static void init_command(word cmd_port, word data_port, const byte* icws) {
  out(cmd_port, icws[0]);
  for (size_t i = 1; i < ICWS_NUM; i++) {
    for (size_t _ = 0; _ < DELAY_CYCLES; _++)
      out(DELAY_PORT, 42);
    out(data_port, icws[i]);
  }
}

void pic_init(bool AEOI) {
  byte icw4 = 0x01 | ((AEOI) ? 0x02 : 0);
  byte icws_master[] = {ICW1, ICW2_MASTER, ICW3_MASTER, icw4};
  byte icws_slave[]  = {ICW1, ICW2_SLAVE,  ICW3_SLAVE,  icw4};
  init_command(CMD_PORT_MASTER, DATA_PORT_MASTER, icws_master);
  init_command(CMD_PORT_SLAVE,  DATA_PORT_SLAVE,  icws_slave);
  out(DATA_PORT_MASTER, devices_master);
  out(DATA_PORT_SLAVE,  devices_slave);
}

void pic_EOI(PicDevice device) {
  if (IRQS_NUM <= device)
    out(CMD_PORT_SLAVE, EOI);
  out(CMD_PORT_MASTER, EOI);
}

static void device_switch(PicDevice device, unsigned(*bit_func)(unsigned, byte)) {
  if (device < IRQS_NUM) {
    devices_master = (byte)bit_func(devices_master, device);
    out(DATA_PORT_MASTER, devices_master);
  }
  else {
    devices_slave = (byte)bit_func(devices_slave, device - IRQS_NUM);
    out(DATA_PORT_SLAVE, devices_slave);
  }
}

void pic_enable(PicDevice device) {
  device_switch(device, bit_reset);
}

void pic_disable(PicDevice device) {
  device_switch(device, bit_set);
}
