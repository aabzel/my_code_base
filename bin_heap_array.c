#include "bin_heap_array.h"

#include "algorithms.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int get_perent_index (int childIndex) {
    int parentIndex = 0;
    if (0 < childIndex) {
        parentIndex = ((childIndex + 1) / 2) - 1;
    } else {
        parentIndex = -1;
    }
    return parentIndex;
}

int get_left_child_index (int parentIndex) {
    int childIndex = 0;
    if (0 <= parentIndex) {
        childIndex = (2 * (parentIndex + 1)) - 1;
    } else {
        childIndex = -1;
    }

    return childIndex;
}

int get_rihgt_child_index (int parentIndex) {
    int childIndex = 0;
    if (0 <= parentIndex) {
        childIndex = 2 * (parentIndex + 1);
    } else {
        childIndex = -1;
    }

    return childIndex;
}

bool insert_val (BinaryHeap_t *binHeap, int val) {
    bool res = false;
    if (binHeap) {
        if (binHeap->length < ARRAY_LIMIT) {
            binHeap->array [binHeap->length] = val;
            bubble_up_val_max_heap (binHeap, binHeap->length);
            binHeap->length++;
            res = true;
        }
    }
    return res;
}

bool bubble_up_val_max_heap (BinaryHeap_t *binHeap, int index) {
    bool res = false;
    int childIndex = index;
    int parentIndex = get_perent_index (childIndex);
    while ((0 <= parentIndex) && (binHeap->array [parentIndex] < binHeap->array [childIndex])) {
        swap_int (&binHeap->array [parentIndex], &binHeap->array [childIndex]);
        childIndex = parentIndex;
        parentIndex = get_perent_index (childIndex);
    }
    return res;
}

bool is_max_bin_heap (BinaryHeap_t *binHeap) {
    bool res = true;
    if (binHeap) {
        if (0 < binHeap->length) {
            int childIndex = 0;
            for (int parInd = 0; parInd < binHeap->length; parInd++) {
                if (is_left_ch_exist (binHeap, parInd)) {
                    /*verify max bin heap property*/
                    childIndex = get_left_child_index (parInd);
                    if (binHeap->array [parInd] < binHeap->array [childIndex]) {
                        res = false;
                    }
                }
                if (is_right_ch_exist (binHeap, parInd)) {
                    childIndex = get_rihgt_child_index (parInd);
                    /*verify max bin heap property*/
                    if (binHeap->array [parInd] < binHeap->array [childIndex]) {
                        res = false;
                    }
                }
            }
        } else if (0 == binHeap->length) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool is_right_ch_exist (BinaryHeap_t *binHeap, int parInd) {
    bool res = false;
    if (binHeap) {
        if (parInd < binHeap->length) {
            int rIndex = get_rihgt_child_index (parInd);
            if (rIndex < binHeap->length) {
                res = true;
            }
        }
    }
    return res;
}

bool is_left_ch_exist (BinaryHeap_t *binHeap, int parInd) {
    bool res = false;
    if (binHeap) {
        if (parInd < binHeap->length) {
            int lIndex = get_left_child_index (parInd);
            if (lIndex < binHeap->length) {
                res = true;
            }
        }
    }
    return res;
}
