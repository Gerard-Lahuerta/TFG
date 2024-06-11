#include "load.h"
#include "train.h"
#include "MLP.h"
#include "utils.h"
#include "definitions.h"

int main() {

    srand(0); 
    char log_name[30], res_name[30], output[30];
    sprintf(log_name, "log/%d-%d-%d-%d.csv", INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE);
    sprintf(res_name, "models/%d-%d-%d-%d.csv", INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE);
    sprintf(output, "res/%d-%d-%d-%d.csv", INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE);

    CostFunction loss = &quadratic_cost;
    CostFunction loss_derivative = &quadratic_cost_derivative;
    ActivationFunction activation_function = &sigmoid;
    ActivationFunction activation_function_derivative = &sigmoid_derivative;

    NeuralNetwork network = create_network(INPUT_SIZE, HIDDEN_SIZE, N_HIDDEN, OUTPUT_SIZE, loss_derivative, activation_function, activation_function_derivative);

    // load dataset
    char* dataset_file = "data/disc.csv";
    int index, i, data_size = 0;
    double** dataset = read_dataset(dataset_file, &data_size);


    // Variables
    unsigned epoch;
    double input, expected_output, mse = 0;
    FILE* log_file = fopen(log_name,"w+");
    FILE* output_file = fopen(output,"w+");

    unsigned order[data_size];
    for ( i = 0; i < data_size; i++) order[i] = i;

    for (epoch = 0; epoch < EPOCHS; epoch++) {
        randomize(order, data_size);
        for (i = 0; i < data_size; i++) {
            index = order[i];
            input = dataset[index][0];
            expected_output = dataset[index][1];
            feedforward(&network, input);
            backpropagation(&network, expected_output);
        }
        if (LOG_ENABLED) LOG(epoch+1, loss(expected_output, network.output_layer.neurons[0].output), log_file);
    }

    fclose(log_file);
    save_neurons_to_csv(res_name, &network);

    for (i = 0; i < data_size; i++){
            input = dataset[i][0];
            feedforward(&network, input);
            fprintf(output_file,"%lf;%lf\n", input, network.output_layer.neurons[0].output);
            mse += (network.output_layer.neurons[0].output - dataset[i][1])*(network.output_layer.neurons[0].output - dataset[i][1]);
    }
    mse /= data_size;
    printf("Load output done\n");
    printf("MSE: %lf\n", mse);

    free(network.input_layer.neurons);
    for (i = 0; i < N_HIDDEN; i++) free(network.hidden_layer[i].neurons);
    free(network.output_layer.neurons);

    return 0;
}
