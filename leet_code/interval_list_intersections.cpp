#include "interval_list_intersections.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "interval_api.h"
#include "utils_cpp.h"

using namespace std;

vector<vector<int>> intervalIntersection (vector<vector<int>> &firstList, vector<vector<int>> &secondList) {
    vector<vector<int>> total_list;
    vector<vector<int>> interseption_list;
    total_list.insert (total_list.end (), firstList.begin (), firstList.end ());
    total_list.insert (total_list.end (), secondList.begin (), secondList.end ());
    vector<intrvEvent_t> event_array = assembple_event_list (total_list);

    stable_sort (event_array.begin (), event_array.end (), comparator_time);

#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
    cout << "sorted event: ";
    debug_events (event_array);
#endif

    iStates_t state = SPARE;
    int cnt = 0, error = 0;
    vector<intrvEvent_t> intercept_event_array;
    for (int event = 0; event < event_array.size (); event++) {
#if 1
        if (1 <= event) {
            if (event_array[event - 1].time == event_array[event].time) {
                if (INTERVAL_START == event_array[event - 1].event && INTERVAL_END == event_array[event].event) {
                    intercept_event_array.push_back (event_array[event - 1]);
                    intercept_event_array.push_back (event_array[event]);
                } else if (INTERVAL_END == event_array[event - 1].event && INTERVAL_START == event_array[event].event) {
                    intercept_event_array.push_back (event_array[event]);
                    intercept_event_array.push_back (event_array[event - 1]);
                }
            }
        }

#endif

#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
        cout << "in " << event_array[event].time << " " << event_array[event].event << endl;
#endif
        switch (event_array[event].event) {
        case INTERVAL_START: {
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
            cout << "start " << endl;
#endif
            if (SPARE == state) {
                state = BUSY;
                cnt++;
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
                cout << "spare " << endl;
#endif
            } else if (BUSY == state) {
                state = BUSY;
                cnt++;
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
                cout << "BUSY " << endl;
                cout << event_array[event].time << " " << event_array[event].event << endl;
#endif
                intercept_event_array.push_back (event_array[event]);
                // ignore
            }
        } break;
        case INTERVAL_END: {
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
            cout << "end " << endl;
#endif
            if (SPARE == state) {
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
                cout << "spare " << endl;
#endif
                error++;
                cout << "Error! End interval after spare!" << endl;
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
#endif
            } else if (BUSY == state) {
                // cnt==1
                cnt--;
                // cnt==0
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
                cout << "BUSY " << endl;
#endif
                if (0 < cnt) {
                    state = BUSY;
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
                    cout << event_array[event].time << " " << event_array[event].event << endl;
#endif
                    intercept_event_array.push_back (event_array[event]);
                } else if (0 == cnt) {
                    state = SPARE;
                }
            }
        } break;
        default:
            break;
        }
    }
#ifdef DEBUG_INTERSEPT_INTERVAL_PEDANTIC
    cout << "Solution:" << endl;
    debug_events (intercept_event_array);
#endif
    interseption_list = assemble_intervals_array (intercept_event_array);

    return interseption_list;
}
