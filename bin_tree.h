#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#include <stdint.h>

#include "arrays.h"
#include "utils.h"
#include <stdio.h>

#define NOT_NUM (99999)
#define COUNT 10

typedef struct xTreeNode_t {
    int val;
    struct xTreeNode_t *left;
    struct xTreeNode_t *right;
} TreeNode_t;

extern int g_sum;
//how to parse array representation of binary tree from leetcode
//How to build an incomplete binary tree from array representation
//construct a binary tree described as array from leetcode  [1,2,3,4,5,null,6,7,null,null,null,null,8]
//How to generate binary tree dot file for Graphviz from C
void parse_bin_tree (int *arr, int size);
int get_parent_index (int nodeIndex, int size);
int max_depth (TreeNode_t* root);
void parse_bin_tree (int *arr, int size);
bool is_node_has_vacant (TreeNode_t * root);
void detele_tree (TreeNode_t * root);
TreeNode_t *get_first_spare_node (TreeNode_t * root);
int height (TreeNode_t * node);
bool is_balanced (TreeNode_t * root);
void print_inorder_traversal (TreeNode_t * tree);
int find_size (TreeNode_t * tree, int curSize);
int deepestLeavesSum (TreeNode_t * root);
int calc_leaves_sum (TreeNode_t* root, int maxDepth);
void init_node (TreeNode_t * Node, int val);
bool binary_tree_attace_node (TreeNode_t * NodePtr, int val, bool isleft);
bool binary_tree_add_node (TreeNode_t ** Node, int val);
TreeNode_t *get_first_spare_leaf_node (TreeNode_t * root) ;


#endif /* __BINARY_TREE_H */
