#include "artificial_neural_network.h"

#include <math.h>

float nodeValues [14];

float neuralNetworkWeights [14] [14] =
    {
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN, NAN },
        { NAN,  NAN,  NAN,  NAN,  NAN,  NAN,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NAN, NAN } };

float synapse (float * const arrOfinputs, float * const arrOfweight, uint32_t amountOfInputs) {
    float outPut = 0.0f;
    for (uint32_t i = 0; i < amountOfInputs; i++) {
        outPut += arrOfweight [i] * arrOfinputs [i];
    }
    return outPut;
}

// 6 synapses in middle
bool control_neural_network (float xErr, float yErr, float aErr, float vXErr, float vYErr, float omegaErr, float *Fjet, float *Fcorr) {
    bool res = false;
    //N - amount of in 6  0.....(N-1)
    // amount of layesr 1
    // amount of
    // first intermediate node N
    //
    if ((Fjet != NULL) && (NULL != Fcorr)) {
        nodeValues [0] = xErr;
        nodeValues [1] = yErr;
        nodeValues [2] = aErr;
        nodeValues [3] = vXErr;
        nodeValues [4] = vYErr;
        nodeValues [5] = omegaErr;
        nodeValues [6] =  synapse (&nodeValues [0], &neuralNetworkWeights [6] [0], 6);
        nodeValues [7] =  synapse (&nodeValues [0], &neuralNetworkWeights [7] [0], 6);
        nodeValues [8] =  synapse (&nodeValues [0], &neuralNetworkWeights [8] [0], 6);
        nodeValues [9] =  synapse (&nodeValues [0], &neuralNetworkWeights [9] [0], 6);
        nodeValues [10] = synapse (&nodeValues [0], &neuralNetworkWeights [10] [0], 6);
        nodeValues [11] = synapse (&nodeValues [0], &neuralNetworkWeights [11] [0], 6);
        nodeValues [12] = synapse (&nodeValues [6], &neuralNetworkWeights [12] [6], 6);
        nodeValues [13] = synapse (&nodeValues [6], &neuralNetworkWeights [12] [6], 6);
        *Fjet = nodeValues [12];
        *Fcorr = nodeValues [13];
    }
    return res;
}
