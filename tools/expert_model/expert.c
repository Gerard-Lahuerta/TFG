#include <stdio.h>
#include <stdlib.h>

unsigned number_to_roman(unsigned num){

    char val[5] = {10, 9, 5, 4, 1};
    char symb[5][2] = {"X ", "IX", "V ", "IV", "I "};
    
    unsigned roman_numeral = 0, i = 0, j;
    while(num > 0){
        for( j = 0; j < num/val[i]; j++){
            if (symb[i][1] != ' '){
                roman_numeral += symb[i][0];
                num -= val[i];
            }
            else{
                roman_numeral += symb[i][0];
                roman_numeral -= symb[i][1];
                num -= val[i];
            }
            
        }
        i ++;
    }
    return roman_numeral;
}


int main() {
    unsigned i, max_value = 40;
    unsigned res;
    FILE *file;
    file = fopen("data/roman.csv", "w+"); // Abre el archivo para escritura

    if (file == NULL) {
        printf("Error while oppening the file.");
        return 1;
    }

    fprintf(file, "Value; Result\n");

    for (i = 0; i < max_value; i++) {
        res = number_to_roman(i);
        fprintf(file, "%d;%d\n", i, res);
    }

    fclose(file);
    printf(" -- Dataset generated succesfully --\n");

    return 0;
}