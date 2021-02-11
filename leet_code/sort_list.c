#include "sort_list.h"

#include "linked_list.h"

static void bubble_sort (ListNode_t *head_node) {
#ifdef DEBUG_SORT
    printf ("\n%s()", __FUNCTION__);
#endif
    int elem_num = linked_list_counts (head_node);
    if (elem_num <= 1) {
        return;
    }

    for (int j = 0; j < elem_num; j++) {
        for (int i = 0; i < elem_num - 1; i++) {
            if (val_by_index (head_node, i + 1) < val_by_index (head_node, i)) {
                bool res = swap_node_ll (node_by_index (head_node, i), node_by_index (head_node, i + 1));
#ifdef DEBUG_SORT
                if (false == res) {
                    printf ("\n%s() swap error", __FUNCTION__);
                }
#endif
            }
        }
    }
}


static void split_list(ListNode_t * list_a, ListNode_t **list_b) {
    ListNode_t * aux, *ult;
    if (list_a != NULL) {
       if (list_a->next == NULL) {
            *list_b = NULL;
       } else {
            aux = list_a;
            ult = list_a->next;
            while (ult != NULL) {
                ult = ult->next;
                if (ult != NULL) {
                    ult = ult->next;
                    aux = aux->next;
                }
            }
            *list_b = aux->next;
            aux->next = NULL;
       }
    }
}

void merge(ListNode_t * *list_a, ListNode_t * *list_b, ListNode_t * *list_res) {
    ListNode_t * aux;

    if (*list_a != NULL && *list_b != NULL) {
        if ((*list_a)->val < (*list_b)->val) {
            aux = *list_a;
            *list_a = (*list_a)->next;
        } else {
            aux = *list_b;
            *list_b = (*list_b)->next;
        }
        *list_res = aux;
        aux->next = NULL;
        while (*list_a != NULL && *list_b != NULL) {
            if ((*list_a)->val < (*list_b)->val) {
                aux->next = *list_a;
                *list_a = (*list_a)->next;
            } else {
                aux->next = *list_b;
                *list_b = (*list_b)->next;
            }
            aux = aux->next;
        }
        if (*list_a != NULL) {
            aux->next = *list_a;
            *list_a = NULL;
        }
        if (*list_b != NULL){
            aux->next = *list_b;
            *list_b = NULL;
        }
    } else if (*list_a == NULL && *list_b != NULL) {
        *list_res = *list_b;
        *list_b = NULL;
    } else if (*list_a != NULL && *list_b == NULL) {
        *list_res = *list_a;
        *list_a = NULL;
    }
}

ListNode_t * sort_list_merge(ListNode_t * head){
    ListNode_t * list_b, *list_res;

    if (head != NULL && head->next != NULL) {
        split_list(head, &list_b);
        head = sort_list_merge(head);
        list_b = sort_list_merge(list_b);
        merge(&head, &list_b, &list_res);
        head = list_res;
    }
    return head;
}



// inplace without recursion in order to use in MCU with small Stack RAM
ListNode_t *sortList (ListNode_t *head_node) {
#ifdef DEBUG_SORT
    printf ("\n%s()", __FUNCTION__);
#endif
    bubble_sort (head_node);
    return head_node;
}
