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

    char N_networks = 3;
    NeuralNetwork *network = (NeuralNetwork*) malloc(N_networks * sizeof(NeuralNetwork));
    double *weights = (double*) malloc(N_networks * sizeof(double));
    double bias = 0, delta;

    // load dataset
    char* dataset_file = "data/roman.csv";
    int index, i, j, data_size = 0;
    double** dataset = read_dataset(dataset_file, &data_size);

    for(i = 0; i < N_networks; i++){
        network[i] = create_network(1, 2, 4, 1, loss_derivative, activation_function, activation_function_derivative);
        weights[i] = (rand() % N_networks)/N_networks;
    }

    // Variables
    unsigned epoch, epochs = 1000000, red = 1000;
    double input, expected_output, res, mse = 0;
    FILE* log_file = fopen(log_name,"w+");
    FILE* output_file = fopen(output,"w+");

    unsigned order[data_size];
    for ( i = 0; i < data_size; i++) order[i] = i;

    double lr = 1;

    for (epoch = 0; epoch < epochs; epoch++) {
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
                backpropagation(&network[j], delta, weights[j], lr);
                weights[j] += lr * delta * network[j].output_layer.neurons[0].output * loss(expected_output, res);
                // bias += LEARNING_RATE * delta;
            }


        }
        if (LOG_ENABLED) LOG(epoch+1, loss(expected_output, res), log_file);
        if (epoch == red){ lr/= 10; red*=10;}
        // if (epoch%10) lr/=10;
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
        printf("wheight %d --> %lf\n",j,weights[j]);
        free(network[j].input_layer.neurons);
        for (i = 0; i < N_HIDDEN; i++) free(network[j].hidden_layer[i].neurons);
        free(network[j].output_layer.neurons);
    }

    return 0;
}
