#include "hash_set.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

MyHashSet *myHashSetCreate (void) {
#ifdef DEBUG_HASH_SET
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    MyHashSet *hSet = NULL;
    hSet = (MyHashSet *)malloc (sizeof (MyHashSet));
    if (hSet) {
        for (int i = 0; i < TLB_SIZE; i++) {
            hSet->head_nodes[i] = NULL;
        }
    }
    return hSet;
}

bool myHashSetAdd (MyHashSet *const in_hSet, int key) {
#ifdef DEBUG_HASH_SET
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    bool res = false;
    if (in_hSet) {
        int index = key % TLB_SIZE;
        // is exist
        res = is_data_exist_linked_list (in_hSet->head_nodes[index], key);
        if (false == res) {
            res = list_add_node_front (&(in_hSet->head_nodes[index]), key);
        }
    }
    return res;
}

bool myHashSetContains (MyHashSet *in_hSet, int data) {
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

bool myHashSetRemove (MyHashSet *hSet, int data) {
#ifdef DEBUG_HASH_SET
    printf ("\n\n[d] %s() data %d", __FUNCTION__, data);
#endif
    printf ("\n[d] 0");
    int index = data % TLB_SIZE;
    bool res = false;
    if (hSet) {
        printf ("\n[d] 1");
        ListNode_t *node_del = NULL;
        printf ("\n[d] 2");
        //(*node) = NULL;
        node_del = is_data_exist_linked_list ((hSet->head_nodes[index]), data);
        printf ("\n[d] (*node) %p", node_del);
        if (NULL != node_del) {
            printf ("\n[d] node to delete exists");
#ifdef DEBUG_HASH_SET
            printf ("\n[d] node exist %p", node_del);
#endif
            res = delete_node (&node_del);
        } else {
#ifdef DEBUG_HASH_SET
            printf ("\n[d] Lack node");
#endif
        }
    }
    return res;
}

bool myHashSetFree (MyHashSet *in_hSet) {
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
