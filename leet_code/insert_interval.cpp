#include "insert_interval.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "utils_cpp.h"

using namespace std;

typedef enum { INTERVAL_START = 1, INTERVAL_END = -1 } eEvent_t;
typedef enum { SPARE = 0, BUSY = 1 } iStates_t;

typedef struct xEvent_t {
    int time;
    eEvent_t event;
} intrvEvent_t;

static bool comparator_time (intrvEvent_t const &a, intrvEvent_t const &b) { return a.time < b.time; }

#ifdef DEBUG_INSERT_INTERVAL
static bool debug_events (vector<intrvEvent_t> &event_array) {
    cout << __FUNCTION__ << endl;
    bool res = false;
    cout << "\n [d] Event list \n" << endl;

    for (int event = 0; event < event_array.size (); event++) {
        res = true;
        cout << "(" << event_array[event].time << " " << event_array[event].event << ") ";
    }
    cout << endl;
    return res;
}
#endif

static vector<vector<int>> assemble_intervals_array (vector<intrvEvent_t> event_array) {
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
                cout << "events unsorted " << endl;
            }
        } else if (INTERVAL_END == event_array[event].event) {
            if (1 == interavl) {
                interavl = 0;
                interval.push_back (event_array[event].time);
                intervals.push_back (interval);
            } else {
                cout << "events unsorted " << endl;
            }
        }
    }
    return intervals;
}

static vector<intrvEvent_t> glue_intervals (vector<intrvEvent_t> &event_array) {
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
#ifdef DEBUG_INSERT_INTERVAL
    print_vector_ints (index_to_del);
#endif
    for (int i = index_to_del.size () - 1; 0 <= i; i--) {
        // cout << "del "<<index_to_del[i] << endl;
        event_array.erase (event_array.begin () + index_to_del[i]);
    }
    new_events = event_array;
    return new_events;
}

vector<vector<int>> Insert_Interval (vector<vector<int>> &intervals, vector<int> &newInterval) {
#ifdef DEBUG_INSERT_INTERVAL
    cout << __FUNCTION__ << endl;
#endif
    vector<vector<int>> new_intervals;
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
    one_event.time = newInterval[0];
    one_event.event = INTERVAL_START;
    event_array.push_back (one_event);
    one_event.time = newInterval[1];
    one_event.event = INTERVAL_END;
    event_array.push_back (one_event);
    stable_sort (event_array.begin (), event_array.end (), comparator_time);
#ifdef DEBUG_INSERT_INTERVAL
    debug_events (event_array);
#endif
    glue_intervals (event_array);
#ifdef DEBUG_INSERT_INTERVAL
    cout << "after glue " << endl;
    debug_events (event_array);
#endif
    iStates_t state = SPARE;
    int cnt = 0, error = 0;
    vector<intrvEvent_t> sol_event_array;
    for (int event = 0; event < event_array.size (); event++) {
#ifdef DEBUG_INSERT_INTERVAL
        cout << "in " << event_array[event].time << " " << event_array[event].event << endl;
#endif
        switch (event_array[event].event) {
        case INTERVAL_END:
#ifdef DEBUG_INSERT_INTERVAL
            cout << "end " << endl;
#endif
            if (SPARE == state) {
#ifdef DEBUG_INSERT_INTERVAL
                cout << "spare " << endl;
#endif
                error++;
#ifdef DEBUG_INSERT_INTERVAL
                cout << "Error! End interval after spare!" << endl;
#endif
            } else if (BUSY == state) {
#ifdef DEBUG_INSERT_INTERVAL
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
#ifdef DEBUG_INSERT_INTERVAL
            cout << "start " << endl;
#endif
            if (SPARE == state) {
#ifdef DEBUG_INSERT_INTERVAL
                cout << "spare " << endl;
#endif
                cnt++;
                state = BUSY;
                sol_event_array.push_back (event_array[event]);
                // cout << event_array[i].time <<" "<< event_array[i].event<< endl;
            } else if (BUSY == state) {
#ifdef DEBUG_INSERT_INTERVAL
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
#ifdef DEBUG_INSERT_INTERVAL
    cout << "Solution:" << endl;
    debug_events (sol_event_array);
#endif
    new_intervals = assemble_intervals_array (sol_event_array);
    return new_intervals;
}
