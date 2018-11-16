OBJDUMP=arm-none-eabi-objdump
CC=arm-none-eabi-gcc

SRCS=$(wildcard *.c) 
DUMP=$(SRCS:.c=.dump)

all: $(DUMP)

%dump: %c
	$(CC) -g -fomit-frame-pointer -Wall -Wextra -Wno-unused-variable -O0 -c -o $*o $<
	$(OBJDUMP) -dS $*o > $@


clean:
	$(RM) *.o* *.dump* *~

	
