EXEC=exec
SRCS=main.c

CC=gcc
CFLAGS=-pedantic -Wall -Wextra -O0 -g -std=c99 -MD -c -pg  
LDFLAGS= -pg
OBJS=$(SRCS:.c=.o)


gprof: clean all
	./$(EXEC)    
	gprof -b $(EXEC)
	

all: $(EXEC)

-include $(OBJS:.o=.d)

.c.o:
	$(CC) $(CFLAGS) -o $*.o $<

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(EXEC) $(OBJS) $(OBJS:.o=.d)
	rm -f gmon.out

.PHONY: all clean gprof
