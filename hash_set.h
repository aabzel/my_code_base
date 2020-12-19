#ifndef HASH_SET_H
#define HASH_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "linked_list.h"

#define TLB_SIZE 100

typedef struct xHashSet_t{
	ListNode_t* head_nodes[TLB_SIZE];
} HashSet_t;

HashSet_t* HashSetCreate(void) ;

bool HashSetAdd(HashSet_t* const hSet, int key);
bool HashSetRemove(HashSet_t* hSet, int key);
/** Returns true if this set contains the specified element */
bool HashSetContains(HashSet_t* hSet, int key) ;
bool HashSetFree(HashSet_t* obj);

#ifdef __cplusplus
}
#endif

#endif /*HASH_SET_H*/
