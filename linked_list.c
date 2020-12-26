#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

/* Function to push a node */
bool list_add_node_front (ListNode_t **headNode, int new_data) {
    bool res = false;
    ListNode_t *newNode = NULL;
    newNode = (ListNode_t *)malloc (sizeof (ListNode_t *));
    if (NULL != newNode) {
        (newNode)->val = new_data;
        (newNode)->next = (*headNode);
        *headNode = newNode;
        res = true;
    }
    return res;
}
#if 0
ListNode_t** reverseList (ListNode_t** head) {
    ListNode_t** prevNode = NULL;
    ListNode_t** currentNode = head;
    ListNode_t** nextNode = NULL;
    while (currentNode != NULL) {
        // Store next
        nextNode = currentNode->next;

        // Reverse current node's pointer
        currentNode->next = prevNode;

        // Move pointers one position ahead.
        prevNode = currentNode;
        currentNode = nextNode;
    }
    head = prevNode;
    return head;
}

// This function mainly calls reverseUtil()
// with prev as NULL
void reverse_rec (ListNode_t*** head) {
    if (!head)
        return;
    reverse_util (*head, NULL, head);
}
#endif

// A simple and tail recursive function to reverse
// a linked list.  prev is passed as NULL initially.
static void reverse_util (ListNode_t *curr, ListNode_t *prev, ListNode_t **head) {
    /* If last node mark it head*/
    if (!curr->next) {
        *head = curr;

        /* Update next to prev node */
        curr->next = prev;
        return;
    }

    /* Save curr->next node for recursive call */
    ListNode_t *next = curr->next;

    /* and update next ..*/
    curr->next = prev;

    reverse_util (next, curr, head);
}

struct xListNode_t *middle_node (struct xListNode_t *head) {
    struct xListNode_t *slow = head;
    struct xListNode_t *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int linked_list_counts (ListNode_t *head_node) {
    int cnt = 0;
    if (head_node) {
        ListNode_t *cur_node = head_node;
        while (NULL != cur_node) {
            cnt++;
            cur_node = cur_node->next;
        }
    }
    return cnt;
}

ListNode_t *is_data_exist_linked_list (ListNode_t *head_node, int data) {
#ifdef DEBUG_LINKED_LIST
    printf ("\n[d] %s() %p", __FUNCTION__, head_node);
#endif
    ListNode_t *cur_node = NULL;
    int cnt = 0;
    int num = linked_list_counts (head_node);
    if (head_node) {
        cur_node = head_node;
        while (NULL != cur_node) {
            printf (",");
            cnt++;
#ifdef DEBUG_LINKED_LIST
            printf ("\n[d] %s() iter cnt %d", __FUNCTION__, cnt);
#endif
            if (num < cnt) {
                cur_node = NULL;
                break;
            }
            if (data == cur_node->val) {
                break;
            }
            if (cur_node->next) {
                cur_node = cur_node->next;
            } else {
                cur_node = NULL;
            }
        }
    } else {
        printf ("\n[d] error node");
    }
    return cur_node;
}

bool delete_node (ListNode_t **node) {
#if 0
    printf ("\n[d] %s() node=%p ", __FUNCTION__, *node);
#endif
    if (NULL == (*node)) {
#if 0
        printf ("\n[d] empty list\n");
#endif
        return false;
    } else {
#if 0
        printf ("\n[d] %s() node=%p val=%d", __FUNCTION__, *node, (*node)->val);
        printf ("\n[d] valid node %p\n", *node);
#endif
        if ((*node)->next == NULL) {
#if 0
            printf ("\n[d] This is last node\n");
#endif
            (*node)->val = 0;
            // free(*node);
            (*node) = NULL;
#if 0
            printf ("\n[d] Empty list\n");
#endif
            return true;
        } else {
            ListNode_t *temp = (*node)->next;
            // Copy data of the next node to current node
            (*node)->val = (*node)->next->val;
            (*node)->next = (*node)->next->next;
            free (temp);
            return true;
        }
    }
    return false;
}

bool linked_list_deinit (ListNode_t **head) {
#if 0
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    if (NULL == head) {
        return true;
    }
    if (NULL == *head) {
        return true;
    }
    bool res = false;
    int del_cnt = 0;
    int num_el = linked_list_counts (*head);
    printf ("\n[d] %d", num_el);
    while (true == delete_node (head)) {
        del_cnt++;
        printf (".");
        if (num_el < del_cnt) {
            printf ("\n[e] hand on");
            res = false;
            break;
        }
    }
    printf ("\n[d] del node done ");
    if (num_el == del_cnt) {
        printf ("\n[d] del fine ");
        res = true;
        (*head) = NULL;
    } else {
        printf ("\n[d] cnt!=del %d!=%d", num_el, del_cnt);
    }

    printf ("\n[d] %s() done", __FUNCTION__);
    return res;
}
