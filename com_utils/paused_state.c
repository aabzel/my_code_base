#include "paused_state.h"

#ifdef FOR_BOOTLOADER
static bool device_paused = false;

bool device_is_paused (void) { return device_paused; }

void device_set_paused (bool paused) { device_paused = paused; }

bool cmd_pause (int32_t argc, char *argv[]) {
    (void)(argv);
    (void)(argc);
    device_set_paused (true);
    return true;
}

bool cmd_resume (int32_t argc, char *argv[]) {
    (void)(argv);
    (void)(argc);
    device_set_paused (false);
    return true;
}
#endif
