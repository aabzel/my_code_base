#include "test_avl_tree.h"

#include "avl_tree.h"
#include "bin_tree_draw.h"

#include <stdio.h>
#include <stdlib.h>

bool test_avl_tree (void) {
    bool res = false;
    TreeNode_t *root = NULL;

    for (int i = 0; i < 40; i++) {
        root = avl_insert (root, i);
        res = print_tree_to_file (root, "AVL_tree.dot");
        if (true == res) {
            system ("draw.bat");
        }
    }

    return res;
}
