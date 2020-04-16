#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include "bin_tree.h"

#include "custom_type.h"

#include <stdio.h>
#include <stdint.h>

void bst_insert (TreeNode_t ** root, int val);
//void bst_delete (TreeNode_t ** root, int val);
TreeNode_t* bst_search (TreeNode_t* root, int val);
bool is_bst_contain (TreeNode_t* root, int val);
bool is_bin_search_tree (TreeNode_t * item);

#endif /* __BINARY_SEARCH_TREE_H */
