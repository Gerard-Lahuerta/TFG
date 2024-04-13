#include "load.h"
#include "train.h"
#include "MLP.h"
#include "utils.h"
#include "definitions.h"

int main() {
    srand(0); 
    char log_name[20], res_name[20];
    sprintf(log_name, "log/%d-%d-%d-%d.csv", INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE);
    sprintf(res_name, "res/%d-%d-%d-%d.csv", INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE);


    FILE* log_file = fopen(log_name,"w+");

    CostFunction loss = &quadratic_cost;
    CostFunction loss_derivative = &quadratic_cost_derivative;
    ActivationFunction activation_function = &sigmoid;
    ActivationFunction activation_function_derivative = &sigmoid_derivative;

    NeuralNetwork network = create_network(INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE, loss_derivative, activation_function, activation_function_derivative);

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
        index = rand() % data_size;
        feedforward(&network, input);
        if (LOG_ENABLED) LOG(epoch+1, loss(expected_output, network.output_layer.neurons[0].output), log_file);
    }

    input = 1; // to be changed
    feedforward(&network, input);
    printf("Output: %lf\n", network.output_layer.neurons[0].output);

    save_neurons_to_csv(res_name, &network);

    free(network.input_layer.neurons);
    for (i = 0; i < N_HIDDEN; i++) free(network.hidden_layer[i].neurons);
    free(network.output_layer.neurons);

    return 0;
}
