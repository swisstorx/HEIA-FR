SRCS=$(wildcard ./src/*.c)
##ARCH=libd2c2.a

# The lines below should not be modified 
##CC=gcc
##CFLAGS =-Wall -Wextra -O2 -g -std=c99 -MD -I. -c 
OBJDIR=./.obj
OBJS= $(addprefix $(OBJDIR)/, $(subst ./src/, ,$(SRCS:.c=.o)))


$(OBJDIR)/%o: ./src/%c
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -o $@

.PHONY: all clean

all: $(OBJDIR) $(ARCH)

$(ARCH): $(OBJS)
	$(AR) cr $@ $(OBJS) 

clean:
	@echo "(RM) $(OBJDIR) $(ARCH)"
	@rm -Rf $(OBJS) $(OBJS:.o=.d) $(ARCH)
	@rm -Rf $(OBJDIR)

$(OBJDIR)/:
	mkdir -p $(OBJDIR)

-include $(OBJS:.o=.d)
