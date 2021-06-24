MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#@echo $(error MK_PATH= $(MK_PATH))
 PROJECT_ROOT:= $(MK_PATH)../

INCDIR			+= -I$(PROJECT_ROOT)

BUILDDIR := $(PROJECT_ROOT)/Build

SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)obj
# the compiler to use
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  += -g
#CFLAGS += -Og
CFLAGS  += -O0
#CFLAGS  += -Wall
#CFLAGS  +=-pedantic
#CFLAGS += -ftime-report

OPT += -DHAS_UTESTS
         
#files to link:
LFLAGS= -static
  
EXECUTABLE=cpp_code_master.exe
include $(PROJECT_ROOT)math/math.mk
include $(PROJECT_ROOT)utils/utils.mk
include $(PROJECT_ROOT)tests/tests.mk
include $(PROJECT_ROOT)/leet_code/leet_code.mk
CPP_SOURCES += $(SRC_PATH)main_cpp.cpp


INCDIR := $(subst /cygdrive/c/,C:/, $(INCDIR))
OBJ_CPP := $(patsubst %.cpp, %.o, $(CPP_SOURCES))
OBJ_CPP := $(subst /cygdrive/c/,C:/, $(OBJ_CPP))
#@echo $(error OBJ=$(OBJ))


#@echo $(error STRANGE_BRA= $<)
#@echo $(error STRANGE_DOG=$@)
#@echo $(error STRANGE_LEFT=$<)

.PHONY:all

$(EXECUTABLE): $(OBJ_CPP)
	$(CC) $(OPT) $(CFLAGS) $(OBJ_CPP) $(LFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) $(OPT) -c $< -o $@ 
	#mv *.o $(SRC_PATH)

all: $(EXECUTABLE)

clean:
	rm -r $(EXECUTABLE) $(OBJ_CPP) 
