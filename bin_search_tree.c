#include "bin_search_tree.h"

#include "algorithms.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static bool is_bin_search_sub_tree (TreeNode_t * root, int *minVal, int *maxVal);

// Recursively inserts elements into binary search tree
void bst_insert (TreeNode_t ** tree, TreeNode_t * item) {
    if (NULL == (*tree)) {
        *tree = item;
        return;
    }
    if ((item->val) < ((*tree)->val)) {
        bst_insert (&(*tree)->left, item);
    } else if (item->val > (*tree)->val) {
        bst_insert (&(*tree)->right, item);
    }
    return;
}

void assemble_tree_from_array (TreeNode_t ** root, int *arr, int arraySize) {
    printf ("\n arraySize: %d\n", arraySize);
    for (int index = 0; index < arraySize; index++) {
        binary_tree_add_val (root, arr [index]);
    }
}

void binary_tree_add_val (TreeNode_t ** root, int val) {
    TreeNode_t *currNode = NULL;
    currNode = (TreeNode_t *) malloc (sizeof(TreeNode_t));
    if (NULL != currNode) {
        currNode->left = NULL;
        currNode->right = NULL;
        currNode->val = val;
        bst_insert (root, currNode);
    }
}

bool is_bin_search_tree (TreeNode_t * root) {
    bool res = true;
    if (root) {
        if (root->left) {
            if (!((root->left->val) < (root->val))) {
                return false;
            } else {
                res = is_bin_search_sub_tree (root->left, NULL, &root->val);
            }
        }
        if (root->right && (true == res)) {
            if (!((root->val) < (root->right->val))) {
                return false;
            } else {
                res = is_bin_search_sub_tree (root->right, &root->val, NULL);
            }
        }
    }
    return res;
}

static bool is_bin_search_sub_tree (TreeNode_t * root, int *minVal, int *maxVal) {
    bool res = true;
    if (root) {
        if (minVal) {
            if (!(*minVal < root->val)) {
                return false;
            }
        }
        if (maxVal) {
            if (!(root->val < *maxVal)) {
                return false;
            }
        }

        if (root->left) {
            if (!((root->left->val) < (root->val))) {
                return false;
            } else {
                res = is_bin_search_sub_tree (root->left, minVal, &(root->val));
            }
        }
        if (root->right && (true == res)) {
            if (!((root->val) < (root->right->val))) {
                return false;
            } else {
                res = is_bin_search_sub_tree (root->right, &(root->val), maxVal);
            }
        }
    }
    return res;
}

// Creates a binary search tree
void create_binary_search_tree (TreeNode_t ** root, int how_many_elements) {
    int number = 0, counter = 0;
    time_t t;
    srand ((unsigned) time (&t));
    for (counter = 1; counter <= how_many_elements; counter++) {
        number = rand () / 100;
        binary_tree_add_val (root, number);
    }
    printf ("\nThe binary search tree is: \n");
    print_inorder_traversal (*root);
}
