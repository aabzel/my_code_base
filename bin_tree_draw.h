#ifndef __BINARY_TREE_DRAW_H
#define __BINARY_TREE_DRAW_H

#include "arrays.h"
#include "bin_tree.h"
#include "bin_heap_array.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

bool print_tree_to_file (TreeNode_t* root, char *fileName);

void print2DUtil (TreeNode_t *root, int space);
void print2D (TreeNode_t *root);
void bst_print_dot_null (unsigned long long int nodeAdddr, FILE* stream);
void bst_print_dot_aux (TreeNode_t* node, FILE* stream);
bool draw_bin_heap_in_file (BinaryHeap_t *binHeap, char *fileName);

#endif /* __BINARY_TREE_DRAW_H */
