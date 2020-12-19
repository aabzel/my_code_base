#ifndef LINKED_LIST_OF_INTS_H
#define LINKED_LIST_OF_INTS_H

// https://leetcode.com/tag/linked-list/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct xListNode_t {
    int val;
    struct xListNode_t *next;
} ListNode_t;

int linked_list_counts (ListNode_t* head_node);

bool delete_node (ListNode_t** node);
struct xListNode_t* middle_node (struct xListNode_t* head);
bool list_add_node_front (ListNode_t** headNode, int new_data);

ListNode_t* is_data_exist_linked_list (ListNode_t* head_node, int data);
ListNode_t* reverse_list (ListNode_t* head);
bool linked_list_deinit(ListNode_t** head);

//debug
void print_list2 (ListNode_t* headNode);

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_OF_INTS_H */
