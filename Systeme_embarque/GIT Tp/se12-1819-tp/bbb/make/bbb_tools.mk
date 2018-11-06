
ifeq ($(OS),Windows_NT)
DIRSEP=\\
LIBGCCPATH="c:/program files (x86)/gnu tools arm embedded/7 2018-q2-update/bin/../lib/gcc/arm-none-eabi/7.3.1"
else
DIRSEP=/
LIBGCCPATH=$(dir $(shell $(CC) -print-libgcc-file-name))
endif




ifeq ($(TARGET),HOST)
	CC=gcc
	LD=gcc
	CFLAGS+=-Wall -Wextra -g -c -O0 -MD -std=gnu11
	CFLAGS+=$(EXTRA_CFLAGS)
	OBJDIR=.obj$(DIRSEP)host
	EXE=$(EXEC)_h
else
	TOOLCHAIN=arm-none-eabi-
	CC=$(TOOLCHAIN)gcc
	AS=$(TOOLCHAIN)as
	LD=$(TOOLCHAIN)ld
	AR=$(TOOLCHAIN)ar
	CFLAGS+=-Wall -Wextra -g -c -O0 -MD -std=gnu11 
	CFLAGS+=-mlittle-endian -funsigned-char -mno-unaligned-access
	CFLAGS+=-mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -msoft-float
	CFLAGS+=-I$(LMIBASE)/bbb/source 
	CFLAGS+=$(addprefix -I./, $(EXTRADIRS)) $(addprefix -I./, $(LIBDIRS))
	CFLAGS+=$(EXTRA_CFLAGS)
	AFLAGS+=-mcpu=cortex-a8 -g 

	LDFLAGS+=--start-group $(addprefix -l, $(LIBDIRS)) -lbbb -lc -lgcc -lm --end-group
	LDFLAGS+= $(addprefix -L./, $(LIBDIRS)) 
	LDFLAGS+=-L$(LMIBASE)/bbb/source
	
	libgcc=$(shell $(CC) -print-libgcc-file-name)
	libgcc-dir= $(shell dirname $(realpath "$(ligbcc)"))

	LDFLAGS+=-L$(LIBGCCPATH)
	LDFLAGS+=-L"$(shell $(CC) -print-sysroot)"/lib 
	ifeq ($(PROCESS),)
		EXE=$(EXEC)_a
		LDFLAGS+=-T $(LMIBASE)/bbb/make/bbb.lds -Map $(EXE).map
	else
		EXE=$(EXEC)_p
		LDFLAGS+=-T $(LMIBASE)/bbb/make/bbb_process.lds -Map $(EXE).map
	endif

	OBJDIR=.obj$(DIRSEP)bbb
	OBJS+=$(addprefix $(OBJDIR)/, $(ASRC:.S=.o) $(SRCS:.c=.o))
	EXTRA_LIBS+=$(foreach dir,$(LIBDIRS), $(addprefix $(dir)/, $(addsuffix .a, $(addprefix lib, $(dir)))))
endif
export CFLAGS
export AFLAGS
export CC
export AS
export AR
export OBJDIR

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
$(OBJDIR)/%.o: %.S
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.s
	$(CC) $(CFLAGS) $< -o $@


