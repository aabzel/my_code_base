#include "bin_tree.h"

#include "algorithms.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int g_maxDepthVal = 0;
static void find_max_depth (struct xTreeNode_t * tree, int level);

int max_depth (struct xTreeNode_t* root) {
    if (root) {
        g_maxDepthVal = 0;
        find_max_depth (root, 0);
    } else {
        g_maxDepthVal = -1;
    }
    return g_maxDepthVal + 1;
}

// Finds the maximum depth of the binary tree
static void find_max_depth (struct xTreeNode_t * tree, int level) {
    int nextLevel = 0;
    //printf ("\nlevel:%d\n", level);
    if (NULL != tree) {
        if (g_maxDepthVal < level) {
            g_maxDepthVal = level;
        }
        nextLevel = ++level;
        //printf ("\nnextLevel:%d\n", nextLevel);
        if (tree->left) {
            find_max_depth (tree->left, nextLevel);
        }
        if (tree->right) {
            find_max_depth (tree->right, nextLevel);
        }
    } else {
        //printf ("\nlast level:%d\n", level);
    }
    return;
}

// Finds the maximum depth of the binary tree
static void find_max_depth_leavs (struct xTreeNode_t * tree, int curLevel, int maxdepth) {
    int nextLevel = 0;
    printf ("\n curLevel:%d val: %d\n", curLevel, tree->val);
    if (NULL != tree) {
        if (g_maxDepthVal < curLevel) {
            g_maxDepthVal = curLevel;
        }
        if (curLevel == (maxdepth - 1)) {
            g_sum += tree->val;
            printf ("\n max level %d val %d\n", curLevel, tree->val);
        }
        nextLevel = ++curLevel;
        //printf ("\nnextLevel:%d\n", nextLevel);
        if (tree->left) {
            find_max_depth_leavs (tree->left, nextLevel, maxdepth);
        }
        if (tree->right) {
            find_max_depth_leavs (tree->right, nextLevel, maxdepth);
        }
    } else {
        //printf ("\nlast level:%d\n", level);
    }
    return;
}

int g_sum = 0;
int calc_leaves_sum (TreeNode_t* root, int maxDepth) {
    g_sum = 0;
    if (root) {
        g_maxDepthVal = 0;
        find_max_depth_leavs (root, 0, maxDepth);
    } else {
        g_maxDepthVal = -1;
    }
    return g_sum;
}

// Finds the size of the binary tree
int find_size (TreeNode_t * tree, int curSize) {
    if (tree->left) {
        curSize++;
        find_size (tree->left, curSize);
    }
    if (tree->right) {
        curSize++;
        find_size (tree->right, curSize);
    }
    return curSize + 1;
}

// In Order traversal
void print_inorder_traversal (TreeNode_t * tree) {
    if (tree->left) {
        print_inorder_traversal (tree->left);
    }
    printf ("%d\n", tree->val);
    if (tree->right) {
        print_inorder_traversal (tree->right);
    }
}

// Wrapper over print2DUtil()
void print2D (TreeNode_t *root) {
// Pass initial space count as 0
    print2DUtil (root, 0);
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil (TreeNode_t *root, int space) {
// Base case
    if (root == NULL)
        return;

// Increase distance between levels
    space += COUNT;

// Process right child first
    print2DUtil (root->right, space);

// Print current node after space
// count
    printf ("\n");
    for (int i = COUNT; i < space; i++)
        printf (" ");
    printf ("%d\n", root->val);

// Process left child
    print2DUtil (root->left, space);
}

void bst_print_dot_null (int key, int nullcount, FILE* stream) {
    fprintf (stream, "    null%d [shape=point];\n", nullcount);
    fprintf (stream, "    %d -> null%d;\n", key, nullcount);
}

void bst_print_dot_aux (TreeNode_t* node, FILE* stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf (stream, "    %d -> %d;\n", node->val, node->left->val);
        bst_print_dot_aux (node->left, stream);
    } else
        bst_print_dot_null (node->val, nullcount++, stream);

    if (node->right) {
        fprintf (stream, "    %d -> %d;\n", node->val, node->right->val);
        bst_print_dot_aux (node->right, stream);
    } else
        bst_print_dot_null (node->val, nullcount++, stream);
}

//use Graphviz Online
//https://dreampuf.github.io/GraphvizOnline

bool print_tree_to_file (TreeNode_t* root, char *fileName) {
    bool res = false;
    FILE * fp = NULL;
    fp = fopen (fileName, "w");
    if (fp) {
        bst_print_dot (root, fp);
        res = true;
    }
    return res;
}

void bst_print_dot (TreeNode_t* tree, FILE* stream) {
    fprintf (stream, "digraph BST {\n");
    fprintf (stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf (stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf (stream, "    %d;\n", tree->val);
    else
        bst_print_dot_aux (tree, stream);

    fprintf (stream, "}\n");
}

int get_parent_index (int nodeIndex, int size) {
    double paretnt = ceil (((double) nodeIndex / 2.0f) - 1.0f);
    int outParent = (int) paretnt;
    if (size < outParent) {
        printf ("\nError out of array %d\n", outParent);
        outParent = 0;
    }
    return outParent;
}

static int get_left_child_index (int perent, int sizeOfArr) {
    int leftChild = perent * 2 + 1;
    if (sizeOfArr < leftChild) {
        printf ("\nError out of array %d\n", leftChild);
        leftChild = 0;
    }
    return leftChild;
}

static bool is_left_son_exist (int patentIndex, int *arr, int size) {
    bool res = false;
    int leftSonIndex = get_left_child_index (patentIndex, size);
    if (NOT_NUM != arr [leftSonIndex]) {
        res = true;
    }
    return res;
}

static int get_right_child_index (int parentIndex, int sizeOfArr) {
    int rightChild = parentIndex * 2 + 2;
    if (sizeOfArr < rightChild) {
        printf ("\nError out of array %d\n", rightChild);
        rightChild = 0;
    }
    return rightChild;
}

static bool is_right_son_exist (int parentIndex, int *arr, int size) {
    bool res = false;
    int rightSonIndex = get_right_child_index (parentIndex, size);
    if (NOT_NUM != arr [rightSonIndex]) {
        res = true;
    }
    return res;
}

void parse_bin_tree (int *arr, int size) {
    bool res = false;
    for (int i = 0; i < size; i++) {
        printf ("\narr[%d] %d", i, arr [i]);
        if (NOT_NUM != arr [i]) {
            res = is_left_son_exist (i, arr, size);
            if (false == res) {
                printf ("\nlack of L son for %d", i);
            }
            res = is_right_son_exist (i, arr, size);
            if (false == res) {
                printf ("\nlack of R son for %d", i);
            }
        }
        //printf ("\n index %d expLindex %d expRindex %d", i, get_left_child_index (i, 1000), get_right_child_index (i, 1000));

        //int patentVal = arr [get_parent_index (i, size)];
        //if (NOT_NUM == patentVal) {
        //    printf ("\ni does not have parent %d\n", i);
        //}
        //if (NOT_NUM != arr [i]) {
        //    printf ("\n%d L(%d) R(%d)", arr [i], arr [get_left_child (i, size)], arr [get_right_child (i, size)]);
        //}
    }
}

int deepestLeavesSum (TreeNode_t * root) {
    int sum = 0;
    int maxDepth = 0;
    maxDepth = max_depth (root);
    sum = calc_leaves_sum (root, maxDepth);
    return sum;

}
