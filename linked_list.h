#ifndef __LINKED_LIST_OF_ARRAYS_H
#define __LINKED_LIST_OF_ARRAYS_H

#include <stdint.h>

#include "arrays.h"
#include "utils.h"
#include <stdio.h>

typedef struct xList_node_t {
    Array_t data;
    struct xList_node_t *nextNode;
} list_node_t;


void print_array_to_file (FILE * filePointer, int *array, int size);
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize);
// reverse list
void print_list (list_node_t *pHead);
bool linked_list_add_array (list_node_t **pInHead, int *inArr, int arrSize);
int list_num_of_elements (list_node_t *pHead);
int list_num_of_data_byte (list_node_t *pHead);
list_node_t *get_node_by_index (list_node_t *pHead, int desInd);

list_node_t *list_get_elem_by_index (int index);
bool linked_list_deinit (list_node_t *pInHead);
void save_list_to_file (list_node_t *pInHead, char *filename);

#if 0

void init_list (void);
void list_print_fwd (void);
void list_print_reverse (void);
void list_print_rev (list_node_t *pHead);

#endif

#endif /* __LINKED_LIST_OF_ARRAYS_H */
