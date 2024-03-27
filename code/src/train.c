#include "train.h"

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

void feedforward(NeuralNetwork *network, double input) {
    unsigned i,j;
    double sum;

    // Set input
    network->input_layer.neurons[0].output = input;

    // Forward propagation through the hidden layer
    for (i = 0; i < HIDDEN_SIZE; i++) {
        Neuron *neuron = &network->hidden_layer.neurons[i];
        sum = neuron->bias;

        for (j = 0; j < INPUT_SIZE; j++) {
            sum += neuron->weights[j] * network->input_layer.neurons[j].output;
        }

        neuron->output = sigmoid(sum);
    }

    // Forward propagation through the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];
        sum = neuron->bias;

        for (j = 0; j < HIDDEN_SIZE; j++) {
            sum += neuron->weights[j] * network->hidden_layer.neurons[j].output;
        }

        neuron->output = sigmoid(sum);
    }
}

void backpropagation(NeuralNetwork *network, double expected_output) {
    unsigned i,j;
    double error;

    // Calculate deltas for the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];
        error = expected_output - neuron->output;
        neuron->delta = error * sigmoid_derivative(neuron->output);
    }

    // Calculate deltas for the hidden layer
    for (i = 0; i < HIDDEN_SIZE; i++) {
        Neuron *neuron = &network->hidden_layer.neurons[i];
        error = 0;

        for (j = 0; j < OUTPUT_SIZE; j++) {
            error += network->output_layer.neurons[j].weights[i] * network->output_layer.neurons[j].delta;
        }

        neuron->delta = error * sigmoid_derivative(neuron->output);
    }

    // Update weights and biases for the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];

        for (j = 0; j < HIDDEN_SIZE; j++) {
            neuron->weights[j] += LEARNING_RATE * neuron->delta * network->hidden_layer.neurons[j].output;
        }

        neuron->bias += LEARNING_RATE * neuron->delta;
    }

    // Update weights and biases for the hidden layer
    for (i = 0; i < HIDDEN_SIZE; i++) {
        Neuron *neuron = &network->hidden_layer.neurons[i];

        for (j = 0; j < INPUT_SIZE; j++) {
            neuron->weights[j] += LEARNING_RATE * neuron->delta * network->input_layer.neurons[j].output;
        }

        neuron->bias += LEARNING_RATE * neuron->delta;
    }
}

