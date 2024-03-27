#include <stdio.h>
#include "definitions.h"

#ifndef MLP_H
#define MLP_H

typedef struct {
    double *inputs;
    double *weights;
    double bias;
    double output;
    double delta;
} Neuron;

typedef struct {
    Neuron *neurons;
    int num_neurons;
} Layer;

typedef struct {
    Layer input_layer;
    Layer hidden_layer;
    Layer output_layer;
} NeuralNetwork;

Neuron create_neuron(unsigned num_inputs);
Layer create_layer(unsigned num_neurons, unsigned num_inputs_per_neuron);
NeuralNetwork create_network();

#endif