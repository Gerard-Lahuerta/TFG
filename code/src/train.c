#include "train.h"

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

void feedforward(NeuralNetwork *network, double input) {
    unsigned i,j,k;
    double sum;

    // Set input
    network->input_layer.neurons[0].output = input;

    // Forward propagation through the hidden layer
    for (k = 0; k < N_HIDDEN; k++) {
        for (i = 0; i < HIDDEN_SIZE; i++) {
            Neuron *neuron = &network->hidden_layer[k].neurons[i];
            sum = neuron->bias;

            for (j = 0; j < (k == 0 ? INPUT_SIZE : HIDDEN_SIZE); j++) {
                if (!k) sum += neuron->weights[j] * network->input_layer.neurons[j].output;
                else sum += neuron->weights[j] * network->hidden_layer[k-1].neurons[j].output;
            }

            neuron->output = sigmoid(sum);
        }
    }

    // Forward propagation through the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];
        sum = neuron->bias;

        for (j = 0; j < HIDDEN_SIZE; j++) {
            sum += neuron->weights[j] * network->hidden_layer[N_HIDDEN-1].neurons[j].output;
        }

        neuron->output = sum;
    }
}

void backpropagation(NeuralNetwork *network, double expected_output) {
    unsigned i,j,k;
    double error;
    CostFunction loss_derivative = network->loss_derivative;

    // Calculate deltas for the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        network->output_layer.neurons[i].delta = loss_derivative(expected_output, network->output_layer.neurons[i].output); 
    }

    // Calculate deltas for the hidden layer
    for (k = N_HIDDEN; k > 0; k--) {
        for (i = 0; i < HIDDEN_SIZE; i++) {
            error = 0;

            if (k == N_HIDDEN) { 
                for (j = 0; j < OUTPUT_SIZE; j++) {
                    error += network->output_layer.neurons[j].weights[i] * network->output_layer.neurons[j].delta;
                }
            } 
            else { 
                for (j = 0; j < HIDDEN_SIZE; j++) {
                    error += network->hidden_layer[k].neurons[j].weights[i] * network->hidden_layer[k].neurons[j].delta;
                }
            }

            network->hidden_layer[k-1].neurons[i].delta = error * sigmoid_derivative(network->hidden_layer[k-1].neurons[i].output);
        }
    }

    // Update weights and biases for the output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];

        for (j = 0; j < HIDDEN_SIZE; j++) {
            neuron->weights[j] += LEARNING_RATE * neuron->delta * network->hidden_layer[N_HIDDEN-1].neurons[j].output;
        }

        neuron->bias += LEARNING_RATE * neuron->delta;
    }

    // Update weights and biases for the hidden layer
    for (k = 0; k < N_HIDDEN; k++) {
        for (i = 0; i < HIDDEN_SIZE; i++) {
            Neuron *neuron = &network->hidden_layer[k].neurons[i];

            for (j = 0; j < (k == 0 ? INPUT_SIZE : HIDDEN_SIZE); j++) {
                if (!k) neuron->weights[j] += LEARNING_RATE * neuron->delta * network->input_layer.neurons[j].output;
                else neuron->weights[j] += LEARNING_RATE * neuron->delta * network->hidden_layer[k - 1].neurons[j].output;
            }

            neuron->bias += LEARNING_RATE * neuron->delta;
        }
    }
}

