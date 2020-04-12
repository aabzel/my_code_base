#ifndef __BINARY_MAX_HEAP_ARRAY_H
#define __BINARY_MAX_HEAP_ARRAY_H

#include "custom_type.h"

/*
 A Binary Max Heap implementation
 */

typedef struct xBinaryHeap_t {
    int length; //current amount of items
    int capacity; //max allowable amount of items
    int *array; // pointer to array in heap memory
} BinaryHeap_t;

bool bin_heap_print (BinaryHeap_t *binHeap, bool isMax);
bool bin_heap_init (BinaryHeap_t *binHeap, int amountOfItems);
bool bin_heap_deinit (BinaryHeap_t *binHeap);

bool is_empty_heap (BinaryHeap_t *binHeap);
bool heap_insert_val (BinaryHeap_t *binHeap, bool isMaxHeap, int newVal);
int heap_peek (BinaryHeap_t *binHeap);
char *type_heap_to_name (bool isMaxHeap);
int heap_pop (BinaryHeap_t *binHeap, bool isMaxHeap);
bool is_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap);
bool bin_heap_remove_val (BinaryHeap_t *binHeap, bool isMax, int val);

int height_of_bin_heap (BinaryHeap_t *binHeap);
bool make_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap);

// low level bin heap API functions

int heap_find_min (BinaryHeap_t *binHeap);
int heap_find_max (BinaryHeap_t *binHeap);
bool make_bin_heap_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int parentIndex);
int get_perent_index (int childIndex);
int get_left_child_index (int parentIndex);
int get_right_child_index (int parentIndex);
int bin_heap_val_index_lll (BinaryHeap_t *binHeap, bool isMaxHeap, int val, int parentIndex);
int bin_heap_val_index_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int val);
int bin_heap_val_index_ll_bf (BinaryHeap_t *binHeap, bool isMaxHeap, int val);
bool is_val_in_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap, int val, int parentIdnex, int * const outIndex);
bool bubble_down_val_heap (BinaryHeap_t *binHeap, bool isMaxHeap);
bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd);
bool bubble_up_val_min_heap (BinaryHeap_t *binHeap, int index);
bool is_left_ch_exist (BinaryHeap_t *binHeap, int parInd);
bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd);

bool bubble_up_val_max_heap (BinaryHeap_t *binHeap, int index);
bool bubble_down_val_max_heap (BinaryHeap_t *binHeap);


#endif /* __BINARY_MAX_HEAP_ARRAY_H */
