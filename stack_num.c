#include "stack_num.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_indexer.h"

bool stack_init(numStack_t **stack_instance, int des_capacity) {
	bool res = false;
	(*stack_instance) = (numStack_t*) malloc(sizeof(numStack_t));
	if (NULL != (*stack_instance)) {
		(*stack_instance)->data_ptr = (int*) malloc(des_capacity * sizeof(int));
		if (NULL != (*stack_instance)->data_ptr) {
			(*stack_instance)->index.capacity = des_capacity;
			(*stack_instance)->index.pos = 0;
			(*stack_instance)->is_init = true;
			res = true;
		}
	}
	return res;
}

bool stack_realloc(numStack_t *stack_instance, int new_des_capacity) {
	bool res = false;
	if (stack_instance->index.capacity < new_des_capacity) {
        int *array = (int *) malloc (sizeof(int)*new_des_capacity );
        if(0<(stack_instance->index.pos)) {
            memcpy( array, stack_instance->data_ptr, sizeof(int)*(stack_instance->index.pos));
        }
        memset(stack_instance->data_ptr, 0x00, sizeof(int)*(stack_instance->index.capacity ));
        free(stack_instance->data_ptr);
        stack_instance->data_ptr = array;
        stack_instance->index.capacity = new_des_capacity;
        res = true;
	}
	return res;
}

bool stack_push(numStack_t *stack_instance, int data) {
	bool res = false;
	if (stack_instance) {
		res = true;
		bool temp_res = stack_indexer_is_full(&((stack_instance)->index));
		if (true == temp_res) {
			printf("\n stack_ is_full");
			int cur_cap = (stack_instance)->index.capacity;
			res = stack_realloc(stack_instance, cur_cap + (cur_cap / 2));
			if (false == res) {
				printf("\n stack_realloc error");
			}
		}
    	if (true == res) {
			(stack_instance)->data_ptr[(stack_instance)->index.pos] =
					data;
			res = stack_indexer_push(&((stack_instance)->index));
		}
	} else {
		printf("\n Error");
	}
	return res;
}

bool stack_pop(numStack_t *stack_instance, int *out_data) {
	bool res = false;
	int pos = stack_instance->index.pos;
	(*out_data) = stack_instance->data_ptr[pos-1];
	res = stack_indexer_pop(&(stack_instance->index));
	return res;
}

bool stack_peek(numStack_t *stack_instance, int *out_data) {
	bool res = false;
	int pos = stack_instance->index.pos;
	*out_data = stack_instance->data_ptr[pos];
	return res;
}

void stack_free(numStack_t *stack_instance) {
	if (stack_instance) {
		if (stack_instance->data_ptr) {
			free(stack_instance->data_ptr);
			stack_instance->data_ptr = NULL;
		}
		free(stack_instance);
		stack_instance = NULL;

	}
}

void stack_debug(numStack_t *stack_instance) {
	if (stack_instance) {
		printf("\n");
        for(int i=0; i<(stack_instance->index.pos);i++){
        	printf(" [%d]", stack_instance->data_ptr[i]);
        }
	}
}
