include ../Makefile.variable

BOOT_SRC=boot.S
BOOT_OBJ=$(BOOT_SRC:.S=.o)

all: $(BOOT_OBJ)

$(BOOT_OBJ): $(BOOT_SRC)
	$(GCC_PRE)gcc $(CFLAGS) -c $(BOOT_SRC) -o $(BOOT_OBJ)

clean:
	rm $(BOOT_OBJ)
