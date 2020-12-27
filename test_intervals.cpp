#include <algorithm>
#include <vector>

#include "intervals.h"

#include "uTests.h"

using namespace std;

bool test_remove_Covered_Intervals(void) {
	vector<vector<int>> intervals = {{1,4},{3,6},{2,8}};
	EXPECT_EQ(2, removeCoveredIntervals(intervals)) ;
	return true;
}
