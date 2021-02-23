#include "arrays.h"

//#include "algorithms.h"
#include "array_type.h"
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *singleNumber (int *nums, int numsSize, int *const returnSize) {
    int code = 0, a = 0, b = 0;
    int *arr = NULL;
    int i;
    for (i = 0; i < numsSize; i++) {
        code ^= nums[i];
    }
#if 0
    printf ("\n  code    %08x %d   0b_%s", code, code,uint32_to_bin_str (code));
    printf ("\n -code    %08x %d  0b_%s", -code, -code,uint32_to_bin_str (-code));
#endif
    code = code & (-code);
#if 0
    printf ("\n new code %08x %d   0b_%s", code, code,uint32_to_bin_str (code));
#endif
    // find a different bits
    for (i = 0; i < numsSize; i++) {
        if (0 != (nums[i] & code)) {
            a ^= nums[i];
        } else {
            b ^= nums[i];
        }
    }

    arr = malloc (4 * 2);
    if (arr) {
        printf ("\n a=%d b=%d \n", a, b);
        arr[0] = a;
        arr[1] = b;
        (*returnSize) = 2;
    }
    return arr;
}

bool test_single_number (void) {
    int arr[] = {1, 2, 1, 3, 2, 5};
    int returnSize = 0;
    int sizeOfnum = sizeof (arr) / sizeof (arr[0]);
    int *outArr;
    outArr = singleNumber (arr, sizeOfnum, &returnSize);
    if (3 == outArr[0]) {
        if (5 == outArr[1]) {
            free (outArr);
            return true;
        }
    }
    if (5 == outArr[0]) {
        if (3 == outArr[1]) {
            free (outArr);
            return true;
        }
    }

    return false;
}

//{1,1,1,1,1,1,1,1}
//{0,0,0,1,1,1,1,1}
static int count_con_one (int *const arr, int sizeOfArr, int indexToDet) {
    int curAmountOfones = 0;
    int maxOnes = 0;
    if (indexToDet < sizeOfArr) {
        int prevVal = 1; //!
        for (int i = 0; i < sizeOfArr; i++) {
            if (indexToDet != i) {
                if (1 == prevVal) {
                    if (1 == arr[i]) {
                        curAmountOfones++;
                        if ((sizeOfArr - 1) == i) {
                            maxOnes = update_max (maxOnes, curAmountOfones);
                        }
                    } else {
                        // 0==arr[i]
                        curAmountOfones = 0;
                        maxOnes = update_max (maxOnes, curAmountOfones);
                    }
                } else {
                    // 0==prevVal
                    if (1 == arr[i]) {
                        curAmountOfones = 1;
                        if ((sizeOfArr - 1) == i) {
                            maxOnes = update_max (maxOnes, curAmountOfones);
                        }

                    } else {
                        // 0==arr[i]
                        curAmountOfones = 0;
                    }
                }
            }
            prevVal = arr[i];
        }
    }
    return maxOnes;
}

//{1 0} indexToArr=1
bool is_single_zero (int *const arr, int sizeOfArr, int indexToArr) {
    bool res = false;
    // TODO: 0<sizeOfArr
    if (0 == arr[indexToArr]) {
        if (1 == sizeOfArr) {
            return true;
        }
        if (0 == indexToArr) {
            if (1 == arr[1] && (2 <= sizeOfArr)) {
                return true;
            }
        } else if (indexToArr == (sizeOfArr - 1)) {
            if (1 == arr[indexToArr - 1]) {
                return true;
            }
        } else {
            if ((1 == arr[indexToArr - 1]) && (1 == arr[indexToArr + 1]) && (3 <= sizeOfArr)) {
                return true;
            }
        }
    }
    return res;
}

// return the amount of seq one
int count_max_amout_of_one_after_del (int *arr, int sizeOfArr) {
    printf ("\n %s %d\n", __FUNCTION__, sizeOfArr);
    bool res = false;
    int curMaxOnes = 0;
    int maxOnes = 0;
    for (int i = 0; i < sizeOfArr; i++) {
        res = is_single_zero (arr, sizeOfArr, i);
        if (true == res) {
            curMaxOnes = count_con_one (arr, sizeOfArr, i);
            if (maxOnes < curMaxOnes) {
                maxOnes = curMaxOnes;
            }
        }
    }
    return maxOnes;
}

int findMaxConsecutiveOnes (int *nums, int numsSize) {
    int currentCount = 0;
    int curMax = 0;
    for (int i = 0; i < numsSize; i++) {
        if (0 == nums[i]) {
            currentCount = 0;
        } else {
            currentCount++;
        }
        curMax = max_int (curMax, currentCount);
    }
    return curMax;
}

//    xor
// 00   0
// 01   1
// 10   1
// 11   0
// O(N) Solution
int findMaxConsecutiveOnesFlip1 (int *nums, int length) {
    int count[2] = {0};
    int index = 0;
    int maxConOne = 0;
    bool zero = false;
    for (int i = 0; i < length; i++) {
        if (nums[i] == 1) {
            count[index]++;
            maxConOne = max_int (maxConOne, count[0] + count[1]);
        } else {
            zero = true;
            index = index ^ 1; // 0->1   1->0
            count[index] = 0;
        }
    }
    if (zero == true) {
        // maxConOne++;
    }
    printf ("\n%d %d", count[0], count[1]);
    return maxConOne;
}

// O(n)
int findMaxConOnesDel1 (int *const array, int length) {
    int maxConOne = 0, prevOneCnt = 0, oneCnt = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] == 0) {
            prevOneCnt = oneCnt;
            oneCnt = 0;
        } else {
            oneCnt++;
        }
        maxConOne = max_int (maxConOne, oneCnt + prevOneCnt);
    }
    return maxConOne;
}

void *memdup (const void *mem, size_t sizeByte) {
    void *out = NULL;
    if (0 < sizeByte) {
        if (NULL != mem) {
            out = (void *)malloc (sizeByte);
            if (NULL != out) {
                memcpy ((void *)out, (void *)mem, sizeByte);
            } else {
                printf ("\n Unable to malloc [%u] byte\n", (unsigned int)sizeByte);
            }
        } else {
            printf ("NUll Array pointer!");
        }
    } else {
        printf ("\n0 size array!");
    }
    return out;
}

//
int *add_val_to_end_array (int *in_arr, int arrSize, int val) {
    int *newArr = NULL;
#if DEBUG_ADD_VAL_TO_END_ARRAY
    printf ("\n %s start", __FUNCTION__);
#endif
    newArr = malloc (sizeof (int) * (arrSize + 1));
    if (newArr) {
        if (NULL != in_arr) {
            if (0 < arrSize) {
#if DEBUG_ADD_VAL_TO_END_ARRAY
                printf ("\n");
                print_curr_array (in_arr, arrSize);
                printf ("\n");
#endif
                memcpy (newArr, in_arr, sizeof (int) * (arrSize));
                // in_arr must not be free here
            }
        }
        newArr[arrSize] = val;
#if DEBUG_ADD_VAL_TO_END_ARRAY
        printf ("\n");
        print_curr_array (newArr, arrSize + 1);
        printf ("\n");
#endif
    } else {
#if DEBUG_ADD_VAL_TO_END_ARRAY
        printf ("\n Unable to accoc [%d] byte", arrSize);
#endif
        newArr = NULL;
    }
#if DEBUG_ADD_VAL_TO_END_ARRAY
    printf ("\n %s end", __FUNCTION__);
#endif
    return newArr;
}
//[in_arr 1 0]
//[in_arr 2 1]
// {11 22} 2 1
int *remove_int_from_arr (int *in_arr, int arrSize, int delIndex) {
#ifdef DEBUG_REMOVE_INT_FROM_ARR
    printf ("\n %s size: %u delInd %u", __FUNCTION__, arrSize, delIndex);
#endif
    int *newArr = NULL;
    if (NULL != in_arr) {
        if (delIndex < arrSize) {
            if (2 <= arrSize) {
                int index = 0;
                for (index = delIndex; index < (arrSize - 1); index++) {
                    in_arr[index] = in_arr[index + 1];
                }
                in_arr[arrSize] = 0;
                newArr = in_arr;
            } else if (1 == arrSize) {
                newArr = NULL;
            } else {
                printf ("%s in Array 0 size", __FUNCTION__);
            }
        } else {
            printf ("arrSize: %d delIndex: %d", arrSize, delIndex);
        }
    } else {
        printf ("\n In array NULL");
    }
    return newArr;
}

int *generate_num_array_malloc (int n) {
    int *outArray = NULL;
    outArray = malloc (sizeof (int) * (n));
    if (outArray) {
        for (int i = 0; i < n; i++) {
            outArray[i] = (i);
        }
    }
    return outArray;
}

bool is_correct_permutation (int *arraOfIndex, int n, int maxVal) {
    bool res = false;
    if (arraOfIndex) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (arraOfIndex[i] < maxVal) {
                cnt++;
            }
        }
        if (n == cnt) {
            res = true;
        }
    }
    return res;
}

void print_mem (unsigned char *array, int num) {
    if (array) {
        if (0 < num) {
            for (int i = 0; i < num; i++) {
                printf ("%02x ", array[i]);
            }
            printf ("\n");
        }
    }
}

void print_curr_array (int *array, int num) {
    if (array) {
        if (0 < num) {
            printf ("\n");
            for (int i = 0; i < num; i++) {
                printf ("%d ", array[i]);
            }
        }
    }
}

void print_array_of_arrays (int **arrOfArr, int amountOfLine, int amountOfCol) {
    if (NULL != arrOfArr) {
        printf ("\n amountOfLine %d \n", amountOfLine);
        for (int line = 0; line < amountOfLine; line++) {
            printf ("\n %d: ", line + 1);
            print_array_int ((int *)arrOfArr[line], amountOfCol);
        }
    }
}

void print_array_of_diff_arrays (int **arrOfArr, int amountOfLine, int *colSizes) {
    if (arrOfArr) {
        if (colSizes) {
            for (int line = 0; line < amountOfLine; line++) {
                if (arrOfArr[line]) {
                    if (colSizes[line]) {
                        print_curr_array (arrOfArr[line], colSizes[line]);
                    }
                }
            }
        }
    }
}

void print_array_to_file_pointer (FILE *filePointer, int *array, int size) {
    int i = 0;
    if (filePointer) {
        for (i = 0; i < size; i++) {
            fprintf (filePointer, "%d ", array[i]);
        }
        fprintf (filePointer, "\n");
    }
}

void print_array_to_filename (char *filename, int *array, int size) {
    int i = 0;
    FILE *filePointer;
    filePointer = fopen (filename, "a");
    if (filePointer) {
        for (i = 0; i < size; i++) {
            fprintf (filePointer, "%d ", array[i]);
        }
        fprintf (filePointer, "\n");
    }
}

uint64_t sum_arr (uint32_t *arr, uint32_t size) {
    uint64_t sum = 0;
    for (uint32_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float calc_avarage (uint32_t *arr, uint32_t size) {
    float avarage = 0.0;
    if (0 < size) {
        uint64_t sum = sum_arr (arr, size);
        avarage = (float)sum / (float)size;
    }
    return avarage;
}

bool concatenate_array (uint8_t *out_fin_array, uint32_t fin_array_len, uint8_t *in_array1, uint32_t in_array1_len,
                        uint8_t *in_array2, uint32_t in_array2_len) {
    bool res = false;
    if (NULL != out_fin_array) {
        if ((in_array1_len + in_array2_len) <= fin_array_len) {
            memcpy (out_fin_array, in_array1, in_array1_len);
            memcpy (&out_fin_array[in_array1_len], in_array2, in_array2_len);
        }
    }
    return res;
}

int *find_common(int *arr1, int len1,
                int *arr2, int len2) {

    bool loop = true;
    int index1=0, cnt=0;
    int index2=0;

    int *result_arr = malloc(min(len1,len2)*sizeof(int));
    if(result_arr) {
        while(true==loop) {
            if(arr2[index2]<arr1[index1]) {
               index2++;
            }else if(arr2[index2]==arr1[index1]) {
               result_arr[cnt]=arr1[index1];
               cnt++;
               index1++;
               index2++;
            }else {
                //b>a
                index1++;
            }
            if(len1<=index1) {
            	loop = false;
            }
            if(len2<=index2) {
               	loop = false;
            }
       }
       return result_arr;
    }
    return NULL;
}
