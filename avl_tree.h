#ifndef AVL_TREE_H
#define AVL_TREE_H

//https://github.com/ebiggers/avl_tree/blob/master/avl_tree.h
//https://github.com/penguincoder/avltree/blob/master/Tree.h
//https://github.com/penguincoder/avltree/blob/master/AVLTree.c
#include "bin_tree.h"

#include "avl_tree.h"

TreeNode_t *avl_insert (TreeNode_t *root, int val);
TreeNode_t *avl_delete (TreeNode_t *root, int val);

TreeNode_t *avl_insert_ok (TreeNode_t *root, int newVal);
TreeNode_t *avl_delete_bad (TreeNode_t *rootNode, int oldVal) ;

#endif /* AVL_TREE_H */
