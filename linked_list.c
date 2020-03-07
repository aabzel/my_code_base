#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#if 0
list_node_t *pHead;

list_node_t Node1;
list_node_t Node2;
list_node_t Node3;
list_node_t Node4;
list_node_t Node5;


void init_list (void) {
    pHead = &Node1;

    Node1.val = 1;
    Node1.nextNode = &Node2;

    Node2.val = 2;
    Node2.nextNode = &Node3;

    Node3.val = 3;
    Node3.nextNode = &Node4;

    Node4.val = 4;
    Node4.nextNode = &Node5;

    Node5.val = 5;
    Node5.nextNode = NULL;
}
#endif

#if 0
void list_print_reverse (void) {
    list_print_rev (&Node1);
    printf ("\n");
}
#endif

#if 0

void list_print_rev (list_node_t *pHead) {
    if (pHead) {
        list_print_rev (pHead->nextNode);
        printf (" %d", pHead->val);
    }
}
#endif
#if 0
void list_print_fwd (void) {
    list_node_t *curNode = &Node1;
    while (NULL != curNode->nextNode) {
        printf (" %d", curNode->val);
        curNode = curNode->nextNode;
    }
    printf (" %d", curNode->val);
    printf ("\n");
}
#endif

bool linked_list_deinit (list_node_t *pInHead) {
    list_node_t *curNode = pInHead;
    list_node_t *prevNode = pInHead;
    bool res = false;
    if (pInHead) {
        if (NULL == curNode->nextNode) {
            free (curNode->data.pArr);
            free (curNode);
            res = true;
        } else {
            free (curNode->data.pArr);
            while (NULL != curNode->nextNode) {
                prevNode = curNode;
                curNode = curNode->nextNode;
                free (curNode->data.pArr);
                free (prevNode);
            }
            res = true;
        }
    }
    return res;
}

int linked_list_add_array (list_node_t **pInHead, int *inArr, int arrSize) {
    /*Find the end of Linked List*/
    int res = 0;
    if (0 < arrSize) {
        list_node_t *newNode = NULL;
        int amountOfElem = list_num_of_elements (*pInHead);
        if (0 < amountOfElem) {
            list_node_t *pCurNode = *pInHead;
            list_node_t *pEndNode = NULL;
            while (NULL != pCurNode->nextNode) {
                pCurNode = pCurNode->nextNode;
            }
            pEndNode = pCurNode;
            newNode = malloc (sizeof(list_node_t));
            if (newNode) {
                newNode->nextNode = NULL;
                newNode->data.arrSize = arrSize;
                newNode->data.pArr = memdup (inArr, sizeof(int) * arrSize);
                pEndNode->nextNode = newNode;
                res = 1;
            } else {
                printf ("\nUnable to malloc new node!\n");
            }
        }
        if (0 == amountOfElem) {
            newNode = malloc (sizeof(list_node_t));
            if (newNode) {
                newNode->nextNode = NULL;
                newNode->data.arrSize = arrSize;
                newNode->data.pArr = memdup (inArr, sizeof(int) * arrSize);

                *pInHead = newNode;
                res = 1;
            } else {
                printf ("\nUnable to malloc new node!\n");
            }
        }
    } else {
        printf ("\nArray is 0\n");
    }
    return res;

}

int list_num_of_elements (list_node_t *pHead) {
    int amountOfElem = 0;
    if (pHead) {
        amountOfElem++;
        list_node_t *pCurNode = pHead;
        while (NULL != pCurNode->nextNode) {
            pCurNode = pCurNode->nextNode;
            amountOfElem++;
        }
    }

    return amountOfElem;
}

void print_list (list_node_t *pHead) {
    int numElem = list_num_of_elements (pHead);
    printf ("\nList content: amount of item: [%d]\n", numElem);
    if (pHead) {
        list_node_t *pCurNode = pHead;
        while (pCurNode) {
            print_curr_array (pCurNode->data.pArr, pCurNode->data.arrSize);
            pCurNode = pCurNode->nextNode;
        }
    }
}

#if 0
void list_print_rev (void) {

}
#endif

