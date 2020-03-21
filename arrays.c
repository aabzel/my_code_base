#include "arrays.h"

#include "array_type.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int update_max (int curMax, int newVal) {
    int newMax = 0;
    if (curMax < newVal) {
        newMax = newVal;
    } else {
        newMax = curMax;
    }
    return newMax;
}

//{1,1,1,1,1,1,1,1}
//{0,0,0,1,1,1,1,1}
static int count_con_one (int * const arr, int sizeOfArr, int indexToDet) {
    int curAmountOfones = 0;
    int maxOnes = 0;
    if (indexToDet < sizeOfArr) {
        int prevVal = 1; //!
        for (int i = 0; i < sizeOfArr; i++) {
            if (indexToDet != i) {
                if (1 == prevVal) {
                    if (1 == arr [i]) {
                        curAmountOfones++;
                        if ((sizeOfArr - 1) == i) {
                            maxOnes = update_max (maxOnes, curAmountOfones);
                        }
                    } else {
                        //0==arr[i]
                        curAmountOfones = 0;
                        maxOnes = update_max (maxOnes, curAmountOfones);
                    }
                } else {
                    //0==prevVal
                    if (1 == arr [i]) {
                        curAmountOfones = 1;
                        if ((sizeOfArr - 1) == i) {
                            maxOnes = update_max (maxOnes, curAmountOfones);
                        }

                    } else {
                        //0==arr[i]
                        curAmountOfones = 0;
                    }

                }
            }
            prevVal = arr [i];
        }
    }
    return maxOnes;
}

//{1 0} indexToArr=1
bool is_single_zero (int * const arr, int sizeOfArr, int indexToArr) {
    bool res = false;
    //TODO: 0<sizeOfArr
    if (0 == arr [indexToArr]) {
        if (1 == sizeOfArr) {
            return true;
        }
        if (0 == indexToArr) {
            if (1 == arr [1] && (2 <= sizeOfArr)) {
                return true;
            }
        } else if (indexToArr == (sizeOfArr - 1)) {
            if (1 == arr [indexToArr - 1]) {
                return true;
            }
        } else {
            if ((1 == arr [indexToArr - 1]) && (1 == arr [indexToArr + 1]) && (3 <= sizeOfArr)) {
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

void* memdup (const void* mem, size_t sizeByte) {
    void* out = NULL;
    if (0 < sizeByte) {
        if (mem) {
            out = malloc (sizeByte);
            if (NULL != out) {
                memcpy (out, mem, sizeByte);
            }
        } else {
            printf ("NUll Array pointer!");
        }
    } else {
        printf ("NUll Array!");
    }

    return out;
}

int *add_val_to_end_array (int *inArr, int arrSize, int val) {
    int *newArr = NULL;
    newArr = malloc (sizeof(int) * (arrSize + 1));
    if (newArr) {
        if (inArr) {
            memcpy (newArr, inArr, sizeof(int) * arrSize);
        }
        newArr [arrSize] = val;
    } else {
        printf ("Unable to accoc");
    }
    return newArr;
}

int *remove_int_from_arr (int *inArr, int arrSize, int delIndex) {
    int *newArr = NULL;
    if (delIndex < arrSize) {
        newArr = malloc (sizeof(int) * arrSize);
        memcpy (newArr, inArr, sizeof(int) * arrSize);
        int index = 0;
        for (index = delIndex; index < (arrSize - 1); index++) {
            newArr [index] = newArr [index + 1];
        }
    } else {
        printf ("arrSize: %d delIndex: %d", arrSize, delIndex);
    }
    return newArr;
}

int *generate_num_array (int n) {
    int *outArray = NULL;
    outArray = malloc (sizeof(int) * (n));
    for (int i = 0; i < n; i++) {
        outArray [i] = (i);
    }

    return outArray;
}

void print_curr_array (int *alphabet, int sizeOfAlphabet) {
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("[%d]", alphabet [i]);
    }
    printf ("\n");
}

void print_array_of_arrays (int **arrOfArr, int amountOfLine, int amountOfCol) {
    if (arrOfArr) {
        for (int line = 0; line < amountOfLine; line++) {
            print_curr_array (arrOfArr [line], amountOfCol);
        }
    }
}

void print_array_of_diff_arrays (int **arrOfArr, int amountOfLine, int *colSizes) {
    if (arrOfArr) {
        if (colSizes) {
            for (int line = 0; line < amountOfLine; line++) {
                if (arrOfArr [line]) {
                    if (colSizes [line]) {
                        print_curr_array (arrOfArr [line], colSizes [line]);
                    }
                }
            }
        }
    }
}

void print_array_to_file_pointer (FILE * filePointer, int *array, int size) {
    int i = 0;
    if (filePointer) {
        for (i = 0; i < size; i++) {
            fprintf (filePointer, "%d ", array [i]);
        }
        fprintf (filePointer, "\n");
    }
}

void print_array_to_filename (char *filename, int *array, int size) {
    int i = 0;
    FILE * filePointer;
    filePointer = fopen (filename, "a");
    if (filePointer) {
        for (i = 0; i < size; i++) {
            fprintf (filePointer, "%d ", array [i]);
        }
        fprintf (filePointer, "\n");
    }
}
