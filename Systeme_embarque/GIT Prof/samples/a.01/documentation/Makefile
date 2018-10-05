EXEC=app
SRCS=$(wildcard ./src/*.c)
DOMAINS=infra domain2

EXTRACFLAGS+=-I./infra/figures
EXTRALFLAGS+=-linfra_figures -L./infra/figures/

EXTRACFLAGS+=-I./infra/math
EXTRALFLAGS+=-linfra_math -L./infra/math 


# The lines below should not be modified 
export CC=gcc
export CFLAGS =-Wall -Wextra -O1 -g -std=c99 -MD -I. -c 
OBJDIR=./.obj
OBJS= $(addprefix $(OBJDIR)/, $(subst ./src/, ,$(SRCS:.c=.o)))

.PHONY: all clean domains dox


$(OBJDIR)/%o: ./src/%c
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -o $@

all: domains $(OBJDIR) $(EXEC)

clean:
	@for dir in $(DOMAINS); do $(MAKE) -C $$dir $@; done
	@rm -f $(EXEC) $(OBJS) $(OBJS:.o=.d)
	@rm -Rf ./doc/html

domains:
	@for dir in $(DOMAINS); do $(MAKE) -C $$dir all; done

dox:
	doxygen ./doc/Doxyfile

$(OBJDIR)/:
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(EXTRALFLAGS) -o $@ 


