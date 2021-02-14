#include "test_majority_element.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "majority_element.h"
#include "uTests.h"

using namespace std;

bool test_majority_element (void) {
    cout << __FUNCTION__ << endl;
    vector<int> vc = {1, 1, 1, 2, 2};
    EXPECT_EQ (1, majority_element (vc));

    vector<int> va = {3, 2, 3};
    EXPECT_EQ (3, majority_element (va));

    vector<int> vb = {2, 2, 1, 1, 1, 2, 2};
    EXPECT_EQ (2, majority_element (vb));

    return true;
}
