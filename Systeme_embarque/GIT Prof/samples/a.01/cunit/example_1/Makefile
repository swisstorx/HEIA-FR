EXEC=exec
SRCS=main.c

CC=gcc
CFLAGS=-pedantic -Wall -Wextra -O2 -g -std=c99 -MD -c -I/opt/local/include
LDFLAGS= -lcunit -L/opt/local/lib
OBJS=$(SRCS:.c=.o)

cunit: clean all
	./$(EXEC)

all: $(EXEC)

-include $(OBJS:.o=.d)

.c.o:
	$(CC) $(CFLAGS) -o $*.o $<

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(EXEC) $(OBJS) $(OBJS:.o=.d) *~

.PHONY: cunit all clean	
