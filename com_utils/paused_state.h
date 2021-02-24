#ifndef PAUSED_STATE_H_
#define PAUSED_STATE_H_
#include <stdbool.h>
#include <stdint.h>

#ifdef FOR_BOOTLOADER

bool device_is_paused (void);
void device_set_paused (bool paused);

bool cmd_pause (int32_t argc, char *argv[]);
bool cmd_resume (int32_t argc, char *argv[]);

#define PAUSED_STATE_COMMANDS                                                                                          \
    SHELL_CMD ("pause", "pause", cmd_pause, "Pause device operation"),                                                 \
        SHELL_CMD ("resume", "resume", cmd_resume, "Resume device operation"),
#else
#define PAUSED_STATE_COMMANDS
#endif

#endif /* PAUSED_STATE_H_ */
