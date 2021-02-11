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

// inplace without recursion in order to use in MCU with small Stack RAM
ListNode_t *sortList (ListNode_t *head_node) {
#ifdef DEBUG_SORT
    printf ("\n%s()", __FUNCTION__);
#endif
    bubble_sort (head_node);
    return head_node;
}
