#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

#@echo $(error PROJECT_ROOT= $(PROJECT_ROOT))
#SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))

#@echo $(error SRC_PATH=$(SRC_PATH))

#CC=clang           

#all: main.c
#	clang  main.c -o hello
    
# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
  
#files to link:
LFLAGS =
  
# the name to use for both the target source file, and the output file:
TARGET = main
  
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).exe $(TARGET).c $(LFLAGS) 
