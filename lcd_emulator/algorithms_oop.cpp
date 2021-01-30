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

vector<int> removeDuplicates (vector<int> nums) {

    int i;
    vector<int> outVector;
    // Initialise a set
    // to store the array values
    set<int> intSet;

    // Insert the array elements
    // into the set
    for (i = 0; i < nums.size (); i++) {

        // insert into set
        intSet.insert (nums[i]);
    }

    set<int>::iterator it;

    // Print the array with duplicates removed
    cout << "\nAfter removing duplicates:\n";
    for (it = intSet.begin (); it != intSet.end (); it++) {
        cout << *it << ", ";
        outVector.push_back ((int)*it);
    }
    return outVector;
}

int find_first_absent (vector<int> nums) {
    cout << __FUNCTION__ << endl;
    nums = removeDuplicates (nums);
    sort (nums.begin (), nums.end (), less<int> ());
    int contineous = 0;
    int min = *min_element (begin (nums), end (nums));
    int max = *max_element (begin (nums), end (nums));
    // cout << " ["<< min << " " << max << "]"  <<endl;
    bool is_spot = false;
    contineous = min;
    for (int i = 0; i < nums.size (); i++) {
        // cout << " ["<< i << "]=" << nums[i] <<" con:"<< contineous  << endl;
        if (contineous != nums[i]) {
            is_spot = true;
            // cout << __FUNCTION__ <<" done"<< endl;
            return contineous;
        }
        contineous++;
    }
    if (false == is_spot) {
        // cout << " lack"<< endl;
        contineous = max + 1;
    }
    // cout << __FUNCTION__ <<" done"<< endl;
    return contineous;
}

vector<int> return_unique (vector<int> nums) {
    vector<int> unique;
    set<int> intSet;
    for (int i = 0; i < nums.size (); i++) {
        if (intSet.find (nums[i]) == intSet.end ()) {
            intSet.insert (nums[i]);
            unique.push_back (nums[i]);
        }
    }
    return unique;
}

bool uniqueOccurrences (vector<int> &arr) {
    set<int> intSet;
    for (int i = 0; i < arr.size (); i++) {
        if (intSet.find (arr[i]) == intSet.end ()) {
            intSet.insert (arr[i]);
        } else {
            return false;
        }
    }
    return true;
}
