bool swap_node_ll (struct ListNode *node_a, struct ListNode *node_b) {
    bool res = false;
    if (node_a && node_b) {
        int temp_a = node_a->val;
        int temp_b = node_b->val;
        node_a->val = temp_b;
        node_b->val = temp_a;
        res = true;
    }
    return res;
}

struct ListNode *node_by_index (struct ListNode *head_node, int des_index) {
    int cur_index = 0;
    struct ListNode *ret_node = NULL;
    struct ListNode *cur_node = head_node;
    while (cur_node != NULL) {
        if (des_index == cur_index) {
            ret_node = cur_node;
            break;
        }
        cur_index++;
        cur_node = cur_node->next;
    }
    return ret_node;
}

int val_by_index (struct ListNode *head_node, int des_index) {
    struct ListNode *ret_node = NULL;
    int val = -1;
    ret_node = node_by_index (head_node, des_index);
    if (NULL != ret_node) {
        val = ret_node->val;
    }
    return val;
}

int linked_list_counts (struct ListNode *head_node) {
    int cnt = 0;
    if (head_node) {
        struct ListNode *cur_node = head_node;
        while (NULL != cur_node) {
            cnt++;
            cur_node = cur_node->next;
        }
    }
    return cnt;
}

static void bubble_sort (struct ListNode *head_node) {
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
                if (false == res) {
                    printf ("\n%s() swap error", __FUNCTION__);
                }
            }
        }
    }
}

// inplace without recursion in ordet to use in MCU with small Stack RAM
struct ListNode *sortList (struct ListNode *head_node) {
#ifdef DEBUG_SORT
    printf ("\n%s()", __FUNCTION__);
#endif
    bubble_sort (head_node);
    return head_node;
}
