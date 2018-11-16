SRCS=$(filter-out Makefile, $(wildcard *.c))
EXEC=$(SRCS:.c=)
CFLAGS=-g -Wall -Wextra -std=c11

all: $(EXEC)

clean :
	rm -Rf $(EXEC) *~ *.dSYM

