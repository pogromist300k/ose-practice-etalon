NASM    = nasm
GCC     = gcc
LD      = ld
OBJCOPY = objcopy
QEMU    = qemu-system-i386

# Selectors: общие для ASM и C
CODE_SELECTOR = 0x08
DATA_SELECTOR = 0x10

# Какой тест собираем: src/tests/test_$(TEST).c
TEST = hello_world

SRC = src
TMP = .tmp

CFLAGS_COMMON = -I$(SRC) -std=c99 -m32 -ffreestanding -no-pie -fno-pie \
                -mno-sse -fno-stack-protector \
                -DCODE_SELECTOR=$(CODE_SELECTOR) -DDATA_SELECTOR=$(DATA_SELECTOR)
NASMFLAGS     = -f elf -dCODE_SELECTOR=$(CODE_SELECTOR) -dDATA_SELECTOR=$(DATA_SELECTOR)
LDFLAGS       = -m elf_i386 -T link.ld

ifeq ($(MAKECMDGOALS),debug)
  CFLAGS    = $(CFLAGS_COMMON) -O0 -g -DDEBUG_MODE
  QEMUFLAGS = -cpu pentium2 -m 1g -fda boot.img -monitor stdio -device VGA -s -S
else
  CFLAGS    = $(CFLAGS_COMMON) -O2
  QEMUFLAGS = -cpu pentium2 -m 1g -fda boot.img -monitor stdio -device VGA
endif

HDRS     = $(wildcard $(SRC)/*.h)
C_SRCS   = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/tests/test_$(TEST).c)
ASM_SRCS = $(filter-out $(SRC)/boot.asm,$(wildcard $(SRC)/*.asm)) \
           $(wildcard $(SRC)/tests/test_$(TEST).asm)

C_OBJS   = $(patsubst $(SRC)/%.c,$(TMP)/%.o,$(C_SRCS))
ASM_OBJS = $(patsubst $(SRC)/%.asm,$(TMP)/asm/%.o,$(ASM_SRCS))

VBR_OBJ = $(TMP)/boot.o
OS_ELF  = $(TMP)/os.elf
OS_BIN  = $(TMP)/os.bin
IMAGE   = boot.img

all: $(IMAGE)

$(IMAGE): $(OS_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$< of=$@ conv=notrunc

$(OS_BIN): $(OS_ELF)
	$(OBJCOPY) -I elf32-i386 -O binary $< $@

$(OS_ELF): $(VBR_OBJ) $(C_OBJS) $(ASM_OBJS) link.ld
	$(LD) $(LDFLAGS) $(VBR_OBJ) $(C_OBJS) $(ASM_OBJS) -o $@

$(VBR_OBJ): $(SRC)/boot.asm $(C_OBJS) $(ASM_OBJS)
	@mkdir -p $(TMP)
	$(NASM) $(NASMFLAGS) -dN=$$(cat $(C_OBJS) $(ASM_OBJS) | wc -c) $< -o $@

$(TMP)/%.o: $(SRC)/%.c $(HDRS)
	@mkdir -p $(@D)
	$(GCC) $(CFLAGS) -c $< -o $@

$(TMP)/asm/%.o: $(SRC)/%.asm
	@mkdir -p $(@D)
	$(NASM) $(NASMFLAGS) $< -o $@

test debug: $(IMAGE)
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -f *.img
	rm -rf $(TMP)

.PHONY: all test debug clean
