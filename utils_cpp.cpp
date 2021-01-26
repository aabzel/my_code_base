#include "utils_cpp.h"

#include <iostream>

void print_map (map<int, int> histogram) {

    map<int, int>::iterator itr;
    for (itr = histogram.begin (); itr != histogram.end (); ++itr) {
        cout << ' ' << itr->first << ' ' << itr->second << '\n';
    }
}

void print_vector (vector<vector<int>> &intervals) {
    cout << endl;
    for (int i = 0; i < intervals.size (); i++) {
        cout << "[";
        for (int j = 0; j < intervals[i].size (); j++) {
            cout << intervals[i].at (j) << ' ';
        }
        cout << "]";
    }
    cout << endl;
    cout << endl;
}

void print_vector_strs (vector<string> words) {
    cout << __FUNCTION__ << endl;
    cout << endl;
    for (int i = 0; i < words.size (); i++) {
        cout << "[";
        cout << words[i] << ' ';
        cout << "]" << endl;
    }
    cout << endl;
}
