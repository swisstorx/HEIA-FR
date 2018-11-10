SRCS=$(filter-out Makefile, $(wildcard *.c))
EXEC=$(SRCS:.c=)
CFLAGS=-g -std=gnu11 

all: $(EXEC)

clean :
	rm -Rf $(EXEC) *~ *.dSYM

