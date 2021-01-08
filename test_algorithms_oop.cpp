#include "test_algorithms_oop.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "algorithms_oop.h"
#include "uTests.h"

using namespace std;

bool test_findDuplicate (void) {
    cout << __FUNCTION__ << endl;
    vector<int> nums3 = {3, 1, 3, 4, 2};
    EXPECT_EQ (3, findDuplicate (nums3));
    vector<int> nums2 = {1, 3, 4, 2, 2};
    EXPECT_EQ (2, findDuplicate (nums2));
    vector<int> nums1 = {1, 1};
    EXPECT_EQ (1, findDuplicate (nums1));
    return true;
}

bool test_singleNumber (void) {
    cout << __FUNCTION__ << endl;
    vector<int> nums1 = {1};
    EXPECT_EQ (1, singleNumber_cpp (nums1));
    vector<int> nums2 = {2, 2, 1};
    EXPECT_EQ (1, singleNumber_cpp (nums2));
    vector<int> nums4 = {4, 1, 2, 1, 2};
    EXPECT_EQ (4, singleNumber_cpp (nums4));
    return true;
}
