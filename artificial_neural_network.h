
#ifndef ARTIFICIAL_NEURAL_NETWORK_H
#define ARTIFICIAL_NEURAL_NETWORK_H

#include <stdint.h>

#include "custom_type.h"

float synapse (float *const arrOfinputs, float *const arrOfweight, uint32_t amountOfInputs);
bool control_neural_network (float xErr, float yErr, float aErr, float vXErr, float vYErr, float omegaErr, float *Fjet,
                             float *Fcorr);

#endif
