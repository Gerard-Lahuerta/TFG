#include "load.h"

double** read_dataset(char* file_name, int* data_size){
    unsigned rows = 0, i;
    int character;

    FILE* file = fopen(file_name, "r");
    if (file == NULL) { printf("Error file not found.\n"); return NULL;}

    while ( (character = fgetc(file)) != EOF){ if (character == '\n') rows++; }
    rows--;

    double** dataset = (double**) malloc(rows*sizeof(double*));

    fseek(file, 0, SEEK_SET);

    while ( fgetc(file) != '\n');

    for (i = 0; i < rows; i++){
        dataset[i] = (double*) malloc(2*sizeof(double));
        fscanf(file,"%lf;%lf\n", &dataset[i][0], &dataset[i][1]);
    }
    
    fclose(file);
    *data_size = rows;
    return dataset;
}

void save_neurons_to_csv(const char *filename, NeuralNetwork *network) {
    unsigned i,j,k, size, input_size, hidden_size, n_hidden, output_size;
    input_size = network->input_size;
    hidden_size = network->hidden_size;
    n_hidden = network->n_hidden;
    output_size = network->output_size;

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Layer, Neuron, Weights, Bias\n");

    // Write data for input layer
    for (i = 0; i < input_size; i++) {
        Neuron *neuron = &network->input_layer.neurons[i];
        fprintf(file, "Input, %d, ", i); // No input for input layer neurons
        for (j = 0; j < network->input_layer.input_size; j++) {
            fprintf(file, "%lf, ", neuron->weights[j]);
        }
        fprintf(file, "%lf\n", neuron->bias);
    }

    // Write data for hidden layers
    for (k = 0; k < n_hidden; k++){
        size = network->hidden_layer[k].input_size;
        for (i = 0; i < hidden_size; i++) {
            Neuron *neuron = &network->hidden_layer[k].neurons[i];
            fprintf(file, "Hidden, %d - %d, ", k, i); // Input for hidden layer neurons
            for (j = 0; j < size; j++) fprintf(file, "%lf, ", neuron->weights[j]);
            fprintf(file, "%lf\n", neuron->bias);
        }
    }

    // Write data for output layer
    for (i = 0; i < output_size; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];
        fprintf(file, "Output, %d, ", i); // Input for output layer neurons
        for (j = 0; j < network->output_layer.input_size; j++) {
            fprintf(file, " %lf,", neuron->weights[j]);
        }
        fprintf(file, "%lf\n", neuron->bias);
    }

    fclose(file);
}

void load_neurons_from_csv(const char *filename, NeuralNetwork *network) {
    unsigned i,j,k, size, input_size, hidden_size, n_hidden, output_size;
    input_size = network->input_size;
    hidden_size = network->hidden_size;
    n_hidden = network->n_hidden;
    output_size = network->output_size;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[1024];
    fgets(line, sizeof(line), file); 

    // Read data for input layer
    for (i = 0; i < input_size; i++) {
        Neuron *neuron = &network->input_layer.neurons[i];
        size = network->input_layer.input_size;
        fscanf(file, "Input,%*d,");
        for (j = 0; j < size; j++) {
            fscanf(file, "%lf,", &neuron->weights[j]);
        }
        fscanf(file, "%lf\n", &neuron->bias);
    }

    // Read data for hidden layer
    for (k = 0; k < n_hidden; k++){
        for (i = 0; i < hidden_size; i++) {
            Neuron *neuron = &network->hidden_layer[k].neurons[i];
            size = network->hidden_layer[k].input_size;
            fscanf(file, "Hidden,%*d-%*d,");
            for (j = 0; j < size; j++) fscanf(file, "%lf,", &neuron->weights[j]);
            fscanf(file, "%lf\n", &neuron->bias);
        }
    }

    // Read data for output layer
    for (i = 0; i < output_size; i++) {
        Neuron *neuron = &network->output_layer.neurons[i];
        fscanf(file, "Output,%*d,");
        for (j = 0; j < network->output_layer.input_size; j++) {
            fscanf(file, "%lf,", &neuron->weights[j]);
        }
        fscanf(file, "%lf\n", &neuron->bias);
    }

    fclose(file);
}

