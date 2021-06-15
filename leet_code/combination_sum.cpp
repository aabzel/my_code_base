#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "utils_cpp.h"

using namespace std;

bool build_solution(vector<vector<int>>& sol_table, vector<int>& candidates, vector<int> cur_collection, int target) {
    bool res = false;
    int sum_of_elems = accumulate(cur_collection.begin(), cur_collection.end(), 0);
#if DDEBUG_COMBINATION_SUM
    cout << "  " << __FUNCTION__ << " sum_of_elems: " << sum_of_elems << endl;
    print_vector_ints(cur_collection);
#endif
    if (target == sum_of_elems) {
#if DDEBUG_COMBINATION_SUM
        cout << "spot solution" << endl;
#endif
        sort(cur_collection.begin(), cur_collection.end());
        if (find(sol_table.begin(), sol_table.end(), cur_collection) == sol_table.end()) {
            sol_table.push_back(cur_collection);
            res = true;
        }
    } else if (sum_of_elems < target) {
        for (int i = 0; i < candidates.size(); i++) {
            vector<int> init_cur_collection = cur_collection;
            init_cur_collection.push_back(candidates[i]);
            res = build_solution(sol_table, candidates, init_cur_collection, target);
        }
    } else {
        res = false;
    }
    return res;
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
#if DDEBUG_COMBINATION_SUM
    cout << __FUNCTION__ << endl;
#endif
    vector<vector<int>> sol_table;
    for (int i = 0; i < candidates.size(); i++) {
        vector<int> cur_collection;
        cur_collection.push_back(candidates[i]);
        build_solution(sol_table, candidates, cur_collection, target);
    }
    return sol_table;
}
