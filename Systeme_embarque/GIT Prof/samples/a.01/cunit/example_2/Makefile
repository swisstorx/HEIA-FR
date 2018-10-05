EXEC=exec
SRCS=main.c

CC=gcc

ifeq ($(host),linux)
CFLAGS=-pedantic -Wall -Wextra -O0 -g -std=c99 -MD -c -I/opt/local/include --coverage 
LDFLAGS= -lcunit -L/opt/local/lib --coverage
else
CFLAGS=-pedantic -Wall -Wextra -O0 -g -std=c99 -MD -c -I/Library/Developer/CommandLineTools/usr/include --coverage 
LDFLAGS= -lcunit -L/Library/Developer/CommandLineTools/usr/lib --coverage
endif

OBJS=$(SRCS:.c=.o)

gcov: clean all
	./$(EXEC)    >cunit_results.txt
	gcov $(SRCS) >gcov_results.txt
	
all: $(EXEC)

-include $(OBJS:.o=.d)

.c.o:
	$(CC) $(CFLAGS) -o $*.o $<

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(EXEC) $(OBJS) $(OBJS:.o=.d)
	rm -f *-Results.xml *.gc* *.txt

.PHONY: all clean gcov
