#include "bin_heap.h"
#include "algorithms.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_max (TreeNode_t **binMaxHeapRoot) {
    int outVal = 0;
    if (NULL != (*binMaxHeapRoot)) {
        outVal = (*binMaxHeapRoot)->val;
        (*binMaxHeapRoot)->val = INT_MIN;
        make_max_heap (*binMaxHeapRoot);
        delet_node_with (binMaxHeapRoot, INT_MIN);
    }
    return outVal;
}

bool delete_node_with_val (TreeNode_t *perent, TreeNode_t *child, int val, bool isLeft) {
    bool res = false;
    if (child && perent) {
        if (child->val == val) {
            if (NULL == child->left && NULL == child->right) {
                if (true == isLeft) {
                    if (perent->left == child) {
                        perent->left = NULL;
                    }
                } else {
                    if (perent->right == child) {
                        perent->right = NULL;
                    }
                }
                free (child);
                res = true;
            }
        } else {
            res = delete_node_with_val (child, child->left, val, true);
            if (false == res) {
                res = delete_node_with_val (child, child->right, val, false);
            }
        }
    }
    return res;
}

bool delet_node_with (TreeNode_t **root, int val) {
    bool res = false;
    if ((*root)) {
        if (val == (*root)->val) {
            if (NULL == (*root)->left && NULL == (*root)->right) {
                free (*root);
                *root = NULL;
                res = true;
            }
        } else {
            res = delete_node_with_val (*root, (*root)->left, val, true);
            if (false == res) {
                res = delete_node_with_val (*root, (*root)->right, val, false);
            }
        }
    }
    return res;
}

int pop_max (TreeNode_t *binMaxHeapRoot) {
    int outVal = 0;
    if (NULL != binMaxHeapRoot) {
        outVal = binMaxHeapRoot->val;
    }
    return outVal;
}

bool is_max_heap (TreeNode_t *Root) {
    bool res = false;
    TreeNode_t *curNode = Root;
    if (NULL == curNode) {
        res = true;
    } else {
        bool isLeftOk = false;
        bool isRightOk = false;
        if (curNode->left) {
            if (curNode->left->val <= curNode->val) {
                isLeftOk = is_max_heap (curNode->left);
            }
        } else {
            isLeftOk = true;
        }

        // TODO:
        if (curNode->right) {
            if (curNode->right->val <= curNode->val) {
                isRightOk = is_max_heap (curNode->right);
            }
        } else {
            isRightOk = true;
        }
        if ((true == isLeftOk) && (true == isRightOk)) {
            res = true;
        }
    }
    return res;
}

bool max_heap_insert (TreeNode_t **binMaxHeapRoot, int newVal) {
    bool res = false;
    TreeNode_t *curNode = *binMaxHeapRoot;
    if (curNode) {
        /*At least one Element exist*/
        if (NULL == curNode->left) {
            res = binary_tree_attace_node (curNode, newVal, true);
            if (false == res) {
                printf (" Error");
            }
        } else if (NULL == curNode->right) {
            res = binary_tree_attace_node (curNode, newVal, false);
            if (false == res) {
                printf (" Error");
            }

        } else {
            /*both child exist*/
            int leftHeight = 1;
            int rightHeight = 1;
            rightHeight = height (curNode->right);
            leftHeight = height (curNode->left);

            if (false == is_complete (curNode)) {
                if (false == is_complete (curNode->left)) {
                    res = max_heap_insert (&curNode->left, newVal);
                } else if (false == is_complete (curNode->right)) {
                    res = max_heap_insert (&curNode->right, newVal);
                } else {
                    // printf ("\n each balansed put in any");
                    if (1 <= (rightHeight - leftHeight)) {
                        res = max_heap_insert (&curNode->left, newVal);
                    } else if (1 <= (leftHeight - rightHeight)) {
                        res = max_heap_insert (&curNode->right, newVal);
                    } else {
                        res = max_heap_insert (&curNode->left, newVal);
                    }
                }
            } else {
                res = max_heap_insert (&curNode->left, newVal);
            }
        }
        make_max_heap (*binMaxHeapRoot);

    } else {
        res = binary_tree_add_node (binMaxHeapRoot, newVal);
        if (false == res) {
            printf (" Error");
        }
    }
    return res;
}

void make_max_heap (TreeNode_t *root) {
    if (root) {
        uint32_t amountOfswiftp = 0;
        while (false == is_max_heap (root)) {
            amountOfswiftp++;
            if (root->left) {
                if (root->val < root->left->val) {
                    swap_int (&root->val, &root->left->val);
                }
                make_max_heap (root->left);
            }
            if (root->right) {
                if (root->val < root->right->val) {
                    swap_int (&root->val, &root->right->val);
                }
                make_max_heap (root->right);
            }
            if ((NULL == root->right) && (NULL == root->left)) {
                break;
            }
        }
        if (0 < amountOfswiftp) {
            printf ("\n amountOfswiftp: %d\n", amountOfswiftp);
        }
    }
}
