#include "train.h"

void feedforward(NeuralNetwork *network, double input) {
    unsigned i,j,k;
    double sum;
    ActivationFunction activation_function = network->activation_function;

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

            neuron->output = activation_function(sum);
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

void backpropagation(NeuralNetwork *network, double delta, double error) {

    unsigned i,j,k;
    ActivationFunction activation_function_derivative = network->activation_function_derivative;

    // Calculate deltas for the output layer
    for (i = 0; i < network->output_size; i++) {
        network->output_layer.neurons[i].delta = error*delta;// loss_derivative(expected_output, network->output_layer.neurons[i].output); 
    }

    // Calculate deltas for the hidden layer
    for (k = network->n_hidden; k > 0; k--) {
        for (i = 0; i < network->hidden_size; i++) {
            error = 0;

            if (k == network->n_hidden) { 
                for (j = 0; j < network->output_size; j++) {
                    error += network->output_layer.neurons[j].weights[i] * network->output_layer.neurons[j].delta;
                }
            } 
            else { 
                for (j = 0; j < network->hidden_size; j++) {
                    error += network->hidden_layer[k].neurons[j].weights[i] * network->hidden_layer[k].neurons[j].delta;
                }
            }

            network->hidden_layer[k-1].neurons[i].delta = error * activation_function_derivative(network->hidden_layer[k-1].neurons[i].output);
        }
    }

    // Update weights and biases for the output layer
    for (i = 0; i < network->output_size; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];

        for (j = 0; j < network->hidden_size; j++) {
            neuron->weights[j] += LEARNING_RATE * neuron->delta * network->hidden_layer[N_HIDDEN-1].neurons[j].output;
        }

        neuron->bias += LEARNING_RATE * neuron->delta;
    }

    // Update weights and biases for the hidden layer
    for (k = 0; k < network->n_hidden; k++) {
        for (i = 0; i < network->hidden_size; i++) {
            Neuron *neuron = &network->hidden_layer[k].neurons[i];

            for (j = 0; j < (k == 0 ? network->input_size : network->hidden_size); j++) {
                if (!k) neuron->weights[j] += LEARNING_RATE * neuron->delta * network->input_layer.neurons[j].output;
                else neuron->weights[j] += LEARNING_RATE * neuron->delta * network->hidden_layer[k - 1].neurons[j].output;
            }

            neuron->bias += LEARNING_RATE * neuron->delta;
        }
    }
}
