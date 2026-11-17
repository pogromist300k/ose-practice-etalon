#include "pic.h"
#include "ports.h"
#include "utils.h"

#define CMD_PORT_MASTER  0x20
#define CMD_PORT_SLAVE   0xA0
#define DATA_PORT_MASTER 0x21
#define DATA_PORT_SLAVE  0xA1
#define EOI              0x20
#define ICWS_NUM         4
#define ICW1             0b00010001
#define ICW2_MASTER      32
#define ICW2_SLAVE       40
#define ICW3_MASTER      0b00000100
#define ICW3_SLAVE       2
#define ICW4             0b00000001
#define ICW4_AEOI        0b00000011
#define DEVICES_NUM      8
#define DELAY_PORT       0x80
#define DELAY_CYCLES     100

static byte devices_master = 0xFF;
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
  byte icw4 = (AEOI) ? ICW4_AEOI : ICW4;
  byte icws_master[] = {ICW1, ICW2_MASTER, ICW3_MASTER, icw4};
  byte icws_slave[]  = {ICW1, ICW2_SLAVE,  ICW3_SLAVE,  icw4};
  init_command(CMD_PORT_MASTER, DATA_PORT_MASTER, icws_master);
  init_command(CMD_PORT_SLAVE,  DATA_PORT_SLAVE,  icws_slave);
  out(DATA_PORT_MASTER, devices_master);
  out(DATA_PORT_SLAVE,  devices_slave);
}

void pic_EOI(PicDevice device) {
  if (DEVICES_NUM <= device)
    out(CMD_PORT_SLAVE, EOI);
  out(CMD_PORT_MASTER, EOI);
}

static void device_switch(PicDevice device, unsigned(*bit_func)(unsigned, byte)) {
  if (device < DEVICES_NUM) {
    devices_master = (byte)bit_func(devices_master, device);
    out(DATA_PORT_MASTER, devices_master);
  }
  else {
    devices_slave = (byte)bit_func(devices_slave, device - DEVICES_NUM);
    out(DATA_PORT_SLAVE, devices_slave);
  }
}

void pic_enable(PicDevice device) {
  device_switch(device, bit_clear);
}

void pic_disable(PicDevice device) {
  device_switch(device, bit_set);
}
