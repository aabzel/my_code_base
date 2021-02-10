#include <algorithm>
#include <iostream>
#include <vector>

#include "test_interval_list_intersections.h"

#include "interval_list_intersections.h"
#include "uTests.h"
#include "utils_cpp.h"

using namespace std;

bool test_interval_list_intersections (void) {
    cout << __FUNCTION__ << endl;
    vector<vector<int>> new_intervals;

    vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    vector<vector<int>> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<vector<int>> intervals3 = {{1, 5}};
    vector<vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> intervals4 = {{0, 2},   {4, 6},   {10, 11}, {14, 15}, {18, 20},
                                      {26, 26}, {31, 31}, {35, 42}, {43, 47}, {49, 52}};

    vector<vector<int>> intervals5 = {{0, 2}, {5, 10}, {13, 23}, {24, 25}};
    vector<vector<int>> intervals6 = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};
    new_intervals = intervalIntersection (intervals5, intervals6); //{2 3 }
    print_intervals (new_intervals);

    new_intervals = intervalIntersection (intervals1, intervals4); //{2 3 }
    print_intervals (new_intervals);

    new_intervals = intervalIntersection (intervals4, intervals3);
    print_intervals (new_intervals);

    new_intervals = intervalIntersection (intervals3, intervals);
    print_intervals (new_intervals);

    new_intervals = intervalIntersection (intervals, intervals2);
    print_intervals (new_intervals);

    new_intervals = intervalIntersection (intervals2, intervals1);
    print_intervals (new_intervals);

    return true;
}
