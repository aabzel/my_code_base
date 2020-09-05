#include "bin_utils_test.h"

#include "bin_utils.h"

bool test_binary_gap (void) {
    int gap;
    gap = binary_gap (529); // 10 0001 0001
    if (4 != gap) {
        printf ("\ngap %u 2", gap);
        return false;
    }
    gap = binary_gap (1041);
    if (5 != gap) {
        printf ("\ngap %u 5", gap);
        return false;
    }
    gap = binary_gap (9);
    if (2 != gap) {
        printf ("\ngap %u 2", gap);
        return false;
    }
    gap = binary_gap (20);
    if (1 != gap) {
        printf ("\ngap %u 1", gap);
        return false;
    }
    return true;
}
