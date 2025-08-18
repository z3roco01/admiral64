SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
BOOT_SRC=boot.S
BOOT_OBJ=$(BOOT_SRC:.S=.o)

LD_FILE=linker.ld
ELF_OUT=kernel8.elf
KRN_IMG=kernel8.img

GCC_PRE=aarch64-none-elf-
CFLAGS=-Wall -O2 -ffreestanding -nostdlib -nostartfiles

all: clean kernel8.img

$(BOOT_OBJ): $(BOOT_SRC)
	$(GCC_PRE)gcc $(CFLAGS) -c $(BOOT_SRC) -o $(BOOT_OBJ)

%.o: %.c
	$(GCC_PRE)gcc $(CFLAGS) -c $< -o $@

kernel8.img: $(BOOT_OBJ) $(OBJS)
	$(GCC_PRE)ld -nostdlib $(BOOT_OBJ) $(OBJS) -T $(LD_FILE) -o $(ELF_OUT)
	$(GCC_PRE)objcopy -O binary $(ELF_OUT) $(KRN_IMG)

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3b -kernel $(KRN_IMG) -serial null -serial stdio
