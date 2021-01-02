#ifndef HASH_SET_H
#define HASH_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "linked_list.h"

#define TLB_SIZE 100

typedef struct xMyHashSet {
    ListNode_t *head_nodes[TLB_SIZE];
} MyHashSet;

MyHashSet *myHashSetCreate (void);

bool myHashSetAdd (MyHashSet *const hSet, int key);
bool myHashSetRemove (MyHashSet *hSet, int key);
/** Returns true if this set contains the specified element */
bool myHashSetContains (MyHashSet *hSet, int key);
bool myHashSetFree (MyHashSet *obj);

#ifdef __cplusplus
}
#endif

#endif /*HASH_SET_H*/
