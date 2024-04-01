#include <stdio.h>
#include <math.h>

int main() {

    double root, i, step;
    unsigned max_value = 100;
    unsigned char decimals = 2;

    FILE *file;
    file = fopen("data/roots.csv", "w+"); // Abre el archivo para escritura

    if (file == NULL) {
        printf("Error while oppening the file.");
        return 1;
    }

    step = pow(10, -decimals);

    fprintf(file, "Value; Square root\n");

    for (i = 0; i < max_value; i+=step) {
        root = sqrt(i);
        fprintf(file, "%lf;%lf\n", i, root);
    }

    fclose(file);

    printf("dataset generated succesfully\n");

    return 0;
}