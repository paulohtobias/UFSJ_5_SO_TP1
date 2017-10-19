#Main Makefile
CC := gcc
CFLAGS := -g -Wall -MMD

#Binary and Running
ifeq ($(OS),Windows_NT)
	OS := windows
	BIN := manager.exe
else
	OS := linux
	BIN := manager.out
endif

#Directories
IDIR := ./utils
SDIR := ./utils

ODIR := ./obj/$(OS)

#Paths
INCLUDE_PATHS = $(IDIR:%=-I%)

#Libraries
LIBS := 
#CFLAGS+= `pkg-config --cflags $(LIBS)`
#LIBRARIES = `pkg-config --libs $(LIBS)`

#Compilation line
COMPILE = $(CC) $(CFLAGS) $(INCLUDE_PATHS)

#FILEs
#---------------Source----------------#
SRCS = $(wildcard $(SDIR)/*.c) $(wildcard $(SDIR)/*/*.c)
#---------------Object----------------#
OBJS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)
#-------------Dependency--------------#
DEPS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.d)


PROCESSOS := commander manager reporter

all: $(OBJS) $(PROCESSOS)

# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(COMPILE) -c $< -o $@ $(LIBRARIES)

commander:
	$(MAKE) -C Commander $(COMANDO)

manager:
	$(MAKE) -C Manager $(COMANDO)

reporter:
	$(MAKE) -C Reporter $(COMANDO)

.PHONY : clean
clean: COMANDO+=clean
clean: all
	-rm $(BIN) $(OBJS) $(DEPS)

init:
	mkdir obj
	mkdir "obj/windows"
	mkdir "obj/linux"

run:
	./commander.out
