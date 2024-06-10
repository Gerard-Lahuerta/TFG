#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define LOG_ENABLED 1

#define INPUT_SIZE 1
#define HIDDEN_SIZE 2
#define OUTPUT_SIZE 1
#define N_HIDDEN 1
#define LEARNING_RATE 0.1
#define EPOCHS 100

typedef double (*CostFunction)(double expected_output, double actual_output);
typedef double (*ActivationFunction)(double value);