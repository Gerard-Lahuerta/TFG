#include "utils.h"

double quadratic_cost(double expected_output, double actual_output) {
    return 0.5 * pow(expected_output - actual_output, 2);
}

double quadratic_cost_derivative(double expected_output, double actual_output) {
    return expected_output - actual_output;
}

// ----------------------------------------------------------------------------------

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// ----------------------------------------------------------------------------------

void write_to_log(unsigned epoch, double loss, FILE* log_file) {
    if (log_file != NULL) {
        fprintf(log_file, "%d;%d\n", epoch, loss);
    }
}