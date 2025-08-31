include ../../Makefile.variable
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(OBJS)

$(OBJS): $(SRCS)
	$(GCC_PRE)gcc $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)
