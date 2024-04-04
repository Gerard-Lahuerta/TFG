#include "load.h"
#include "train.h"
#include "MLP.h"
#include "definitions.h"

int main() {
    srand(0); 

    NeuralNetwork network = create_network();

    // load dataset
    char* dataset_file = "data/roots.csv";
    int index, i, data_size = 0;
    double** dataset = read_dataset(dataset_file, &data_size);


    // Variables
    unsigned epoch;
    double input, expected_output;
    

    for (epoch = 0; epoch < EPOCHS; epoch++) {
        for (i = 0; i < data_size; i++) {
            index = rand() % data_size;
            input = dataset[index][0];
            expected_output = dataset[index][1];
            feedforward(&network, input);
            backpropagation(&network, expected_output);
        }
    }

    input = 1; // to be changed
    feedforward(&network, input);
    printf("Output: %lf\n", network.output_layer.neurons[0].output);

    save_neurons_to_csv("./data/neuron_values.csv", &network);

    free(network.input_layer.neurons);
    for (i = 0; i < N_HIDDEN; i++) free(network.hidden_layer[i].neurons);
    free(network.output_layer.neurons);

    return 0;
}
