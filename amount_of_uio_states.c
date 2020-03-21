#include "amount_of_uio_states.h"

#include <string.h>
#include <stdio.h>

char *uioPulls [] =
    { "PullUp", "PullDown", "PullNone" };

char *uioModes [] =
    { "lowSide", "highSide", "H-Bridge", "input", "Vref", "Disabled" };

char *uioLoadDet [] =
    { "LoadDet_On", "LoadDet_Off" };

char *bridModes [] =
    { "Free", "Fwd", "Rev", "Break" };

char *dutyModes [] =
    { "duty=0%", "0%<duty<100%", "duty=100%" };

bool save_the_amount_of_bridge_cfg (void) {
    return true;
}

bool save_the_amount_of_uio (void) {
    int amountOfStates = 1;
    int amountOfDutyModes = sizeof(dutyModes) / sizeof(dutyModes [0]);
    int amountOfBridgeModes = sizeof(bridModes) / sizeof(bridModes [0]);
    int amountOfLdStated = sizeof(uioLoadDet) / sizeof(uioLoadDet [0]);
    int amountOfPullModes = sizeof(uioPulls) / sizeof(uioPulls [0]);
    int amountOfModes = sizeof(uioModes) / sizeof(uioModes [0]);
    for (int curDutyMode = 0; curDutyMode < amountOfDutyModes; curDutyMode++) {
        for (int curPullMode = 0; curPullMode < amountOfPullModes; curPullMode++) {
            for (int curMode = 0; curMode < amountOfModes; curMode++) {
                for (int curLd = 0; curLd < amountOfLdStated; curLd++) {
                    if (0 == strcmp (uioModes [curMode], "H-Bridge")) {
                        for (int curBrMode = 0; curBrMode < amountOfBridgeModes; curBrMode++) {
                            printf (
                                "\n%d: %s %s %s %s %s",
                                amountOfStates,
                                uioModes [curMode],
                                bridModes [curBrMode],
                                uioPulls [curPullMode],
                                uioLoadDet [curLd],
                                dutyModes [curDutyMode]);
                            amountOfStates++;
                        }
                    } else {
                        printf (
                            "\n%d: %s %s %s %s",
                            amountOfStates,
                            uioModes [curMode],
                            uioPulls [curPullMode],
                            uioLoadDet [curLd],
                            dutyModes [curDutyMode]);
                        amountOfStates++;
                    }
                }
            }
        }
    }

    printf ("\n\nAmount Of combinations %d\n", amountOfStates);

    return true;
}
