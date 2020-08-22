#include "test_avl_tree.h"

#include "avl_tree.h"
#include "bin_search_tree.h"
#include "bin_tree.h"
#include "bin_tree_draw.h"

#include <stdio.h>
#include <stdlib.h>

bool test_avl_tree (void) {
    bool res = false;

    res = test_avl_tree_insert ();
    if (false == res) {
        return res;
    }
    res = test_avl_tree_delete ();
    if (false == res) {
        return res;
    }

    return res;
}

bool test_avl_tree_insert (void) {
    bool res = false;
    TreeNode_t *root = NULL;
    int numOfElem;
    for (int i = 1; i <= 40; i++) {
        root = avl_insert (root, i);
        res = is_bin_search_tree (root);
        if (false == res) {
            printf ("\n not BST  after insert \n");
            break;
        }
        res = is_balanced (root);
        if (false == res) {
            printf ("\n not balanced  after insert \n");
            break;
        }

        numOfElem = find_size (root);
        if (i != numOfElem) {
            printf ("\nsize unmatch  after insert  \n");
            res = false;
            break;
        }

#if DRAW_AVL_TREE
        res = print_tree_to_file (root, "AVL_tree.dot");
        if (true == res) {
            system ("draw.bat");
        }
#endif
    }
    print_inorder (root);

    return res;
}

bool test_avl_tree_delete (void) {
    bool res = false;
    TreeNode_t *root = NULL;
    int numOfElem;

    for (int i = 1; i <= 20; i++) {
        root = avl_insert (root, i);
        res = is_bin_search_tree (root);
        if (false == res) {
            printf ("\n not BST after insert \n");
            break;
        }
        res = is_balanced (root);
        if (false == res) {
            printf ("\n not balanced  after insert \n");
            break;
        }
        numOfElem = find_size (root);
        if (i != numOfElem) {
            printf ("\nsize unmatch  after insert  \n");
            res = false;
            break;
        }

#if DRAW_AVL_TREE_INSERT
        res = print_tree_to_file (root, "AVL_tree.dot");
        if (true == res) {
            system ("draw.bat");
        }
#endif
    }

    for (int i = 1; i <= 20; i++) {
        root = avl_delete (root, i);
        res = is_bin_search_tree (root);
        if (false == res) {
            printf ("\n not BST after del \n");
            break;
        }
        res = is_balanced (root);
        if (false == res) {
            printf ("\n not balanced after del %d\n", i);
            break;
        }
        numOfElem = find_size (root);
        if ((20 - i) != numOfElem) {
            res = false;
            printf ("\nsize unmatch after del \n");
            break;
        }

#if DRAW_AVL_TREE_DELETE
        res = print_tree_to_file (root, "AVL_tree.dot");
        if (true == res) {
            system ("draw.bat");
        }
#endif
    }

    return res;
}
