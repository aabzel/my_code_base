class Solution {
  public:
    typedef enum { INTERVAL_START = 1, INTERVAL_END = -1 } eEvent_t;
    typedef enum { SPARE = 0, BUSY = 1 } iStates_t;

    typedef struct xEvent_t {
        int time;
        eEvent_t event;
    } intrvEvent_t;

    static bool comparator_time (intrvEvent_t const &a, intrvEvent_t const &b) { return a.time < b.time; }

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

    vector<vector<int>> intervalIntersection (vector<vector<int>> &firstList, vector<vector<int>> &secondList) {
        vector<vector<int>> total_list;
        vector<vector<int>> interseption_list;
        total_list.insert (total_list.end (), firstList.begin (), firstList.end ());
        total_list.insert (total_list.end (), secondList.begin (), secondList.end ());
        vector<intrvEvent_t> event_array = assembple_event_list (total_list);

        stable_sort (event_array.begin (), event_array.end (), comparator_time);

#ifdef DEBUG_INTERSEPT_INTERVAL
        cout << "sorted event:" << endl;
        debug_events (event_array);
#endif

        iStates_t state = SPARE;
        int cnt = 0, error = 0;
        vector<intrvEvent_t> intercept_event_array;
        for (int event = 0; event < event_array.size (); event++) {
            if ((1 <= event) && (INTERVAL_START == event_array[event - 1].event) &&
                (INTERVAL_END == event_array[event].event) &&
                (event_array[event - 1].time == event_array[event].time)) {
                intercept_event_array.push_back (event_array[event - 1]);
                intercept_event_array.push_back (event_array[event]);
            }
#ifdef DEBUG_INTERSEPT_INTERVAL
            cout << "in " << event_array[event].time << " " << event_array[event].event << endl;
#endif
            switch (event_array[event].event) {
            case INTERVAL_START: {
#ifdef DEBUG_INTERSEPT_INTERVAL
                cout << "start " << endl;
#endif
                if (SPARE == state) {
                    state = BUSY;
                    cnt++;
#ifdef DEBUG_INTERSEPT_INTERVAL
                    cout << "spare " << endl;
#endif
                } else if (BUSY == state) {
                    state = BUSY;
                    cnt++;
#ifdef DEBUG_INTERSEPT_INTERVAL
                    cout << "BUSY " << endl;
                    cout << event_array[event].time << " " << event_array[event].event << endl;
#endif
                    intercept_event_array.push_back (event_array[event]);
                    // ignore
                }
            } break;
            case INTERVAL_END: {
#ifdef DEBUG_INTERSEPT_INTERVAL
                cout << "end " << endl;
#endif
                if (SPARE == state) {
#ifdef DEBUG_INTERSEPT_INTERVAL
                    cout << "spare " << endl;
#endif
                    error++;
                    // cout << "Error! End interval after spare!" << endl;
#ifdef DEBUG_INTERSEPT_INTERVAL
#endif
                } else if (BUSY == state) {
                    // cnt==1
                    cnt--;
                    // cnt==0
#ifdef DEBUG_INTERSEPT_INTERVAL
                    cout << "BUSY " << endl;
#endif
                    if (0 < cnt) {
                        state = BUSY;
                        // cout << event_array[event].time <<" "<< event_array[event].event<< endl;
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
#ifdef DEBUG_INTERSEPT_INTERVAL
        cout << "Solution:" << endl;
        debug_events (intercept_event_array);
#endif
        interseption_list = assemble_intervals_array (intercept_event_array);

        return interseption_list;
    }
};
