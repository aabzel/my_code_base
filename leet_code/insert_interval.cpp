#include "insert_interval.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "interval_api.h"
#include "merge_interval.h"
#include "utils_cpp.h"

using namespace std;

static bool comparator_time (intrvEvent_t const &a, intrvEvent_t const &b) { return a.time < b.time; }

vector<vector<int>> insert_interval (vector<vector<int>> &intervals, vector<int> &newInterval) {
#ifdef DEBUG_INSERT_INTERVAL
    cout << __FUNCTION__ << endl;
#endif
    vector<vector<int>> new_intervals;
    intervals.push_back(newInterval);
    new_intervals = merge_interval(intervals);
    return new_intervals;
}
