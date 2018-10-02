ARCH=$(addsuffix .a, $(addprefix lib, $(notdir $(CURDIR))))

include $(LMIBASE)/bbb/make/bbb_tools.mk

.PHONY: all clean

OBJS=$(addprefix $(OBJDIR)/, $(ASRC:.S=.o) $(SRCS:.c=.o))

all: $(OBJDIR)/ $(EXTRA_ALL) $(ARCH) 

clean: $(EXTRA_CLEAN)
	rm -Rf $(ARCH) *~ $(EXTRAS)
	rm -Rf .obj
	
$(ARCH): $(OBJS) 
	$(AR) cr $@ $(OBJS)

$(OBJDIR)/:
	mkdir -p $(OBJDIR)

-include $(OBJS:.o=.d)

