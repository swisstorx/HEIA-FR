EXEC=exec
SRCS=$(wildcard *.c)


# The lines below should not be modified
CC=gcc
CFLAGS=-pedantic -Wall -Wextra -O0 -std=c99 -g -MD -c
OBJDIR=.obj
OBJS= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))


.PHONY: all clean

all: $(OBJDIR)/ $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%o: %c
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/:
	mkdir -p $(OBJDIR)

-include $(OBJS:.o=.d)

clean:
	rm -Rf $(OBJDIR) $(EXEC) *.map *~

