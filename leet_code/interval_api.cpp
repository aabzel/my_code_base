
#include <iostream>
#include <vector>

#include "interval_api.h"
#include "utils_cpp.h"

using namespace std;

vector<intrvEvent_t> assembple_event_list (vector<vector<int>> &intervals) {
    vector<intrvEvent_t> event_array;
    intrvEvent_t one_event;
    for (int i = 0; i < intervals.size (); i++) {
        one_event.time = intervals[i][0];
        one_event.event = INTERVAL_START;
        event_array.push_back (one_event);
        one_event.time = intervals[i][1];
        one_event.event = INTERVAL_END;

        event_array.push_back (one_event);
    }
    return event_array;
}

bool comparator_time (intrvEvent_t const &a, intrvEvent_t const &b) { return a.time < b.time; }

vector<intrvEvent_t> glue_intervals (vector<intrvEvent_t> &event_array) {
    vector<intrvEvent_t> new_events;
    intrvEvent_t event_to_del;
    vector<int> index_to_del;
    for (int event = 0; event < event_array.size () - 1; event++) {
        if (event_array[event].time == event_array[event + 1].time) {
            if ((INTERVAL_END == event_array[event].event) && (INTERVAL_START == event_array[event + 1].event)) {
                index_to_del.push_back (event);
                index_to_del.push_back (event + 1);
            }
        }
    }
#ifdef DEBUG_MERGE_INTERVAL
    print_vector_ints (index_to_del);
#endif
    for (int i = index_to_del.size () - 1; 0 <= i; i--) {
        // cout << "del "<<index_to_del[i] << endl;
        event_array.erase (event_array.begin () + index_to_del[i]);
    }
    new_events = event_array;
    return new_events;
}

vector<vector<int>> assemble_intervals_array (vector<intrvEvent_t> event_array) {
    vector<vector<int>> intervals;
    vector<int> interval;
    int interavl = 0;
    for (int event = 0; event < event_array.size (); event++) {
        if (INTERVAL_START == event_array[event].event) {

            if (0 == interavl) {
                interval.clear ();
                interval.push_back (event_array[event].time);
                interavl = 1;
            } else {
                // cout << "events unsorted " << endl;
            }
        } else if (INTERVAL_END == event_array[event].event) {
            if (1 == interavl) {
                interavl = 0;
                interval.push_back (event_array[event].time);
                intervals.push_back (interval);
            } else {
                // cout << "events unsorted " << endl;
            }
        }
    }
    return intervals;
}

bool debug_events (vector<intrvEvent_t> &event_array) {
    cout << __FUNCTION__ << endl;
    bool res = false;
    cout << "\n [d] Event list size: " << event_array.size () << endl;

    for (int event = 0; event < event_array.size (); event++) {
        res = true;
        cout << "(" << event_array[event].time << " " << event_array[event].event << ") ";
    }
    cout << endl;
    return res;
}
