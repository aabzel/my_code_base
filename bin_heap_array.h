#ifndef __BINARY_MAX_HEAP_ARRAY_H
#define __BINARY_MAX_HEAP_ARRAY_H

#include "custom_type.h"

/*
 A Binary Max Heap implementation
 */

typedef struct xBinaryHeap_t {
    int length; //current amount of items
    int capacity; //max allowable amount of items
    int *array; // pointer to array in heap memory
} BinaryHeap_t;

bool bin_heap_init (BinaryHeap_t *binHeap, int amountOfItems);
bool heap_init (BinaryHeap_t *binHeap);
bool bin_heap_deinit (BinaryHeap_t *binHeap);
bool heap_insert_val (BinaryHeap_t *binHeap, int newVal, bool isMaxHeap);

int heap_peek (BinaryHeap_t *binHeap);
//bool is_min_bin_heap (BinaryHeap_t *binHeap);
//bool is_max_bin_heap (BinaryHeap_t *binHeap);
bool bin_heap_remove_val (BinaryHeap_t *binHeap, bool isMax, int val);
bool max_heap_insert_val (BinaryHeap_t *binHeap, int val);
bool min_heap_insert_val (BinaryHeap_t *binHeap, int val);
bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd);
bool bubble_up_val_min_heap (BinaryHeap_t *binHeap, int index);

int height_of_bin_heap (BinaryHeap_t *binHeap);
bool is_left_ch_exist (BinaryHeap_t *binHeap, int parInd);
bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd);

int get_perent_index (int childIndex);
int get_left_child_index (int parentIndex);
int get_rihgt_child_index (int parentIndex);

bool make_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap);
bool make_bin_heap_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int parentIndex);

bool bubble_up_val_max_heap (BinaryHeap_t *binHeap, int index);
bool bubble_down_val_max_heap (BinaryHeap_t *binHeap);
bool is_empty (BinaryHeap_t *binHeap);

int heap_find_max (BinaryHeap_t *binHeap);
int heap_find_min (BinaryHeap_t *binHeap);

int bin_heap_val_index_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int val);
bool is_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap);
bool is_val_in_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap, int val, int parentIdnex);

/* Forces the heap empty by setting length to zero */
void make_empty (BinaryHeap_t *binHeap);

int heap_pop (BinaryHeap_t *binHeap, bool isMaxHeap);
bool bubble_down_val_heap (BinaryHeap_t *binHeap, bool isMaxHeap);

//TOTO
//void make_max_heap (TreeNode_t * root) ;
//void init_node (TreeNode_t * Node, int val);
//bool delet_node_with (TreeNode_t **root, int val);
//bool delete_node_with_val (TreeNode_t *perent, TreeNode_t *child, int val, bool isLeft) ;

#endif /* __BINARY_MAX_HEAP_ARRAY_H */
