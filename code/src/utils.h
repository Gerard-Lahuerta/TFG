#include "definitions.h"

double quadratic_cost(double expected_output, double actual_output);
double quadratic_cost_derivative(double expected_output, double actual_output);

// -----------------------------------------------------------------------------

double sigmoid(double x);
double sigmoid_derivative(double x);

// -----------------------------------------------------------------------------

void LOG(unsigned epoch, double loss, FILE* file_log);
