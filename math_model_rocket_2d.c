#include "math_model_rocket_2d.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// curAlfa radiand
// periodSec se
// mass
bool rocket_math_model_2d (float rocketLength, float GravitationalAcceleration, float curX, float curY, float curAlfa,
                           float curVx, float curVy, float curOmega, float *newX, float *newY, float *newAlfa,
                           float *newVx, float *newVy, float *newOmega, float periodSec, float massKg, float Fjet,
                           float Fcorrect) {
    bool res = false;

    if ((0.0f < massKg) && (0.0 < rocketLength)) {
        res = true;
        float rodMomentOfInertia = massKg * rocketLength * rocketLength / 12.0f;
        float tempNewVx, tempNewVy;
        float tempNewX, tempNewY;
        float tempNewOmega;
        float tempNewAlfa;

        tempNewVx = (-Fjet * sin (curAlfa) * periodSec / massKg) + curVx;
        tempNewVy = (-GravitationalAcceleration * massKg + Fjet * cos (curAlfa)) * periodSec / massKg + curVy;
        tempNewOmega = ((rocketLength * Fcorrect * periodSec) / 2.0f * rodMomentOfInertia) + curOmega;

        tempNewX = tempNewVx * periodSec + curX;
        tempNewY = tempNewVy * periodSec + curY;
        tempNewAlfa = tempNewOmega * periodSec + curAlfa;

        (*newX) = tempNewX;
        (*newY) = tempNewY;
        (*newAlfa) = tempNewAlfa;

        (*newVx) = tempNewVx;
        (*newVy) = tempNewVy;
        (*newOmega) = tempNewOmega;
    }
    return res;
}
