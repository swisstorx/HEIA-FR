AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump

all:
	$(CC) -c main.c -o des.o2
	$(OBJDUMP) -Ds des.o2 > des.c.s

clean:
	rm -f *~ des.*

.PHONY:	clean all
