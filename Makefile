PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

#CC=gcc
LDFLAGS=

SOURCES = arrays.c combinations.c str_ops.c uTests.c utils.c permutations.c linked_list.c
SOURCES += algorithms.c main.c 

EXECUTABLE=training

OBJECTS=$(SOURCES:.c=.o)


CFLAGS += -g -c
CFLAGS += -O2 -Werror -Wall -Wextra  
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
 

all: $(EXECUTABLE)

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) -o $@ $^

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
	
#.c.o:
#	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -fr $(EXECUTABLE) $(OBJECTS)
	
#test: blockAllocator	
#	./blockAllocator
	