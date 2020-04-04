#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <stdint.h>

#include "arrays.h"
#include "bin_tree.h"
#include "utils.h"
#include <stdio.h>

void insert (TreeNode_t ** tree, TreeNode_t * item);
void assemble_tree_from_array (TreeNode_t ** root, int *arr, int arraySize);
void create_binary_search_tree (TreeNode_t ** root, int how_many_elements);
void binary_tree_add_val (TreeNode_t ** root, int val);


#endif /* __BINARY_SEARCH_TREE_H */
