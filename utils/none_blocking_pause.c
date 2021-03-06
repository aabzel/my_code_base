#include "none_blocking_pause.h"

#include "common_functions.h"
#include "task_info.h"
#include "timer_utils.h"

/*none blocking wait for self test and poling*/
bool wait_in_loop_ms (uint64_t wait_pause_ms) {
    uint64_t start_ms = 0U;
    uint64_t curr_ms = 0U;
    bool res = false;
    start_ms = get_time_ms64 ();
    bool loop = true;
    while (loop) {
        MAIN_LOOP_START;
        common_loop (loop_start_time);

        curr_ms = get_time_ms64 ();
        if (wait_pause_ms < (curr_ms - start_ms)) {
            res = true;
            loop = false;
            break;
        }
    }
    return res;
}
