#include "bin_search_tree.h"

#include "algorithms.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void bst_insert_ll (TreeNode_t **tree, TreeNode_t *item);
static bool is_bin_search_sub_tree (TreeNode_t *root, int *minVal, int *maxVal);

// Recursively inserts elements into binary search tree

void bst_insert (TreeNode_t **root, int val) {
    TreeNode_t *currNode = NULL;
    currNode = (TreeNode_t *)malloc (sizeof (TreeNode_t));
    if (NULL != currNode) {
        currNode->left = NULL;
        currNode->right = NULL;
        currNode->val = val;
        bst_insert_ll (root, currNode);
    }
}

bool is_bin_search_tree (TreeNode_t *root) {
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

static bool is_bin_search_sub_tree (TreeNode_t *root, int *minVal, int *maxVal) {
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

// Time:  O(h)
TreeNode_t *bst_search (TreeNode_t *root, int val) {
    TreeNode_t *retNode = NULL;
    TreeNode_t *cur = root;
    while (cur != NULL) {
        if (val == cur->val) {
            retNode = cur;
            return retNode;
        } else if (val < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return retNode;
}

bool is_bst_contain (TreeNode_t *root, int val) {
    // Iteratively search for val in t.
    TreeNode_t *cur = root;
    while (cur != NULL) {
        if (val == cur->val) {
            // We found the value we're looking for in cur.
            return true;
        } else if (val < cur->val) {
            /*
             * The value we're looking for is less than the value at cur, so we
             * branch left.
             */
            cur = cur->left;
        } else {
            /*
             * The value we're looking for is greater than or equal to the value at
             * cur, so we branch right.
             */
            cur = cur->right;
        }
    }
    /*
     * If we make it to a leaf node (i.e. cur is NULL), we didn't find what we
     * were looking for.
     */
    return false;
}

static void bst_insert_ll (TreeNode_t **tree, TreeNode_t *item) {
    if (NULL == (*tree)) {
        *tree = item;
        return;
    }
    if ((item->val) < ((*tree)->val)) {
        bst_insert_ll (&(*tree)->left, item);
    } else if (item->val > (*tree)->val) {
        bst_insert_ll (&(*tree)->right, item);
    }
    return;
}
