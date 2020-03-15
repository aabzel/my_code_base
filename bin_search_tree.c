#include "bin_search_tree.h"

#include "algorithms.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Recursively inserts elements into binary search tree
void insert (TreeNode_t ** tree, TreeNode_t * item) {
    if (NULL == (*tree)) {
        *tree = item;
        return;
    }
    if ((item->val) < ((*tree)->val)) {
        insert (&(*tree)->left, item);
    } else if (item->val > (*tree)->val) {
        insert (&(*tree)->right, item);
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
        insert (root, currNode);
    }
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
