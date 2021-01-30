
PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))


CC = g++
CFLAGS  = -g 
CFLAGS  += -Wall

LFLAGS= -static
OPT = -DHAS_UTESTS
OPT = -DBRICK_WALL

EXECUTABLE=code_master_cpp

SOURCES += $(SRC_PATH)brick_wall.cpp
SOURCES += $(SRC_PATH)test_brick_wall.cpp
SOURCES += $(SRC_PATH)intervals.cpp
SOURCES += $(SRC_PATH)main_cpp.cpp
SOURCES += $(SRC_PATH)u_tests.cpp
SOURCES += $(SRC_PATH)test_intervals.cpp


OBJECTS =$(SOURCES:.cpp=.o)

.PHONY : all clean
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPT) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) $(OPT) -c $^
	move "*.o" $(SRC_PATH)

clean:
	rm *.o *.exe
	 