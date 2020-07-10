#include "simulate_rocket_2d.h"

#include "math_model_rocket_2d.h"


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

bool simulate_roket (float runTime) {
    bool res = false;
    float curTime = 0.0f;
    float rocketLength = 10.0f;
    float deltaTimeS = 0.01f;
    float curX = 0.0f;
    float curY = 10.0f;
    float curAlfa = 0.0f;
    float curVx = 0.0f;
    float curVy = 0.0f;
    float mass = 1000.0;
    float GravitationalAcceleration = 9.8f;
    float curOmega = 0.0f;
    float Fjet = mass* GravitationalAcceleration + 0.5f * mass* GravitationalAcceleration;
    float Fcorrect = 0.0f;
    float newX = 0.0f;
    float newY = 0.0f;
    float newAlfa = 0.0f;
    float newVx = 0.0f;
    float newVy = 0.0f;
    float newOmega = 0.0f;
    FILE *outFilePrt = NULL;
    outFilePrt = fopen ("rocket_flight_simulation.txt", "w");
    if (NULL != outFilePrt) {
        for (curTime = 0.0f; curTime < runTime; curTime += deltaTimeS) {
            res = rocket_math_model_2d (
                rocketLength,
                GravitationalAcceleration,
                curX,
                curY,
                curAlfa,
                curVx,
                curVy,
                curOmega,
                &newX,
                &newY,
                &newAlfa,
                &newVx,
                &newVy,
                &newOmega,
                deltaTimeS,
                mass,
                Fjet,
                Fcorrect);
            curX = newX;
            curY = newY;
            curAlfa = newAlfa;
            curVx = newVx;
            curVy = newVy;
            curOmega = newOmega;
            fprintf (outFilePrt, "\n t:%6.3f X:%6.3f m Y:%6.3f m alfa:%6.3f rag Vx %6.3f m/s Vy %6.3f m/s omega %6.3f rag/s", curTime ,newX, newY, newAlfa, newVx, newVy, newOmega);
        }
        fclose (outFilePrt);
        res = true;
    }
    return res;
}
