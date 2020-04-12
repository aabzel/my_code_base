#include "bin_heap_array.h"

#include "algorithms.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int heap_find_max (BinaryHeap_t *binHeap) {
    int val = INT_MIN;
    val = heap_peek (binHeap);
    return val;
}

int heap_find_min (BinaryHeap_t *binHeap) {
    int val = INT_MAX;
    val = heap_peek (binHeap);
    return val;
}

bool is_empty_heap (BinaryHeap_t *binHeap) {
    bool res = false;
    if (binHeap) {
        if (0 == binHeap->length) {
            res = true;
        }
    }
    return res;
}

int heap_peek (BinaryHeap_t *binHeap) {
    int val = 0;
    if (binHeap) {
        if (0 < binHeap->length) {
            val = binHeap->array [0];
        } else {
            printf ("\n %s Bin Heap is empty!\n", __FUNCTION__);
        }
    }
    return val;
}

bool bubble_down_val_heap (BinaryHeap_t *binHeap, bool isMaxHeap) {
    bool res = false;
    if (binHeap) {
        int childIndex;
        for (int parentIndex = 0; parentIndex < binHeap->length; parentIndex++) {
            if (is_left_ch_exist (binHeap, parentIndex)) {
                /*verify max bin heap property*/
                childIndex = get_left_child_index (parentIndex);
                if (isMaxHeap) {
                    if (binHeap->array [parentIndex] < binHeap->array [childIndex]) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [childIndex]));
                    }
                } else {
                    if (binHeap->array [childIndex] < binHeap->array [parentIndex]) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [childIndex]));
                    }
                }

            }
            if (is_right_ch_exist (binHeap, parentIndex)) {
                childIndex = get_right_child_index (parentIndex);
                /*verify max bin heap property*/
                if (isMaxHeap) {
                    if (binHeap->array [parentIndex] < binHeap->array [childIndex]) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [childIndex]));
                    }
                } else {
                    if (binHeap->array [childIndex] < binHeap->array [parentIndex]) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [childIndex]));
                    }
                }
            }
        }
        res = true;
    }
    return res;
}

int heap_pop (BinaryHeap_t *binHeap, bool isMaxHeap) {
    int val = 0;
    if (binHeap) {
        if (0 < binHeap->length) {
            val = binHeap->array [0];
            binHeap->array [0] = binHeap->array [binHeap->length - 1];
            binHeap->length--;
            if (true == isMaxHeap) {
                bubble_down_val_heap (binHeap, true);
            } else {
                bubble_down_val_heap (binHeap, false);
            }
        } else {
            printf ("\n binHeap is emply!\n");
        }
    }
    return val;
}

//0->-1    1->0 2->0 3->1 4->1 5->2 6->2 7->3 8->3 9->4
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
        childIndex = (2 * (parentIndex)) + 1;
    } else {
        childIndex = -1;
    }

    return childIndex;
}
//0->2  1->4  2->6   3->8
int get_right_child_index (int parentIndex) {
    int childIndex = 0;
    if (0 <= parentIndex) {
        childIndex = (2 * (parentIndex)) + 2;
    } else {
        childIndex = -1;
    }

    return childIndex;
}

//TODO: boost function
int bin_heap_val_index_ll_bf (BinaryHeap_t *binHeap, bool isMaxHeap, int val) {
    int indexVal = -1;
    if (binHeap) {
        if (true == isMaxHeap || false == isMaxHeap) {
            for (int i = 0; i < binHeap->length; i++) {
                if (val == binHeap->array [i]) {
                    return i;
                }
            }
        }
    }
    return indexVal;
}

int bin_heap_val_index_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int val) {
    int indexVal = -1;
    if (binHeap) {
        //indexVal = bin_heap_val_index_ll_bf (binHeap, isMaxHeap, val);
        indexVal = bin_heap_val_index_lll (binHeap, isMaxHeap, val, 0);
        if (indexVal < 0) {
            printf ("\nUnable to find index of val in bin heap [%d]\n", val);
        }
    }
    return indexVal;
}

//SIG SEG unable to find val index
int bin_heap_val_index_lll (BinaryHeap_t *binHeap, bool isMaxHeap, int val, int parentIndex) {
    int indexVal = -1;
    if (binHeap && (0 <= parentIndex) && (parentIndex < (binHeap->length))) {
        if (val == binHeap->array [parentIndex]) {
            return parentIndex;
        } else {
            if (isMaxHeap) {
                if (binHeap->array [parentIndex] < val) {
                    return -1;
                } else {
                    indexVal = bin_heap_val_index_lll (binHeap, isMaxHeap, val, get_left_child_index (parentIndex));
                    if (indexVal < 0) {
                        indexVal = bin_heap_val_index_lll (binHeap, isMaxHeap, val, get_right_child_index (parentIndex));
                    }
                }
            } else {
                if (val < binHeap->array [parentIndex]) {
                    return -1;
                } else {
                    indexVal = bin_heap_val_index_lll (binHeap, isMaxHeap, val, get_left_child_index (parentIndex));
                    if (indexVal < 0) {
                        indexVal = bin_heap_val_index_lll (binHeap, isMaxHeap, val, get_right_child_index (parentIndex));
                    }
                }
            }
        }
    }
    return indexVal;
}

bool bin_heap_remove_val (BinaryHeap_t *binHeap, bool isMaxHeap, int val) {
    bool res = false;
    if (binHeap && ((true == isMaxHeap) || (false == isMaxHeap))) {
        int indexValFast = -1;
        res = is_val_in_bin_heap (binHeap, isMaxHeap, val, 0, &indexValFast);
        if (true == res) {
#if DEBUG_HEAP
            printf ("\n val [%d] exists in heap \n", val);
#endif
            //int indexVal = bin_heap_val_index_ll (binHeap, isMaxHeap, val);
            //if (indexVal != indexVal1) {
            //    printf ("\n %s: Val Index   fast %d slow %d \n", __FUNCTION__, indexVal1, indexVal);
            //}
#if DEBUG_HEAP
            printf ("\n val [%d] exists in heap. Its index [%d] \n", val, indexVal);
#endif
            if (0 <= indexValFast && indexValFast < binHeap->length) {
                swap_int (&binHeap->array [indexValFast], &binHeap->array [binHeap->length - 1]);
                binHeap->length--;
                res = make_bin_heap (binHeap, isMaxHeap);
                if (false == res) {
                    printf ("\n Unable to gather heap after delete %d\n", val);
                }
            } else {
                printf ("\n %s: Index error fast %d slow \n", __FUNCTION__, indexValFast);
            }
        }
    }
    if (false == res) {
        printf ("\n Unable to delete val %d from %s bin heap\n", val, type_heap_to_name (isMaxHeap));
    }
    return res;
}

char *type_heap_to_name (bool isMaxHeap) {
    static char *str = "undef";
    if (true == isMaxHeap) {
        str = "Max";
    } else if (false == isMaxHeap) {
        str = "Min";
    }
    return str;
}

bool heap_insert_val (BinaryHeap_t *binHeap, bool isMaxHeap, int newVal) {
    bool res = false;
    if (binHeap && ((false == isMaxHeap) || (true == isMaxHeap))) {
        if (binHeap->length <= binHeap->capacity) {
            binHeap->array [binHeap->length] = newVal;
            if (true == isMaxHeap) {
                res = bubble_up_val_max_heap (binHeap, binHeap->length);
            } else {
                res = bubble_up_val_min_heap (binHeap, binHeap->length);
            }
            if (true == res) {
                binHeap->length++;
            }
        } else {
            printf ("\n Heap is full!\n");
        }
    }
    if (false == res) {
        printf ("\n heap insert val [%d] error \n", res);
    }

    return res;
}

bool make_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap) {
    bool res = false;
    if (binHeap) {
        int iter = 0;
        while (false == is_bin_heap (binHeap, isMaxHeap)) {
            res = make_bin_heap_ll (binHeap, isMaxHeap, 0);
            //printf ("\n make_bin_heap_ll!\n");
            iter++;
        }
        if (0 == iter) {
            res = true;
        }
        //printf ("\n iter: %d\n", iter);
    }
    return res;
}

bool make_bin_heap_ll (BinaryHeap_t *binHeap, bool isMaxHeap, int parentIndex) {
    bool res = false;
    if (binHeap) {
        if ((0 <= parentIndex) && (parentIndex < (binHeap->length))) {
            if (isMaxHeap) {
                if (is_left_ch_exist (binHeap, parentIndex)) {
                    int lChInd = get_left_child_index (parentIndex);
                    if ((binHeap->array [parentIndex]) < (binHeap->array [lChInd])) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [lChInd]));
                    }
                    res = make_bin_heap_ll (binHeap, isMaxHeap, lChInd);
                }
                if (is_right_ch_exist (binHeap, parentIndex)) {
                    int rChInd = get_right_child_index (parentIndex);
                    if ((binHeap->array [parentIndex]) < (binHeap->array [rChInd])) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [rChInd]));
                    }
                    res = make_bin_heap_ll (binHeap, isMaxHeap, rChInd);
                }
            } else {
                if (is_left_ch_exist (binHeap, parentIndex)) {
                    int lChInd = get_left_child_index (parentIndex);
                    if ((binHeap->array [lChInd]) < (binHeap->array [parentIndex])) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [lChInd]));
                    }
                    res = make_bin_heap_ll (binHeap, isMaxHeap, lChInd);
                }
                if (is_right_ch_exist (binHeap, parentIndex)) {
                    int rChInd = get_right_child_index (parentIndex);
                    if ((binHeap->array [rChInd]) < (binHeap->array [parentIndex])) {
                        swap_int (&(binHeap->array [parentIndex]), &(binHeap->array [rChInd]));
                    }
                    res = make_bin_heap_ll (binHeap, isMaxHeap, rChInd);
                }
            }
            res = true;
        }
    } else {
        res = false;
    }
    return res;
}

bool bubble_up_val_min_heap (BinaryHeap_t *binHeap, int index) {
    bool res = false;
    if (binHeap) {
        if (0 <= (binHeap->length) - index) {
            int childIndex = index;
            int parentIndex = get_perent_index (childIndex);
            while ((0 <= parentIndex) && (binHeap->array [childIndex] < binHeap->array [parentIndex])) {
                swap_int (&binHeap->array [parentIndex], &binHeap->array [childIndex]);
                childIndex = parentIndex;
                parentIndex = get_perent_index (childIndex);
            }
            res = true;
        }
    }
    return res;
}

bool bubble_up_val_max_heap (BinaryHeap_t *binHeap, int index) {
    bool res = false;
    if (binHeap) {
        if (0 <= (binHeap->length) - index) {
            int childIndex = index;
            int parentIndex = get_perent_index (childIndex);
            while ((0 <= parentIndex) && (binHeap->array [parentIndex] < binHeap->array [childIndex])) {
                swap_int (&binHeap->array [parentIndex], &binHeap->array [childIndex]);
                childIndex = parentIndex;
                parentIndex = get_perent_index (childIndex);
            }
            res = true;
        }
    }
    return res;
}

bool bin_heap_deinit (BinaryHeap_t *binHeap) {
    bool res = false;
    if (binHeap) {
        binHeap->length = 0;
        binHeap->capacity = 0;
        free (binHeap->array);
        binHeap->array = NULL;
    }
    return res;
}

bool bin_heap_init (BinaryHeap_t *binHeap, int amountOfItems) {
    bool res = false;
    if (binHeap) {
        binHeap->length = 0;
        binHeap->capacity = 0;
        binHeap->array = (int *) malloc (amountOfItems * sizeof(int));
        if (binHeap->array) {
            binHeap->capacity = amountOfItems;
            res = true;
        } else {
            printf ("\nUnabe to alloc array for heap\n");
        }
    }
    if (false == res) {
        printf ("\nUnabe to init heap\n");
    }
    return res;
}

bool is_val_in_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap, int val, int parentIdnex, int * const outIndex) {
    bool res = false;
    int valIndex = 0;
    if (binHeap) {
        if ((0 < binHeap->length) && (parentIdnex < (binHeap->length))) {
            int parentVal = binHeap->array [parentIdnex];
            if (parentVal == val) {
                *outIndex = parentIdnex;
                return true;
            }
            int rChildIndex = get_right_child_index (parentIdnex);
            int lChildIndex = get_left_child_index (parentIdnex);

            if (isMaxHeap) {
                if (parentVal < val) {
                    return false;
                }
            } else {
                if (val < parentVal) {
                    return false;
                }
            }

            res = is_val_in_bin_heap (binHeap, isMaxHeap, val, rChildIndex, &valIndex);
            if (true == res) {
                *outIndex = valIndex;
                return true;
            }
            res = is_val_in_bin_heap (binHeap, isMaxHeap, val, lChildIndex, &valIndex);
            if (true == res) {
                *outIndex = valIndex;
                return true;
            }
        }
    }
    return false;

}

bool is_bin_heap (BinaryHeap_t *binHeap, bool isMaxHeap) {
    bool res = true;
    if (binHeap) {
        if (0 < binHeap->length) {
            int childIndex = 0;
            for (int parInd = 0; parInd < binHeap->length; parInd++) {
                if (is_left_ch_exist (binHeap, parInd)) {
                    childIndex = get_left_child_index (parInd);
                    if (true == isMaxHeap) {
                        /*verify max bin heap property*/
                        if (binHeap->array [parInd] < binHeap->array [childIndex]) {
                            res = false;
                        }
                    } else {
                        if (binHeap->array [childIndex] < binHeap->array [parInd]) {
                            res = false;
                        }
                    }
                }
                if (is_right_ch_exist (binHeap, parInd)) {
                    childIndex = get_right_child_index (parInd);
                    if (true == isMaxHeap) {
                        /*verify max bin heap property*/
                        if (binHeap->array [parInd] < binHeap->array [childIndex]) {
                            res = false;
                        }
                    } else {
                        if (binHeap->array [childIndex] < binHeap->array [parInd]) {
                            res = false;
                        }
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
            int rIndex = get_right_child_index (parInd);
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

bool bin_heap_print (BinaryHeap_t *binHeap, bool isMax) {
    bool res = false;
    if (binHeap) {
        printf ("\n%s Bin heap tree [ \n", type_heap_to_name (isMax));
        if (0 < (binHeap->length)) {
            for (int i = 0; i < binHeap->length; i++) {
                printf (" %d ", binHeap->array [i]);
                if (is_power_of_two (i)) {
                    printf ("\n");
                }
            }
        }
        res = true;
        printf ("]\n");
    }

    return res;
}
