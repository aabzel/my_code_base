#ifndef __LINKED_LIST_OF_ARRAYS_TYPE_H
#define __LINKED_LIST_OF_ARRAYS_TYPE_H

//https://leetcode.com/tag/linked-list/

#ifdef __cplusplus
extern "C"
{
#endif

#include "array_type.h"

#include <stdint.h>


typedef struct xList_node_t {
    Array_t data;
    struct xList_node_t *nextNode;
} list_node_t;

#ifdef __cplusplus
}
#endif

#endif /* __LINKED_LIST_OF_ARRAYS_TYPE_H */
