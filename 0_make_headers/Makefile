MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#@echo $(error MK_PATH= $(MK_PATH))
 PROJECT_ROOT:= $(MK_PATH)../

CFLAGS			+= -I$(PROJECT_ROOT)

BUILDDIR := $(PROJECT_ROOT)/Build




SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)obj
# the compiler to use
#CC = clang
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  += -g
#CFLAGS += -Og
CFLAGS  += -O0
CFLAGS  += -Wall
#CFLAGS  +=-pedantic
#CFLAGS += -ftime-report

#files to link:
LFLAGS= -static
  
EXECUTABLE=makeheaders
# the name to use for both the target source file, and the output file:
#TARGET = main

SOURCES = $(SRC_PATH)makeheaders.c
#SOURCES += $(SRC_PATH)uTests.c




OBJ := $(patsubst %.c, %.o, $(SOURCES))
#@echo $(error OBJECTS= $(OBJECTS))

.PHONY:all

all:$(OBJ) $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $(OPT) -c $< -o $@ 
	#mv *.o $(SRC_PATH)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OPT) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(EXECUTABLE).exe 

clean:
	rm -r $(EXECUTABLE) $(OBJ) 
