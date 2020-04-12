PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC=gcc
LDFLAGS=

SOURCES = arrays.c  
SOURCES += permutations.c 
SOURCES += utils.c  
SOURCES += bin_tree_draw.c   
SOURCES += uTests.c   
SOURCES += min_path_diag_scale.c
SOURCES += str_ops.c  
SOURCES += combinations.c
SOURCES += linked_list.c
SOURCES += algorithms.c main.c 
SOURCES += bin_tree.c 
SOURCES += bin_heap.c 
SOURCES += bin_heap_array.c 
SOURCES += bin_search_tree.c 
SOURCES += amount_of_uio_states.c
SOURCES += min_path.c
SOURCES += avl_tree.c
SOURCES += test_avl_tree.c
SOURCES += slidingWindowMid.c
SOURCES += slidingWindowMax.c

EXECUTABLE=training

OBJECTS=$(SOURCES:.c=.o)

CFLAGS = -O2
#CFLAGS += -g -c
CFLAGS += -Werror -Wall -Wextra  
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
 

all: $(EXECUTABLE)

	
$(EXECUTABLE):	$(OBJECTS)
	$(CC) -o $@ $^

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
	