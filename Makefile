PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC=gcc
LDFLAGS=

SOURCES = arrays.c  
SOURCES += permutations.c 
SOURCES += utils.c 
SOURCES += tcp_client.c
SOURCES += artificial_neural_network.c   
SOURCES += convert.c  
SOURCES += scan_serial_port.c
SOURCES += float_utils.c  
SOURCES += simulate_rocket_2d.c
SOURCES += math_model_rocket_2d.c
SOURCES += stream_averager.c  
SOURCES += test_stream_averager.c  
SOURCES += parse_regs.c
SOURCES += parse_tja1101_regs.c
SOURCES += parse_tic12400_regs.c
SOURCES += russian_doll_envelopes_test.c
SOURCES += russian_doll_envelopes.c
SOURCES += bin_tree_draw.c   
SOURCES += uTests.c   
SOURCES += min_path_diag_scale.c
SOURCES += str_ops.c
SOURCES += test_str_ops.c    
SOURCES += mk_to_dot.c
SOURCES += combinations.c
SOURCES += linked_list.c
SOURCES += algorithms.c 
SOURCES += main.c 
SOURCES += bin_tree.c 
SOURCES += hash_table.c
SOURCES += sort_linked_list.c
SOURCES += bin_heap.c 
SOURCES += bin_heap_array.c 
SOURCES += bin_search_tree.c 
SOURCES += amount_of_uio_states.c
SOURCES += min_path.c
SOURCES += fifo_index.c
SOURCES += fifo_char.c
SOURCES += fifo_uint16.c
SOURCES += lifo_char.c
SOURCES += avl_tree.c
SOURCES += test_fifo_char.c
SOURCES += test_lifo_char.c
SOURCES += test_avl_tree.c
#SOURCES += BinaryTreeInorderTraversal.c
#SOURCES += test_BinaryTreeInorderTraversal.c
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
	$(CC) -o $@ $^ -lws2_32

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
	