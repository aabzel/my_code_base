#include "brick_wall.h"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

int leastBricks (vector<vector<int>> &wall) {
    cout << "num of rows is wall " << wall.size () << endl;
    map<int, int> gap_histogram;
    int max_gap_cnt = 0;
    for (int line = 0; line < wall.size (); line++) {
        int indent = 0;
        for (int brick = 0; brick < wall[line].size () - 1; brick++) {
            indent += wall[line][brick];
            // register a gap
            auto itr = gap_histogram.find (indent);
            if (gap_histogram.end () == itr) {
                gap_histogram.insert ({indent, 1});
                max_gap_cnt = max (max_gap_cnt, 1);
            } else {
                itr->second++;
                max_gap_cnt = max (max_gap_cnt, itr->second);
            }
        }
    }
    print_map (gap_histogram);
    cout << "max_gap_cnt " << max_gap_cnt << endl;
    return wall.size () - max_gap_cnt;
}
