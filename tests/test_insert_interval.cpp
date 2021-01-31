#include <algorithm>
#include <iostream>
#include <vector>

#include "insert_interval.h"
#include "uTests.h"
#include "utils_cpp.h"

using namespace std;

bool test_insert_interval (void) {
    cout << __FUNCTION__ << endl;
    vector<vector<int>> new_intervals;

    vector<int> in_interval4 ={59,62};
    vector<vector<int>> intervals4 = {    {0,2},{4,6},{10,11},{14,15},{18,20},{26,26},{31,31},{35,42},{43,47},{49,52}};

    new_intervals = Insert_Interval(intervals4, in_interval4);
    print_intervals(new_intervals);

#if 0
    vector<int> in_interval3 ={5,7};
    vector<vector<int>> intervals3 = {{1,5}};
    new_intervals = Insert_Interval(intervals3, in_interval3);
    print_intervals(new_intervals);


    vector<int> in_interval ={2,5};
    vector<vector<int>> intervals = {{1,3},{6,9}};
    new_intervals = Insert_Interval(intervals, in_interval);
    print_intervals(new_intervals);

    vector<int> in_interval2 ={4,8};
    vector<vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    new_intervals = Insert_Interval(intervals2, in_interval2);
    print_intervals(new_intervals);
#endif

    return true;
}
