#include "compare_version_test.h"

#include "compare_version.h"

bool compare_version_test (void) {
    int cmp_res, rank;
    int val;
    rank = calc_rank ("1.0");
    if (2 != rank) {
    	printf("\nrank %u exp 2",rank);
        return false;
    }
    rank = calc_rank ("1");
    if (1 != rank) {
    	printf("\nrank %u exp 1",rank);
        return false;
    }

    rank = calc_rank ("7.5.2.4");
    if (4 != rank) {
    	printf("rank %u exp 4",rank);
        return false;
    }

    val = extract_val ("7.5.2.4", 0, 4);
    if (7 != val) {
    	printf("\nval %u exp 7",val);
        return false;
    }

    val = extract_val ("7.5.2.4", 1, 4);
    if (5 != val) {
    	printf("\nval %u exp 5",val);
        return false;
    }

    val = extract_val ("7.5.2.4", 3, 4);
    if (4 != val) {
    	printf("\nval %u exp 4",val);
        return false;
    }

    cmp_res = compareVersion ("1.0", "1.0.0");
    if (0 != cmp_res) {
    	printf("\ncmp_res %u exp 0",cmp_res);
        return false;
    }
    cmp_res = compareVersion ("1.01", "1.001");
    if (0 != cmp_res) {
    	printf("cmp_res %u exp 0",cmp_res);
        return false;
    }
    cmp_res = compareVersion ("7.5.2.4", "7.5.3");
    if (-1 != cmp_res) {
    	printf("cmp_res %u exp -1",cmp_res);
        return false;
    }
    cmp_res = compareVersion ("0.1", "1.1");
    if (-1 != cmp_res) {
    	printf("cmp_res %u exp -1",cmp_res);
        return false;
    }

    cmp_res = compareVersion ("1.0.1", "1");
    if (1 != cmp_res) {
    	printf("cmp_res %u exp 1",cmp_res);
        return false;
    }
    return true;
}
