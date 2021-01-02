#include <algorithm>
#include <vector>
#include <iostream>

#include "intervals.h"

#include "uTests.h"

using namespace std;

#include <string.h>


int init_by_foo5(void){
	//cout <<__BASE_FILE__ <<" "<<__FUNCTION__<<"() line "<<__LINE__ << endl;
	cout <<BASENAME() <<" "<<__FUNCTION__<<"() line "<<__LINE__ << endl;
	return 5;
}

int init_by_foo6(void){
	cout <<BASENAME() <<" "<<__FUNCTION__<<"() line "<<__LINE__ << endl;
	return 6;
}

int a_val5=init_by_foo5();
int a_val6=init_by_foo6();


bool test_remove_Covered_Intervals(void) {
	cout << "test_remove_Covered_Intervals" << endl;
	vector<vector<int>> intervals = {{1,4},{3,6},{2,8}};
	EXPECT_EQ(2, removeCoveredIntervals(intervals)) ;
	return true;
}
