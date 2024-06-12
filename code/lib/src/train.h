#include <stdio.h>
#include <math.h>
#include "definitions.h"
#include "MLP.h"

void feedforward(NeuralNetwork *network, double input);
void backpropagation(NeuralNetwork *network, double expected_output);

