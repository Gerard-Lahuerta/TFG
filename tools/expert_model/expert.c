#include <stdio.h>
#include <stdlib.h>

char* number_to_roman(num){

    val = [10, 9, 5, 4, 1-]
    syms = [
        "X", "IX", "V", "IV", "I"
    ]
    
    roman_numeral = ""
    i = 0
    while num > 0:
        for _ in range(num / val[i]):
            roman_numeral += syms[i]
            num -= val[i]
        i += 1
    return roman_numeral
}


int main() {
    unsigned i, max_value = 15;
    char* res;
    FILE *file;
    file = fopen("data/roman.csv", "w+"); // Abre el archivo para escritura

    if (file == NULL) {
        printf("Error while oppening the file.");
        return 1;
    }

    fprintf(file, "Value; Result\n");

    for (i = 0; i < max_value; i++) {
        res = number_to_roman(i);
        fprintf(file, "%lf;%s\n", i, res);
    }

    fclose(file);
    printf(" -- Dataset generated succesfully --\n");

    return 0;
}