#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)/obj
# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall 

OPT = -DDECRYPT_KEEPASS 
OPT += -DTEST_SHA256
OPT += -DTEST_ARRAY

#files to link:
LFLAGS=-lws2_32 -liphlpapi -lbcrypt
  
EXECUTABLE=keepass_decipher
# the name to use for both the target source file, and the output file:
#TARGET = main

SOURCES = $(SRC_PATH)/main.c 
SOURCES += $(SRC_PATH)/aes256.c 
SOURCES += $(SRC_PATH)/utils.c 
SOURCES += $(SRC_PATH)/helper.c 
SOURCES += $(SRC_PATH)/algorithms.c 
SOURCES += $(SRC_PATH)/arrays.c  
SOURCES += $(SRC_PATH)/arrays_test.c  
SOURCES += $(SRC_PATH)/convert.c  
SOURCES += $(SRC_PATH)/float_utils.c  
SOURCES += $(SRC_PATH)/uTests.c   
SOURCES += $(SRC_PATH)/str_ops.c
SOURCES += $(SRC_PATH)/test_str_ops.c    
SOURCES += $(SRC_PATH)/parse_keepass.c
SOURCES += $(SRC_PATH)/sha256.c
SOURCES += $(SRC_PATH)/sha256_test.c
SOURCES += $(SRC_PATH)/crypto-ms.c

OBJECTS =$(SOURCES:.c=.o)

#@echo $(error OBJECTS= $(OBJECTS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPT) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) $(OPT)  -c $^  
	mv *.o $(SRC_PATH)
