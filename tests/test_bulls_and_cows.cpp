#include "test_bulls_and_cows.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "bulls_and_cows.h"
#include "uTests.h"

using namespace std;

bool test_bulls_and_cows (void) {
    cout << __FUNCTION__ << endl;
    // 1 2
    // 2 1
    // 3 1

    // 0 1
    // 1 3
    EXPECT_EQ_STR_CPP ("3A0B", getHint ("1122", "1222"));

    EXPECT_EQ (3, count_max_cows ("1122", "1222"));
    EXPECT_EQ (2, count_max_cows ("1123", "0111"));
    // 1222
    // 1122

    EXPECT_EQ_STR_CPP ("1A0B", getHint ("1", "1"));
    EXPECT_EQ_STR_CPP ("0A0B", getHint ("1", "0"));
    EXPECT_EQ_STR_CPP ("1A3B", getHint ("1807", "7810"));
    EXPECT_EQ_STR_CPP ("1A1B", getHint ("1123", "0111"));
    return true;
}
