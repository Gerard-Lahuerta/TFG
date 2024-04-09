#include "costFunctions.h"

double quadratic_cost(double expected_output, double actual_output) {
    return 0.5 * pow(expected_output - actual_output, 2);
}

double quadratic_cost_derivative(double expected_output, double actual_output) {
    return expected_output - actual_output;
}