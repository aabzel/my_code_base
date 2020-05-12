#ifndef __LINKED_LIST_OF_ARRAYS_H
#define __LINKED_LIST_OF_ARRAYS_H
//https://leetcode.com/tag/linked-list/
#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

#include "array_type.h"
#include "linked_list_types.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

#if 0
typedef struct xListNode {
    int val;
    struct xListNode *next;
} ListNode;
#endif

bool push_val (list_node_t **pInHead, int newVal);
void show_list (list_node_t* headNode);

#if 0
bool linked_list_deinit (list_node_t *pInHead);
bool linked_list_add_array (list_node_t **pInHead, int *inArr, int arrSize);
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize);
bool delete_node (ListNode* node);
ListNode* middle_node (ListNode* head);
void print_array_to_file (FILE * filePointer, int *array, int size);
// reverse list
void print_list (list_node_t *pHead);
int list_num_of_elements (list_node_t *pHead);
int list_num_of_data_byte (list_node_t *pHead);
list_node_t *get_node_by_index (list_node_t *pHead, int desInd);
list_node_t* sortList (list_node_t* head);

list_node_t *list_get_elem_by_index (int index);
void save_list_to_file (list_node_t *pInHead, char *filename);

void show_list (ListNode* headNode);
void list_add_node_front (ListNode** headNode, int new_data);
ListNode* reverseList (ListNode* head);
void reverse_rec (ListNode** head);
#endif



#if 0

void init_list (void);
void list_print_fwd (void);
void list_print_reverse (void);
void list_print_rev (list_node_t *pHead);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __LINKED_LIST_OF_ARRAYS_H */
