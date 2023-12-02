#ifndef __NeuralNetwork__
#define __NeuralNetwork__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void nn_init1(void);
float *getInputBuffer1(void);
float *predict1(void);

void nn_init2(void);
float *getInputBuffer2(void);
float *predict2(void);



#ifdef __cplusplus
}
#endif

#endif