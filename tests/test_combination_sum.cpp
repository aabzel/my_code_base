#include "test_combination_sum.h"

#include <iostream>
#include <vector>

#include "combination_sum.h"
#include "uTests.h"
#include "utils_cpp.h"

using namespace std;

bool test_combination_sum(void) {
    cout << __FUNCTION__ << endl;
	vector<int> candidates1 = {2,3,5};
	vector<vector<int>> table1 = combinationSum(candidates1, 8);
	print_vectors(table1);
	EXPECT_EQ(3,table1.size());
	
	vector<int> candidates2 = {2};
	vector<vector<int>> table2 = combinationSum(candidates2, 1);
	print_vectors(table2);
	EXPECT_EQ(0,table2.size());	
	
	
	vector<int> candidates3 = {1};
	vector<vector<int>> table3 = combinationSum(candidates3, 1);
	print_vectors(table3);
	EXPECT_EQ(1,table3.size());	

	vector<int> candidates4 = {1};
	vector<vector<int>> table4 = combinationSum(candidates4, 2);
	print_vectors(table4);
	EXPECT_EQ(1,table4.size());	
	
    return true;
}
