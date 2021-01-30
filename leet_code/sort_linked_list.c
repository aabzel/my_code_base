#include "sort_linked_list.h"

#include "linked_list.h"

#include <stdint.h>
#include <stdio.h>

#if 0
static list_node_t *SortedMerge (list_node_t *a, list_node_t *b);
static void FrontBackSplit (list_node_t *source, list_node_t **frontRef, list_node_t **backRef);

bool test_list_sort (void) {
    bool res = false;
    list_node_t *Head = NULL;
    res = push_val (&Head, 4);
    res = push_val (&Head, 5);
    res = push_val (&Head, 2);
    res = push_val (&Head, 6);
    res = push_val (&Head, 7);
    res = push_val (&Head, 1);

    show_list (Head);

    MergeSort (&Head);

    show_list (Head);
    return res;
}

void MergeSort (list_node_t **headRef) {
    list_node_t *head = *headRef;
    list_node_t *a;
    list_node_t *b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->nextNode == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit (head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort (&a);
    MergeSort (&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge (a, b);
}

static void FrontBackSplit (list_node_t *source, list_node_t **frontRef, list_node_t **backRef) {
    list_node_t *fast;
    list_node_t *slow;
    slow = source;
    fast = source->nextNode;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->nextNode;
        if (fast != NULL) {
            slow = slow->nextNode;
            fast = fast->nextNode;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
     at that point. */
    *frontRef = source;
    *backRef = slow->nextNode;
    slow->nextNode = NULL;
}

static list_node_t *SortedMerge (list_node_t *a, list_node_t *b) {
    list_node_t *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->data <= b->data) {
        result = a;
        result->nextNode = SortedMerge (a->nextNode, b);
    } else {
        result = b;
        result->nextNode = SortedMerge (a, b->nextNode);
    }
    return (result);
}

#endif