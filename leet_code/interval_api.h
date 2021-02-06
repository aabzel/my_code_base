

#pragma once

#include <vector>

using namespace std;

typedef enum { INTERVAL_START = 1, INTERVAL_END = -1 } eEvent_t;
typedef enum { SPARE = 0, BUSY = 1 } iStates_t;

typedef struct xEvent_t {
    int time;
    eEvent_t event;
} intrvEvent_t;

vector<intrvEvent_t> assembple_event_list (vector<vector<int>> &intervals);
vector<intrvEvent_t> glue_intervals (vector<intrvEvent_t> &event_array) ;
vector<vector<int>> assemble_intervals_array (vector<intrvEvent_t> event_array) ;
bool debug_events (vector<intrvEvent_t> &event_array) ;
