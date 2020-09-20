#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)/obj
# the compiler to use
##CC = clang
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall 

OPT = -DHAS_PARSE_MK
OPT += -DTEST_FIFO
OPT += -DHAS_UTESTS
OPT += -DHAS_TEST_PARSE_MK
OPT += -DHAS_TEST_PARSE_C
         
         
#files to link:
LFLAGS=-lws2_32 -liphlpapi 
  
EXECUTABLE=parse_mk
# the name to use for both the target source file, and the output file:
#TARGET = main

SOURCES = $(SRC_PATH)/main.c
SOURCES += $(SRC_PATH)/utils.c
SOURCES += $(SRC_PATH)/helper.c
SOURCES += $(SRC_PATH)/mk_to_dot.c
SOURCES += $(SRC_PATH)/algorithms.c
SOURCES += $(SRC_PATH)/arrays.c
SOURCES += $(SRC_PATH)/arrays_test.c
SOURCES += $(SRC_PATH)/convert.c
SOURCES += $(SRC_PATH)/float_utils.c
SOURCES += $(SRC_PATH)/uTests.c
SOURCES += $(SRC_PATH)/fifo_index.c
SOURCES += $(SRC_PATH)/str_ops.c
SOURCES += $(SRC_PATH)/test_str_ops.c
SOURCES += $(SRC_PATH)/fifo_char.c
SOURCES += $(SRC_PATH)/test_fifo_char.c
SOURCES += $(SRC_PATH)/test_mk_2_dot.c


OBJECTS =$(SOURCES:.c=.o)

#@echo $(error OBJECTS= $(OBJECTS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPT) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) $(OPT)  -c $^  
	mv *.o $(SRC_PATH)
