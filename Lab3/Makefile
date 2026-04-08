ARMGNU ?= aarch64-linux-gnu-

CC = $(ARMGNU)gcc
AS = $(ARMGNU)as
LD = $(ARMGNU)ld
OBJCOPY = $(ARMGNU)objcopy


CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles -Isrc/include
ASMFLAGS = -Isrc/include


SRCDIR = src
BUILDDIR = build


C_SOURCES = $(wildcard $(SRCDIR)/*.c)
ASM_SOURCES = $(wildcard $(SRCDIR)/*.S)


OBJ_FILES = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%_c.o, $(C_SOURCES))
OBJ_FILES += $(patsubst $(SRCDIR)/%.S, $(BUILDDIR)/%_s.o, $(ASM_SOURCES))


all: clean kernel8.img run


kernel8.img: $(BUILDDIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BUILDDIR)/kernel8.elf kernel8.img


$(BUILDDIR)/kernel8.elf: $(SRCDIR)/linker.ld $(OBJ_FILES)
	$(LD) -T $(SRCDIR)/linker.ld -o $(BUILDDIR)/kernel8.elf $(OBJ_FILES)

$(BUILDDIR)/%_c.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILDDIR)/%_s.o: $(SRCDIR)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILDDIR) *.img
run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio 
run-debug:
	llvm-objdump -d --arch=arm64 build/kernel8.elf >> build/instr
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio -d int,unimp -D qemu.log
run-pty:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial pty