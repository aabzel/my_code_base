#ifndef ROCKET_MATH_MODEL_2D_H
#define ROCKET_MATH_MODEL_2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

bool rocket_math_model_2d (float rocketLength, float GravitationalAcceleration, float curX, float curY, float curAlfa,
                           float curVx, float curVy, float curOmega, float *newX, float *newY, float *newAlfa,
                           float *newVx, float *newVy, float *newOmega, float periodSec, float mass, float Fjet,
                           float Fcorrect);

#ifdef __cplusplus
}
#endif

#endif /* ROCKET_MATH_MODEL_2D_H */
