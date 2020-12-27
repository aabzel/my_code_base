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
#CFLAGS  += -Og
CFLAGS  += -O0
CFLAGS  += -Wall
#CFLAGS  +=-pedantic
#CFLAGS += -ftime-report

VECTOR_CALC=Y 
HOTEL=Y 
 
OPT += -DHAS_UTESTS
OPT += -DTEST_ENCODE_STRING
OPT += -DTEST_LINKED_LIST
OPT += -DTEST_ARRAY
#OPT += -DHAS_HOTEL
OPT += -DTEST_STACK_NUM
OPT += -DHAS_ARRAY
OPT += -DHAS_ALGORITHMS
OPT += -DHAS_PERMUTATIONS_TEST
#OPT += -DHAS_EVAL_CACHE
#OPT += -DDEBUG_PERMUT
#OPT += -DTEST_CONVERT
#OPT += -DHAS_COMBINATIONS_TEST
#OPT += -DDEPLOY_DIF_SUB_STR_ERROR 
OPT += -DTEST_STR_STR 
#OPT += -DTEST_UNIQ_DIAG_PATH_TASK 
#OPT += -DTEST_MIN_PATH_DIAG 
#OPT += -DTEST_MIN_DIAG_SCALE_SUMM 
#OPT += -DTEST_UNIQ_PATH_TASK 
#OPT += -DTEST_UIO_COMB 
#OPT += -DTEST_YA_TASK 
#OPT += -DTEST_HEAP_CON 
#OPT += -DTEST_HEAP_SAME 
#OPT += -DBIN_HEAP_RAND_ADD 
#OPT += -DDEPLOY_TEST_AVL_TREE 
OPT += -DTEST_BIT_UTILS 
#OPT += -DHAS_VECTOR_CALC
         
#files to link:
LFLAGS= -static
  
EXECUTABLE=code_master
# the name to use for both the target source file, and the output file:
#TARGET = main

SOURCES = $(SRC_PATH)main.c

SOURCES += $(SRC_PATH)vector_calc.c
SOURCES += $(SRC_PATH)test_vector_calc.c

#@echo $(error VECTOR_CALC)
ifeq (,$(VECTOR_CALC),Y)
    @echo $(error VECTOR_CALC=$(VECTOR_CALC)) 
endif

ifeq (,$(HOTEL),Y)
     @echo $(error HOTEL=$(HOTEL)) 
endif

SOURCES += $(SRC_PATH)intervals.cpp
SOURCES += $(SRC_PATH)algorithms.c
SOURCES += $(SRC_PATH)algorithms_test.c
SOURCES += $(SRC_PATH)arrays.c
SOURCES += $(SRC_PATH)stack_indexer.c
SOURCES += $(SRC_PATH)stack_num.c
SOURCES += $(SRC_PATH)stack_str.c
SOURCES += $(SRC_PATH)hash_set.c
SOURCES += $(SRC_PATH)test_hash_set.c
SOURCES += $(SRC_PATH)test_stack_num.c
SOURCES += $(SRC_PATH)decode_string.c
#SOURCES += $(SRC_PATH)compiler_test.c
SOURCES += $(SRC_PATH)test_decode_string.c
SOURCES += $(SRC_PATH)decode_way.c
SOURCES += $(SRC_PATH)test_decode_way.c
#SOURCES += $(SRC_PATH)auriga_task.c
#SOURCES += $(SRC_PATH)evaluate_cache.c
SOURCES += $(SRC_PATH)bit_utils.c
SOURCES += $(SRC_PATH)test_hotel.c
SOURCES += $(SRC_PATH)hotel.c
SOURCES += $(SRC_PATH)check_address.c
SOURCES += $(SRC_PATH)bin_utils.c
SOURCES += $(SRC_PATH)bin_utils_test.c
SOURCES += $(SRC_PATH)compare_version.c
SOURCES += $(SRC_PATH)compare_version_test.c
SOURCES += $(SRC_PATH)convert.c
SOURCES += $(SRC_PATH)permutations.c
SOURCES += $(SRC_PATH)permutations_test.c
#SOURCES += $(SRC_PATH)combinations.c
#SOURCES += $(SRC_PATH)combinations_test.c
SOURCES += $(SRC_PATH)float_utils.c
SOURCES += $(SRC_PATH)fifo_index.c
SOURCES += $(SRC_PATH)fifo_char.c
SOURCES += $(SRC_PATH)helper.c
SOURCES += $(SRC_PATH)linked_list.c
#SOURCES += $(SRC_PATH)linked_list_array.c
SOURCES += $(SRC_PATH)test_linked_list.c
#SOURCES += $(SRC_PATH)validate_ip_address.c
#SOURCES += $(SRC_PATH)test_validate_ip_address.c
SOURCES += $(SRC_PATH)str_ops.c
#SOURCES += $(SRC_PATH)test_auriga_task.c
SOURCES += $(SRC_PATH)test_arrays.c
SOURCES += $(SRC_PATH)test_str_ops.c
SOURCES += $(SRC_PATH)test_algorithms.c
#SOURCES += $(SRC_PATH)test_evaluate_cache.c
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
