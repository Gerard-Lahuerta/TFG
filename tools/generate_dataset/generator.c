#include <stdio.h>

#include <math.h>
#define M_PI 3.14159265358979323846

int main() {

    double res, i, step;
    unsigned char decimals = 2;

    FILE *file;
    file = fopen("data/poli3.csv", "w+"); // Abre el archivo para escritura

    if (file == NULL) {
        printf("Error while oppening the file.");
        return 1;
    }

    step = pow(10, -decimals);

    fprintf(file, "Value; Result\n");

    for (i = -2; i < 2; i+=step) {
        res = i*i*i;
        fprintf(file, "%lf;%lf\n", i, res);
    }

    fclose(file);
    printf(" -- Dataset generated succesfully --\n");

    return 0;
}