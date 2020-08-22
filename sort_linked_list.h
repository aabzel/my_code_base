#ifndef SORT_LINKED_LIST_H
#define SORT_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

#include "linked_list_types.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

bool test_list_sort (void);
void MergeSort (list_node_t **headRef);

#ifdef __cplusplus
}
#endif

#endif /* SORT_LINKED_LIST_H */
