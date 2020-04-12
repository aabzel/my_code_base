#include "avl_tree.h"
#include "algorithms.h"

#include <stdlib.h>

static TreeNode_t *DoubleRightRotation (TreeNode_t *rootNode);
static TreeNode_t *DoubleLeftRotation (TreeNode_t *rootNode);
static TreeNode_t *CheckTreeNodeRotation (TreeNode_t *tnode, TreeNode_t *subtree, short *finished);
static TreeNode_t *SingleLeftRotation (TreeNode_t *rootNode);
static TreeNode_t *SingleRightRotation(TreeNode_t *rootNode);
static TreeNode_t *InsertNode (TreeNode_t *tnode, int val, short *finished);

TreeNode_t *avl_insert (TreeNode_t *root, int newVal) {
    TreeNode_t *node;
    short done = 0;
    node = InsertNode (root, newVal, &done);
    return node;
}

static TreeNode_t *InsertNode (TreeNode_t *tnode, int newVal, short *finished) {
    TreeNode_t *subtree = NULL;
    short comp = 0;

    if (tnode == NULL) {
        /* found the spot that the TreeNode belongs */
        tnode = malloc (sizeof(TreeNode_t));
        /* malloc problem, return NULL */
        if (tnode == NULL)
            return NULL;
        else {
            /* default settings for a new node */
            tnode->left = NULL;
            tnode->right = NULL;
            tnode->val = newVal;
            tnode->Balance = 0;
        }
    } else {
        /* need to find the new node, don't check for a 0,
         cos its already in teh tree, foo */
        comp = compare (newVal, tnode->val);
        if (comp < 0) {
            /* go left */
            subtree = InsertNode (tnode->left, newVal, finished);
            /* if this is NULL, there is problem. quit now */
            if (subtree == NULL)
                return NULL;
            /* you are not finished until Balance == 0, reached the root
             or a rotation has occured */
            if (!*finished)
                tnode->Balance--;
            tnode->left = subtree;
        } else if (comp > 0) {
            /* go right */
            subtree = InsertNode (tnode->right, newVal, finished);
            if (subtree == NULL)
                return NULL;
            if (!*finished)
                tnode->Balance++;
            tnode->right = subtree;
        } else
            /* got a dupe, return NULL */
            return NULL;

        /* check if a rotation is neccessary */
        if (!*finished) {
            tnode = CheckTreeNodeRotation (tnode, subtree, finished);
        }
    }
    return tnode;
}

static TreeNode_t *CheckTreeNodeRotation (TreeNode_t *tnode, TreeNode_t *subtree, short *finished) {
    /* this function will check to see if tnode's Balance factor indicates
     that a rotation is needed. Subtree is the child link that was either
     just added or possibly changed */
    switch (tnode->Balance) {
        case 0:
            /* nothing special, but we have balanced out properly, yay */
            *finished = 1;
            break;
        case 2:
            /* right heavy */
            *finished = 1;
            if (subtree->Balance == -1) {
                /* update balance factors */
                if (subtree->left->Balance == 1) {
                    subtree->Balance = 0;
                    tnode->Balance = -1;
                } else if (subtree->left->Balance == -1) {
                    subtree->Balance = 1;
                    tnode->Balance = 0;
                } else
                    subtree->Balance = tnode->Balance = 0;
                subtree->left->Balance = 0;
                tnode = DoubleLeftRotation (tnode);
            } else if (subtree->Balance == 1) {
                /* update balance factors */
                subtree->Balance = tnode->Balance = 0;
                tnode = SingleLeftRotation (tnode);
            }
            break;
        case -2:
            /* left heavy */
            *finished = 1;
            if (subtree->Balance == 1) {
                /* update balance factors */
                if (subtree->right->Balance == -1) {
                    subtree->Balance = 0;
                    tnode->Balance = 1;
                } else if (subtree->right->Balance == 1) {
                    subtree->Balance = -1;
                    tnode->Balance = 0;
                } else
                    subtree->Balance = tnode->Balance = 0;
                subtree->right->Balance = 0;
                tnode = DoubleRightRotation (tnode);
            } else if (subtree->Balance == -1) {
                /* update balance factors */
                subtree->Balance = tnode->Balance = 0;
                tnode = SingleRightRotation (tnode);
            }
    }
    return tnode;
}

static TreeNode_t *DoubleRightRotation (TreeNode_t *rootNode) {
    TreeNode_t *newRoot = SingleLeftRotation (rootNode->left);
    rootNode->left = newRoot;
    newRoot = SingleRightRotation (rootNode);
    return newRoot;
}

static TreeNode_t *DoubleLeftRotation (TreeNode_t *rootNode) {
    TreeNode_t *newRoot = SingleRightRotation (rootNode->right);
    rootNode->right = newRoot;
    newRoot = SingleLeftRotation (rootNode);
    return newRoot;
}

static TreeNode_t *SingleRightRotation(TreeNode_t *rootNode)
{
    TreeNode_t *newRoot = NULL;
    newRoot = rootNode->left;
    rootNode->left = newRoot->right;
    newRoot->right = rootNode;
    return newRoot;
}

static TreeNode_t *SingleLeftRotation (TreeNode_t *rootNode) {
    TreeNode_t *newRoot = NULL;
    newRoot = rootNode->right;
    rootNode->right = newRoot->left;
    newRoot->left = rootNode;
    return newRoot;
}
