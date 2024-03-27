#include <stdio.h>
#include "MLP.h"
#include "definitions.h"

void save_neurons_to_csv(const char *filename, NeuralNetwork *network);
void load_neurons_from_csv(const char *filename, NeuralNetwork *network);