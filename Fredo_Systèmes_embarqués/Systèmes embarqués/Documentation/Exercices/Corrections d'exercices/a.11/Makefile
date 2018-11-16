SRCS=$(filter-out Makefile, $(wildcard exer*.c))
EXEC=$(SRCS:.c=)
SRC2=hello.c nombre.c opp.c
OBJ2=$(SRC2:.c=.o)
EXE2=hello
CFLAGS=-g -Wall -Wextra -std=c99

all: $(EXEC) $(EXE2)

$(EXE2): $(OBJ2)



clean :
	rm -Rf $(EXEC) $(EXE2)
	rm -Rf *.o *~ *.dSYM

