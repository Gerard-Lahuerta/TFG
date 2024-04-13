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
    unsigned num_neurons;
    unsigned input_size;
} Layer;

typedef struct {
    unsigned input_size;
    unsigned hidden_size;
    unsigned n_hidden;
    unsigned output_size;
    Layer input_layer;
    Layer *hidden_layer;
    Layer output_layer;
    CostFunction loss_derivative;
    ActivationFunction activation_function; 
    ActivationFunction activation_function_derivative;
} NeuralNetwork;

Neuron create_neuron(unsigned num_inputs);
Layer create_layer(unsigned num_neurons, unsigned num_inputs_per_neuron);
NeuralNetwork create_network(unsigned input_size, unsigned hidden_size, unsigned n_hidden, unsigned output_size, CostFunction loss_derivative, ActivationFunction activation_function, ActivationFunction activation_function_derivative);
#endif