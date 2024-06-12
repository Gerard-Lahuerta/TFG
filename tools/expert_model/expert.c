#include <stdio.h>
#include <stdlib.h>

int number_to_roman(int num){

    char initial = 'A';

    char val[9] = {100, 90, 50, 40, 10, 9, 5, 4, 1};
    char symb[9][2] = {"C ", "XC", "L ", "XL", "X ", "IX", "V ", "IV", "I "};
    
    int roman_numeral = 0, i = 0;
    while(num > 0){
        // printf("-->%d | %d\n", val[i], num/val[i]);
        while( num-val[i] >= 0){
            if (symb[i][1] == ' '){
                roman_numeral += symb[i][0];
                num -= val[i];
                // printf("WOOOOW %d\n",j);
                roman_numeral -= initial;
            }
            else{
                roman_numeral += symb[i][1];
                roman_numeral -= symb[i][0];
                num -= val[i];
            }
            
        }
        i ++;
    }
    return roman_numeral;
}


int main() {
    int i, max_value = 40;
    double res;
    FILE *file;
    file = fopen("data/roman.csv", "w+"); // Abre el archivo para escritura

    if (file == NULL) {
        printf("Error while oppening the file.");
        return 1;
    }

    fprintf(file, "Value; Result\n");

    for (i = 1; i < max_value; i++) {
        res = number_to_roman(i)/10.0;
        // printf("%d-%d\n",i,res);
        fprintf(file, "%d;%lf\n", i, res);
    }

    fclose(file);
    printf(" -- Dataset generated succesfully --\n");

    return 0;
}