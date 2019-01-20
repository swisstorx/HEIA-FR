OBJDUMP=arm-none-eabi-objdump
CC=arm-none-eabi-gcc

all:
	$(CC) -g -Wall -Wextra -O0 -std=c11 -c -o as2c.o0 as2c.c
	$(CC) -g -Wall -Wextra -O1 -std=c11 -c -o as2c.o1 as2c.c	
	$(CC) -g -Wall -Wextra -O2 -std=c11 -c -o as2c.o2 as2c.c			
	$(CC) -g -Wall -Wextra -O3 -std=c11 -c -o as2c.o3 as2c.c
	$(CC) -g -Wall -Wextra -Og -std=c11 -c -o as2c.og as2c.c
	$(OBJDUMP) -dS as2c.o0 > as2c.dump0
	$(OBJDUMP) -dS as2c.o1 > as2c.dump1
	$(OBJDUMP) -dS as2c.o2 > as2c.dump2
	$(OBJDUMP) -dS as2c.o3 > as2c.dump3
	$(OBJDUMP) -dS as2c.og > as2c.dumpg


clean:
	$(RM) *.o* *.dump* *~ 

	
