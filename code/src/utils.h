#include "definitions.h"

double quadratic_cost(double expected_output, double actual_output);
double quadratic_cost_derivative(double expected_output, double actual_output);

// -----------------------------------------------------------------------------

double sigmoid(double x);
double sigmoid_derivative(double x);

// -----------------------------------------------------------------------------

void write_to_log(unsigned epoch, double loss, FILE* file_log);

#if LOG_ENABLED 
#define LOG(epoch, loss) write_to_log(epoch, loss, file_log);
#else #define LOG(epoch, loss, file_log) do { } while (0);
#endif