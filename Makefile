include ./Makefile.variable

all: boot kern

boot:
	$(MAKE) -C $(BOOT_DIR)

kern:
	$(foreach makeFile,$(C_DIRS),$(MAKE) -C $(makeFile) all;)
	$(GCC_PRE)ld -nostdlib $(KERN_DIR)/kernel.o $(GPIO_DIR)/gpio.o $(GPU_DIR)/gpu.o $(MBOX_DIR)/mailbox.o $(UART_DIR)/uart.o $(MEM_DIR)/mem.o $(BOOT_DIR)/boot.o -T $(LD_FILE) -o $(ELF_OUT)
	$(GCC_PRE)objcopy -O binary $(ELF_OUT) $(KRN_IMG)

clean:
	$(foreach makeFile,$(C_DIRS),$(MAKE) --directory=$(makeFile) clean;)
	$(MAKE) -C $(BOOT_DIR) clean

run:
	qemu-system-aarch64 -M raspi3b -kernel $(KRN_IMG) -serial null -serial stdio
