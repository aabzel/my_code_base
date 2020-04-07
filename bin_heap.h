#ifndef __BINARY_MAX_HEAP_H
#define __BINARY_MAX_HEAP_H

#include "bin_tree.h"


//https://en.wikipedia.org/wiki/Binary_tree

typedef struct xBinHeap_t {
    unsigned int size; // Size of the allocated memory (in number of items)
    unsigned int count; // Count of the elements in the heap
    int *data; // Array with the elements
} xBinHeap_t;

TreeNode_t binMaxHeapRoot;

int pop_max (TreeNode_t *binMaxHeapRoot);
int get_max (TreeNode_t **binMaxHeapRoot);
bool swift_up (TreeNode_t *binMaxHeapRoot);
bool is_max_heap (TreeNode_t *binMaxHeapRoot);

//TOTO
TreeNode_t *get_last (TreeNode_t *binMaxHeapRoot);
void make_max_heap (TreeNode_t * root) ;
bool max_heap_insert (TreeNode_t **binMaxHeapRoot, int newVal);
void init_node (TreeNode_t * Node, int val);
bool delet_node_with (TreeNode_t **root, int val);
bool delete_node_with_val (TreeNode_t *perent, TreeNode_t *child, int val, bool isLeft) ;


#endif /* __BINARY_MAX_HEAP_H */
