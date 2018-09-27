# Copyright 2015 University of Applied Sciences Western Switzerland / Fribourg
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Project:	HEIA-FR / Embedded Systems 1+2 Laboratory
#
# Author: 	Daniel Gachet
# Date: 	16.09.2018
#

ifeq ($(OS),Windows_NT)
DEL=del /F /S /Q
MKDIR=mkdir
RMDIR=rmdir /S /Q
else
DEL=rm -Rf
MKDIR=mkdir -p
RMDIR=rm -Rf
endif

MYLIB=libbbb.a
SRCS=$(wildcard *.c) 
ASRC=$(wildcard *.S)

# The lines below should not be modified 
TOOLCHAIN=arm-none-eabi-
CC=$(TOOLCHAIN)gcc
AS=$(TOOLCHAIN)gcc
AR=$(TOOLCHAIN)ar
CFLAGS=-Wall -Wextra -c -mcpu=cortex-a8 -mfpu=vfpv3 -O0 -MD -std=gnu11 -g -I.
OBJDIR=.obj
OBJS= $(addprefix $(OBJDIR)/, $(ASRC:.S=.o) $(SRCS:.c=.o))

.PHONY: all clean install

all: $(OBJDIR) $(MYLIB)
	
$(MYLIB): $(OBJS)
	@echo "[ar] --> generate libbbb.a"
	@$(AR) rcs $@  $(OBJS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
$(OBJDIR)/%.o: %.S
	$(CC) $(CFLAGS) $< -o $@	

$(OBJDIR):
	$(MKDIR) $(OBJDIR)
 
-include $(OBJS:.o=.d)

clean:
	$(DEL) $(MYLIB) *.o *.a *.d *~
	$(RMDIR) $(OBJDIR)
