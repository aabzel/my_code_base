#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#@echo $(error MK_PATH= $(MK_PATH))
PROJECT_ROOT:= $(MK_PATH)../

INCDIR			+= -I$(PROJECT_ROOT)

APP_INPUT	= 1
APP_GUI		= 1
 
#PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
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
CFLAGS  += -g
#CFLAGS += -Og
CFLAGS  += -O0
CFLAGS  += -Wall
#CFLAGS  +=-pedantic
#CFLAGS += -ftime-report


OPT = -DHAS_TCP
OPT += -DHAS_TCP_CLIENT
OPT += -DHAS_UTESTS
OPT += -DTCP_CLIENT
OPT += -DHAS_CONVERT
OPT += -DHAS_LCD_TEST

#files to link:
LFLAGS += -static
LFLAGS += -lws2_32 -liphlpapi
  
EXECUTABLE=lcd_emulator
include $(PROJECT_ROOT)utils/utils.mk
include $(PROJECT_ROOT)tests/tests.mk
include $(PROJECT_ROOT)math/math.mk
include $(PROJECT_ROOT)/lib/lib.mk
include $(PROJECT_ROOT)/core/core.mk
include $(PROJECT_ROOT)/applications/applications.mk





 

SOURCES += $(SRC_PATH)tcp_client.c
SOURCES += $(SRC_PATH)win_utils.c
SOURCES += $(SRC_PATH)lcd_emulator_main.c

#OBJECTS =$(SOURCES:.c=.o) ???

OBJ := $(patsubst %.c, %.o, $(SOURCES))
#@echo $(error OBJECTS= $(OBJECTS))

.PHONY:all

all:$(OBJ) $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCDIR) $(OPT) -c $< -o $@ 
	#mv *.o $(SRC_PATH)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OPT) $(CFLAGS) $(INCDIR) $(OBJ) $(LFLAGS) -o $(EXECUTABLE).exe 

clean:
	rm -r $(EXECUTABLE) $(OBJ) 
