#include "load.h"
#include "train.h"
#include "MLP.h"
#include "definitions.h"

int main() {
    srand(0); 

    NeuralNetwork network = create_network();

    // load dataset
    double dataset[DATA_SIZE][2] = { {1,1}, {4,2}}; 

    // Variables
    unsigned epoch, i;
    double input, expected_output;
    

    for (epoch = 0; epoch < EPOCHS; epoch++) {
        for (i = 0; i < DATA_SIZE; i++) {
            input = dataset[i][0];
            expected_output = dataset[i][1];
            feedforward(&network, input);
            backpropagation(&network, expected_output);
        }
    }

    input = 0.5; // to be changed
    feedforward(&network, input);
    printf("Output: %lf\n", network.output_layer.neurons[0].output);

    save_neurons_to_csv("./data/neuron_values.csv", &network);

    free(network.input_layer.neurons);
    free(network.hidden_layer.neurons);
    free(network.output_layer.neurons);

    return 0;
}
