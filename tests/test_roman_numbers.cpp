#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "roman_to_numbers.h"
#include "test_roman_numbers.h"
#include "uTests.h"
#include "utils_cpp.h"

bool test_roman_numbers (void) {
    cout << __FUNCTION__ << endl;
    EXPECT_EQ (1, romanToInt ("I"));
    EXPECT_EQ (58, romanToInt ("LVIII"));
    EXPECT_EQ (1994, romanToInt ("MCMXCIV"));
    EXPECT_EQ (1000, romanToInt ("M"));
    EXPECT_EQ (3, romanToInt ("III"));
    EXPECT_EQ (4, romanToInt ("IV"));
    EXPECT_EQ (9, romanToInt ("IX"));
    cout << __FUNCTION__ << " Fine " << endl;
    return true;
}
