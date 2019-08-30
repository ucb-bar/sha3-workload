CC=riscv64-unknown-linux-gnu-gcc
OBJDUMP=riscv64-unknown-linux-gnu-objdump
OBJCOPY=riscv64-unknown-linux-gnu-objcopy
CFLAGS=-std=gnu99 -O2 -Wall
LDFLAGS=-static

PROGRAMS = sha3-rocc  sha3-sw

default: $(PROGRAMS)

dumps: $(addsuffix .dump,$(PROGRAMS))

%.o: %.S
	$(CC) $(CFLAGS) -D__ASSEMBLY__=1 -c $< -o $@

sha3-rocc.o: sha3-rocc.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o 
	$(CC) $(LDFLAGS) $< -o $@

%.dump: %
	$(OBJDUMP) -D $< > $@

clean:
	rm -f *.riscv *.o *.dump
