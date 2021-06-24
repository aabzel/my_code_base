#include "test_min_num_of_swaps.h"

#include <iostream>
#include <vector>

#include "uTests.h"
#include "min_num_of_swaps.h"

using namespace std;

static bool test_min_swaps5(void) {
	cout << __FUNCTION__<< endl;
    int num = 0;
	vector <int> arr = {7, 6, 4, 2, 5, 3, 1};  
	num = minSwaps(arr);
	EXPECT_EQ(3,num);
	return true;
}


static bool test_min_swaps4(void) {
	cout << __FUNCTION__<< endl;
    int num = 0;
	vector <int> arr = {2, 1, 3, 4}; 
	num = minSwaps(arr);
	EXPECT_EQ(3,num);
	return true;
}


static bool test_min_swaps3(void) {
	cout << __FUNCTION__<< endl;
    int num;
	vector <int> arr={2, 3, 4, 5, 1};
	num = minSwaps(arr);
	EXPECT_EQ(2,num);
	return true;
}


static bool test_min_swaps2(void) {
	cout << __FUNCTION__<< endl;
    int num;
	vector <int> arr={4, 3, 1, 2, 4};   
	num = minSwaps(arr);
	EXPECT_EQ(2,num);
	return true;
}

static bool test_min_swaps1(void) {
	cout << __FUNCTION__ << endl;
    int num;
	vector <int> arr = {6, 5, 4, 2, 3, 1, 7}; 
	num = minSwaps(arr);
	EXPECT_EQ(5,num);
	return true;
}


bool test_min_swaps(void) {
    int num;
	cout << __FUNCTION__<< endl;
	EXPECT_TRUE(test_min_swaps5());
	EXPECT_TRUE(test_min_swaps4());
	EXPECT_TRUE(test_min_swaps2());
	EXPECT_TRUE(test_min_swaps3());
	EXPECT_TRUE(test_min_swaps1());
	return true;
}
