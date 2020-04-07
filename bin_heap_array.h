#ifndef __BINARY_MAX_HEAP_ARRAY_H
#define __BINARY_MAX_HEAP_ARRAY_H

#include "custom_type.h"

/*
 A Binary Max Heap implementation
 */

#define ARRAY_LIMIT 100

/* Binary Heap struct with a length and set length array */
typedef struct xBinaryHeap_t {
    int length;
    int array [ARRAY_LIMIT];
} BinaryHeap_t;

bool is_max_bin_heap (BinaryHeap_t *binHeap);
bool insert_val (BinaryHeap_t *binHeap, int val);

bool is_left_ch_exist (BinaryHeap_t *binHeap, int parInd);
bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd);
int get_perent_index (int childIndex);
int get_left_child_index (int parentIndex);
int get_rihgt_child_index (int parentIndex);
bool bubble_up_val_max_heap (BinaryHeap_t *binHeap, int index);

bool is_empty (BinaryHeap_t *binHeap);

int find_max (BinaryHeap_t *binHeap);

/* Forces the heap empty by setting length to zero */
void make_empty (BinaryHeap_t *bh);
int heap_pop_max (int *arr);
int heap_get_max (int *arr);
//bool heap_swift_up ();
bool is_max_heap_in_array (int *arr);

//TOTO
//TreeNode_t *get_last (TreeNode_t *binMaxHeapRoot);
//void make_max_heap (TreeNode_t * root) ;
//bool max_heap_insert (TreeNode_t **binMaxHeapRoot, int newVal);
//void init_node (TreeNode_t * Node, int val);
//bool delet_node_with (TreeNode_t **root, int val);
//bool delete_node_with_val (TreeNode_t *perent, TreeNode_t *child, int val, bool isLeft) ;

#endif /* __BINARY_MAX_HEAP_ARRAY_H */
