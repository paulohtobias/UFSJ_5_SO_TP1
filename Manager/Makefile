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
IDIR := ./include ../utils
SDIR := ./src

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
OBJS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o) \
	$(patsubst ../utils/%.c,../obj/$(OS)/%.o,$(wildcard ../utils/*.c))
#-------------Dependency--------------#
DEPS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.d) \
	$(patsubst ../utils/%.c,../obj/$(OS)/%.d,$(wildcard ../utils/*.c))


all: $(OBJS)
	$(COMPILE) $(OBJS) main.c -o $(BIN) $(LIBRARIES)

# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(COMPILE) -c $< -o $@ $(LIBRARIES)

.PHONY : clean
clean :
	-rm $(BIN) $(OBJS) $(DEPS)

init:
	mkdir obj
	mkdir "obj/windows"
	mkdir "obj/linux"
	mkdir include
	mkdir src

run: all
	./$(BIN)
