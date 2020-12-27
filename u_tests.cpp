// hello.cpp
#include <iostream>

#include "uTests.h"
#include "test_intervals.h"

using namespace std;
 
bool u_tests(void) {
   cout << "utests" << endl;
   EXPECT_TRUE( test_remove_Covered_Intervals( ));
   return true;
}
