#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "merge_interval.h"
#include "uTests.h"
#include "utils_cpp.h"

bool test_merge_interval (void) {
    cout << __FUNCTION__ << endl;
    vector<vector<int>> new_intervals;

    vector<vector<int>> intervals44 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    new_intervals = merge_interval (intervals44);
    print_intervals (new_intervals);

#if 1
    vector<vector<int>> intervals4 = {{0, 2},   {4, 6},   {10, 11}, {14, 15}, {18, 20},
                                      {26, 26}, {31, 31}, {35, 42}, {43, 47}, {49, 52}};
    new_intervals = merge_interval (intervals4);
    print_intervals (new_intervals);

    vector<vector<int>> intervals3 = {{1, 5}};
    new_intervals = merge_interval (intervals3);
    print_intervals (new_intervals);

    vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    new_intervals = merge_interval (intervals);
    print_intervals (new_intervals);

    vector<vector<int>> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    new_intervals = merge_interval (intervals2);
    print_intervals (new_intervals);
#endif

    return true;
}
