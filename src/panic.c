#include "panic.h"
#include "printer.h"
#include "vga.h"
#include "cpu.h"

static const char panic_art[] =
  "     .--.\n"
  "    |o_o |\n"
  "    |:_/ |    _  _______ ____  _   _ _____ _      ____   _    _   _ ___ ____ _\n"
  "   //   \\ \\  | |/ / ____|  _ \\| \\ | | ____| |    |  _ \\ / \\  | \\ | |_ _/ ___| |\n"
  "  (|     | ) | ' /|  _| | |_) |  \\| |  _| | |    | |_) / _ \\ |  \\| || | |   | |\n"
  " /'\\_   _/`\\ | . \\| |___|  _ <| |\\  | |___| |___ |  __/ ___ \\| |\\  || | |___|_|\n"
  " \\___)=(___/ |_|\\_\\_____|_| \\_\\_| \\_|_____|_____||_| /_/   \\_\\_| \\_|___\\____(_)";

void kernel_panic(const char* fmt, ...) {
  cpu_cli();
  va_list args;
  va_start(args, fmt);
  vkernel_panic(fmt, args);
  va_end(args);
}

void vkernel_panic(const char* fmt, va_list args) {
  cpu_cli();
  
  printer_init_color(VGA_BLUE, VGA_WHITE);
  printf("%s\n\n ", panic_art);
  vprintf(fmt, args);
  cpu_halt();
}