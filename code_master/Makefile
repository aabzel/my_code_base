#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)obj
# the compiler to use
#CC = clang
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g
CFLAGS  += -Wall
#CFLAGS += -ftime-report


OPT = -DTEST_FIFO
#OPT += -DDEBUG_RESULT
#OPT += -DHAS_AURIGA_TASK
OPT += -DHAS_UTESTS
OPT += -DHAS_ALGORITHMS
#OPT += -DHAS_PERMUTATION
#OPT += -DHAS_PERMUTATION_TEST
OPT += -DDEBUG_ASSEMBLE_FROM_ALPH
OPT += -DTEST_ARRAY
OPT += -DHAS_ARRAY
OPT += -DHAS_EVAL_CACHE
#OPT += -DDEBUG_PERMUT
OPT += -DTEST_CONVERT

#OPT += -DHAS_COMBINATIONS_TEST

         
#files to link:
LFLAGS= -static
  
EXECUTABLE=code_master
# the name to use for both the target source file, and the output file:
#TARGET = main

SOURCES = $(SRC_PATH)main.c

SOURCES += $(SRC_PATH)algorithms.c
SOURCES += $(SRC_PATH)algorithms_test.c
SOURCES += $(SRC_PATH)arrays.c
SOURCES += $(SRC_PATH)auriga_task.c
SOURCES += $(SRC_PATH)evaluate_cache.c
SOURCES += $(SRC_PATH)bit_utils.c
SOURCES += $(SRC_PATH)bin_utils.c
SOURCES += $(SRC_PATH)bin_utils_test.c
SOURCES += $(SRC_PATH)compare_version.c
SOURCES += $(SRC_PATH)compare_version_test.c
SOURCES += $(SRC_PATH)convert.c
#SOURCES += $(SRC_PATH)permutations.c
#SOURCES += $(SRC_PATH)permutations_test.c
#SOURCES += $(SRC_PATH)combinations.c
#SOURCES += $(SRC_PATH)combinations_test.c
SOURCES += $(SRC_PATH)float_utils.c
SOURCES += $(SRC_PATH)fifo_index.c
SOURCES += $(SRC_PATH)fifo_char.c
SOURCES += $(SRC_PATH)helper.c
SOURCES += $(SRC_PATH)linked_list.c
SOURCES += $(SRC_PATH)str_ops.c
SOURCES += $(SRC_PATH)test_auriga_task.c
SOURCES += $(SRC_PATH)test_arrays.c
SOURCES += $(SRC_PATH)test_str_ops.c
SOURCES += $(SRC_PATH)test_algorithms.c
SOURCES += $(SRC_PATH)test_evaluate_cache.c
SOURCES += $(SRC_PATH)test_convert.c
SOURCES += $(SRC_PATH)test_fifo_char.c
SOURCES += $(SRC_PATH)utils.c
SOURCES += $(SRC_PATH)uTests.c


OBJECTS =$(SOURCES:.c=.o)

#@echo $(error OBJECTS= $(OBJECTS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPT) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) $(OPT) -c $^
	move "*.o" $(SRC_PATH)
