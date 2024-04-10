#include <stdio.h>
#include <math.h>
#include "definitions.h"
#include "MLP.h"

double sigmoid(double x);
double sigmoid_derivative(double x);

void feedforward(NeuralNetwork *network, double input);
void backpropagation(NeuralNetwork *network, double expected_output, CostFunction loss);

