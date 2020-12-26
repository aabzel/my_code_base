#include "hash_set.h"

#include <stdio.h>
#include <stdlib.h>

HashSet_t *HashSetCreate (void) {
#ifdef DEBUG_HASH_SET
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    HashSet_t *hSet = NULL;
    hSet = (HashSet_t *)malloc (sizeof (HashSet_t));
    if (hSet) {
        for (int i = 0; i < TLB_SIZE; i++) {
            hSet->head_nodes[i] = NULL;
        }
    }
    return hSet;
}

bool HashSetAdd (HashSet_t *const in_hSet, int key) {
#ifdef DEBUG_HASH_SET
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    bool res = false;
    if (in_hSet) {
        int index = key % TLB_SIZE;
        res = list_add_node_front (&(in_hSet->head_nodes[index]), key);
    }
    return res;
}

bool HashSetContains (HashSet_t *in_hSet, int data) {
#ifdef DEBUG_HASH_SET
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    bool res = false;
    if (in_hSet) {
        ListNode_t *node;
        int index = data % TLB_SIZE;
        if (NULL != in_hSet->head_nodes[index]) {
            node = is_data_exist_linked_list ((in_hSet->head_nodes[index]), data);
            if (node) {
                res = true;
            }
        } else {
            printf ("\n[d] Error");
        }
    }
    return res;
}

bool HashSetRemove (HashSet_t *hSet, int data) {
#ifdef DEBUG_HASH_SET
    printf ("\n\n[d] %s() data %d", __FUNCTION__, data);
#endif
    int index = data % TLB_SIZE;
    bool res = false;
    if (hSet) {
        ListNode_t **node;
        (*node) = is_data_exist_linked_list ((hSet->head_nodes[index]), data);
        if (*node) {
            printf ("\n[d] node exist %p", *node);
#ifdef DEBUG_HASH_SET
#endif
            res = delete_node (node);
        } else {
            printf ("\n[d] Lack node");
#ifdef DEBUG_HASH_SET
#endif
        }
    }
    return res;
}

bool HashSetFree (HashSet_t *in_hSet) {
    printf ("\n[d] %s()", __FUNCTION__);
#ifdef DEBUG_HASH_SET
#endif
    bool res = false;
    if (in_hSet) {
        res = true;
        for (int i = 0; i < TLB_SIZE; i++) {
            res = linked_list_deinit (&(in_hSet->head_nodes[i])) && res;
        }
        // free(in_hSet);
        in_hSet = NULL;
    }
    printf ("\n[d] %s() done!", __FUNCTION__);
    return res;
}
