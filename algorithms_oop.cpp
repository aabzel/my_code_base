#include "algorithms_oop.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

#include "utils_cpp.h"

using namespace std;

int findDuplicate (vector<int> &nums) {
    set<int> intSet;
    for (int i = 0; i < nums.size (); i++) {
        // cout <<"nums["<<i<<"] " << nums[i]<< endl;
        if (intSet.find (nums[i]) == intSet.end ()) {
            intSet.insert (nums[i]);
        } else {
            return nums[i];
        }
        // Do something with i
    }
    return -1;
}

int singleNumber_cpp (vector<int> &nums) {
    map<int, int> int_histogram;
    for (int i = 0; i < nums.size (); i++) {
        // cout <<"nums["<<i<<"] " << nums[i]<< endl;
        auto itr = int_histogram.find (nums[i]);
        if (itr == int_histogram.end ()) {
            int_histogram.insert ({nums[i], 1});
        } else {
            itr->second++;
        }
        // Do something with i
    }
    // print_map (int_histogram);
    map<int, int>::iterator itr;
    for (itr = int_histogram.begin (); itr != int_histogram.end (); ++itr) {
        // cout << ' ' << itr->first << ' ' << itr->second << '\n';
        if (1 == itr->second) {
            return itr->first;
        }
    }

    return -1;
}
