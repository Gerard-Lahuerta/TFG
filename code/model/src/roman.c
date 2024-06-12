#include "load.h"
#include "train.h"
#include "MLP.h"
#include "utils.h"
#include "definitions.h"


int main() {

    srand(0); 
    char log_name[30], output[30];
    sprintf(log_name, "log/roman.csv");
    sprintf(output, "res/roman.csv");

    CostFunction loss = &quadratic_cost;
    CostFunction loss_derivative = &quadratic_cost_derivative;
    ActivationFunction activation_function = &sigmoid;
    ActivationFunction activation_function_derivative = &sigmoid_derivative;

    NeuralNetwork sin1 = create_network(1, 2, 2, 1, loss_derivative, activation_function, activation_function_derivative);
    NeuralNetwork sin2 = create_network(1, 2, 2, 1, loss_derivative, activation_function, activation_function_derivative);
    NeuralNetwork sin3 = create_network(1, 2, 2, 1, loss_derivative, activation_function, activation_function_derivative);
    NeuralNetwork sqr = create_network(1, 3, 1, 1, loss_derivative, activation_function, activation_function_derivative);

    NeuralNetwork network[4] = {sin1, sin2, sin3, sqr};
    double weights[4] = {4,3,2,1};
    double bias = 0, delta;
    char N_networks = 4;


    // load dataset
    char* dataset_file = "data/roman.csv";
    int index, i, j, data_size = 0;
    double** dataset = read_dataset(dataset_file, &data_size);


    // Variables
    unsigned epoch;
    double input, expected_output, res, mse = 0;
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

            res = 0;
            for(j = 0; j < N_networks; j++){
                feedforward(&network[j], input);
                res += weights[j]*network[j].output_layer.neurons[0].output;
            }
            res += bias;

            for(j = 0; j < N_networks; j++){
                delta = loss_derivative(expected_output, res);
                backpropagation(&network[j], delta, weights[j]*loss(expected_output, res));

                    for (j = 0; j < N_networks; j++) {
                        weights[j] += LEARNING_RATE * delta * network[j].output_layer.neurons[0].output;
                    }

                    bias += LEARNING_RATE * delta;
            }

        if (LOG_ENABLED) LOG(epoch+1, loss(expected_output, res), log_file);
        }
    }

    fclose(log_file);

    for (i = 0; i < data_size; i++){
            input = dataset[i][0];
            res = 0;
            for(j = 0; j < N_networks; j++){
                feedforward(&network[j], input);
                res += weights[j]*network[j].output_layer.neurons[0].output;
            }
            res += bias;
            fprintf(output_file,"%lf;%lf\n", input, res);
            mse += (res - dataset[i][1])*(res - dataset[i][1]);
    }
    mse /= data_size;
    printf("Load output done\n");
    printf("MSE: %lf\n", mse);

    for(j = 0; j < N_networks; j++){
        free(network[j].input_layer.neurons);
        for (i = 0; i < N_HIDDEN; i++) free(network[j].hidden_layer[i].neurons);
        free(network[j].output_layer.neurons);
    }

    return 0;
}
