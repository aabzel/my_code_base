#include "algorithms_test.h"

#include "algorithms.h"

bool test_algorithm (void) {
    bool res;
    res = test_splitting_sum ();
    if (false == res) {
        return false;
    }
    return true;
}

bool test_splitting_sum (void) {
    int alf[6] = {1, 2, 3, 4, 5, 6};
    int *syllables = malloc (sizeof (int) * 6);
    print_terms (2, alf, 6, 12, syllables);

    return true;
}
