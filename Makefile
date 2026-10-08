# =============================================================================
# Инженерия операционных систем — Лабораторная №2
# =============================================================================

# --- Инструменты -------------------------------------------------------------

NASM    = nasm
GCC     = gcc
LD      = ld
OBJCOPY = objcopy
QEMU    = qemu-system-i386

NASMFLAGS    = -f elf
CFLAGS       = -std=c99 -m32 -O2 -ffreestanding -no-pie -fno-pie \
               -mno-sse -fno-stack-protector
LDFLAGS      = -m elf_i386 -T link.ld
OBJCOPYFLAGS = -I elf32-i386 -O binary
QEMUFLAGS    = -cpu pentium2 -m 1g -fda boot.img -monitor stdio -device VGA

# --- Пути --------------------------------------------------------------------

SRC     = src
TMP     = .tmp
LINKER  = link.ld

VBR_SRC    = $(SRC)/boot.asm
KERNEL_SRC = $(SRC)/kernel.c
VBR_OBJ    = $(TMP)/boot.o
KERNEL_OBJ = $(TMP)/kernel.o
OS_ELF     = $(TMP)/os.elf
OS_BIN     = $(TMP)/os.bin
IMAGE      = boot.img

# =============================================================================
# Сборка

all: build

# --- Объектные файлы ---------------------------------------------------------

$(VBR_OBJ): $(VBR_SRC) $(KERNEL_OBJ) | $(TMP)
	$(NASM) $(NASMFLAGS) -dN=$$(stat -c%s $(KERNEL_OBJ)) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC) | $(TMP)
	$(GCC) $(CFLAGS) -c $< -o $@

# --- Линковка и бинарь -------------------------------------------------------

$(OS_ELF): $(VBR_OBJ) $(KERNEL_OBJ) $(LINKER)
	$(LD) $(LDFLAGS) $(VBR_OBJ) $(KERNEL_OBJ) -o $@

$(OS_BIN): $(OS_ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# --- Образ дискеты -----------------------------------------------------------

$(IMAGE): $(OS_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(OS_BIN) of=$@ conv=notrunc

# --- Служебное ---------------------------------------------------------------

$(TMP):
	mkdir -p $(TMP)

clean:
	rm -f *.img
	rm -rf $(TMP)
	mkdir -p $(TMP)

build: $(IMAGE)

test: $(IMAGE)
	$(QEMU) $(QEMUFLAGS)

debug: $(IMAGE)
	$(QEMU) $(QEMUFLAGS) -s -S &
	sleep 1
	gdb

.PHONY: all build clean test debug
