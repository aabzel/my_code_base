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

bool test_find_first_absent (void) {
    cout << __FUNCTION__ << endl;
    vector<int> nums1 = {1};
    EXPECT_EQ (2, find_first_absent (nums1));
    vector<int> nums2 = {2, 2, 1};
    EXPECT_EQ (3, find_first_absent (nums2));
    vector<int> nums4 = {4, 1, 2, 1, 2};
    EXPECT_EQ (3, find_first_absent (nums4));

    vector<int> nums3 = {2, 3, 0};
    EXPECT_EQ (1, find_first_absent (nums3));
    return true;
}

bool test_return_unique (void) {
    cout << __FUNCTION__ << endl;
    vector<int> out_nums;
    vector<int> in_nums1 = {1, 2, 2, 1, 1, 3};
    vector<int> exp_nums = {1, 2, 3};
    out_nums = return_unique (in_nums1);
    EXPECT_VEC_EQ (exp_nums, out_nums);
    return true;
}

bool test_uniqueOccurrences (void) {
    cout << __FUNCTION__ << endl;
    vector<int> in_nums1 = {1, 2, 2, 1, 1, 3};
    EXPECT_FALSE (uniqueOccurrences (in_nums1));

    vector<int> in_nums2 = {1, 2, 3};
    EXPECT_TRUE (uniqueOccurrences (in_nums2));

    return true;
}
