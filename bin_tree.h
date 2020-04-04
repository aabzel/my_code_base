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

int height (TreeNode_t * node);
bool is_balanced (TreeNode_t * root);
void print_inorder_traversal (TreeNode_t * tree);
int find_size (TreeNode_t * tree, int curSize);
void print2DUtil (TreeNode_t *root, int space);
void print2D (TreeNode_t *root);
void bst_print_dot (TreeNode_t* tree, FILE* stream);
void bst_print_dot_null (int key, int nullcount, FILE* stream);
void bst_print_dot_aux (TreeNode_t* node, FILE* stream);
bool print_tree_to_file (TreeNode_t* root, char *fileName);
void binary_tree_add_val (TreeNode_t ** root, int val);
int deepestLeavesSum(TreeNode_t * root);
int calc_leaves_sum (TreeNode_t* root, int maxDepth);
#endif /* __BINARY_TREE_H */
