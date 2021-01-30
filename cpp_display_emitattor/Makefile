
PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))

CC = "C:\cygwin64\bin\gcc.exe"
#CC = C:\cygwin64\bin\g++
#CC = clang
CFLAGS  =
#CFLAGS  = -g 
#CFLAGS  += -Wall
#CFLAGS  += -Wextra

#LFLAGS= -static
LFLAGS += -L"C:\1_lessons\C_programming_language\trainings\training\cpp_display_emitattor\CSFML-2.5-windows-64-bit\lib\gcc"
LFLAGS += -lcsfml-system 
LFLAGS += -lcsfml-window  
LFLAGS += -lcsfml-graphics 
LFLAGS += -I"C:\1_lessons\C_programming_language\trainings\training\cpp_display_emitattor\CSFML-2.5-windows-64-bit\include"
OPT =


EXECUTABLE=emulate_lcd

SOURCES += main.c
#SOURCES += $(SRC_PATH)u_tests.cpp



OBJECTS =$(SOURCES:.cpp=.o)

.PHONY : all clean
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPT) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) $(OPT) -c $^


clean:
	rm *.o *.exe
	 