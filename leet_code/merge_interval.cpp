#include "merge_interval.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "interval_api.h"
#include "utils_cpp.h"

using namespace std;

static bool comparator_time (intrvEvent_t const &a, intrvEvent_t const &b) { return a.time < b.time; }


vector<vector<int>> merge_interval (vector<vector<int>> &intervals) {
#ifdef DEBUG_MERGE_INTERVAL
    cout << __FUNCTION__ << endl;
#endif
    vector<vector<int>> new_intervals;
    vector<intrvEvent_t> event_array = assembple_event_list (intervals);

    stable_sort (event_array.begin (), event_array.end (), comparator_time);
#ifdef DEBUG_MERGE_INTERVAL
    debug_events (event_array);
#endif
    glue_intervals (event_array);
#ifdef DEBUG_MERGE_INTERVAL
    cout << "after glue " << endl;
    debug_events (event_array);
#endif
    iStates_t state = SPARE;
    int cnt = 0, error = 0;
    vector<intrvEvent_t> sol_event_array;
    for (int event = 0; event < event_array.size (); event++) {
#ifdef DEBUG_MERGE_INTERVAL
        cout << "in " << event_array[event].time << " " << event_array[event].event << endl;
#endif
        switch (event_array[event].event) {
        case INTERVAL_END:
#ifdef DEBUG_MERGE_INTERVAL
            cout << "end " << endl;
#endif
            if (SPARE == state) {
#ifdef DEBUG_MERGE_INTERVAL
                cout << "spare " << endl;
#endif
                error++;
#ifdef DEBUG_MERGE_INTERVAL
                cout << "Error! End interval after spare!" << endl;
#endif
            } else if (BUSY == state) {
#ifdef DEBUG_MERGE_INTERVAL
                cout << "BUSY " << endl;
#endif
                cnt--;
                if (0 == cnt) {
                    state = SPARE;
                    // cout << event_array[i].time <<" "<< event_array[i].event<< endl;
                    sol_event_array.push_back (event_array[event]);
                }
            }
            break;
        case INTERVAL_START:
#ifdef DEBUG_MERGE_INTERVAL
            cout << "start " << endl;
#endif
            if (SPARE == state) {
#ifdef DEBUG_MERGE_INTERVAL
                cout << "spare " << endl;
#endif
                cnt++;
                state = BUSY;
                sol_event_array.push_back (event_array[event]);
                // cout << event_array[i].time <<" "<< event_array[i].event<< endl;
            } else if (BUSY == state) {
#ifdef DEBUG_MERGE_INTERVAL
                cout << "BUSY " << endl;
#endif
                cnt++;
                state = BUSY;
                // ignore
            }
            break;
        default:
            break;
        }
    }
#ifdef DEBUG_MERGE_INTERVAL
    cout << "Solution:" << endl;
    debug_events (sol_event_array);
#endif
    new_intervals = assemble_intervals_array (sol_event_array);
    return new_intervals;
}
