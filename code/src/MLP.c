#include "MLP.h"

Neuron create_neuron(unsigned num_inputs) {
    Neuron neuron;
    neuron.weights = (double *)malloc(num_inputs * sizeof(double));
    neuron.bias = ((double)rand() / RAND_MAX) * 2 - 1; 

    for (unsigned i = 0; i < num_inputs; i++) {
        neuron.weights[i] = ((double)rand() / RAND_MAX) * 2 - 1; 
    }

    return neuron;
}

Layer create_layer(unsigned num_neurons, unsigned num_inputs_per_neuron) {
    Layer layer;
    layer.num_neurons = num_neurons;
    layer.neurons = (Neuron *)malloc(num_neurons * sizeof(Neuron));

    for (unsigned i = 0; i < num_neurons; i++) {
        layer.neurons[i] = create_neuron(num_inputs_per_neuron);
    }

    return layer;
}

NeuralNetwork create_network(CostFunction loss_derivative, ActivationFunction activation_function, ActivationFunction activation_function_derivative) {
    NeuralNetwork network;
    
    network.loss_derivative = loss_derivative;
    network.activation_function = activation_function;
    network.activation_function_derivative = activation_function_derivative;

    network.input_layer = create_layer(INPUT_SIZE, 1);
    network.hidden_layer = (Layer*) malloc(N_HIDDEN * sizeof(Layer));
    for (unsigned i = 0; i < N_HIDDEN; i++){
        if (!i) network.hidden_layer[i] = create_layer(HIDDEN_SIZE, INPUT_SIZE);
        else network.hidden_layer[i] = create_layer(HIDDEN_SIZE, HIDDEN_SIZE);
    }
    network.output_layer = create_layer(OUTPUT_SIZE, HIDDEN_SIZE);
    return network;
}
