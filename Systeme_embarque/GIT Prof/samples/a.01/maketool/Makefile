EXEC=exec
SRCS=main.c mymathlib.c



#-----------------------

OBJS=$(SRCS:.c=.o)


CC=gcc
CFLAGS=-g -c -Wall -Wextra -O1 -std=c11 -MD

all: $(EXEC)

clean:
	rm -f $(EXEC)
	rm -f *.o *.d

install:
	echo "nothing to do"
	echo "source: $(SRCS)"
	echo "objects: $(OBJS)"

$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

-include $(OBJS:.o=.d)

.PHONY: all clean install
