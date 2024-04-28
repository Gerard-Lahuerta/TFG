#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Error: File name not introduced\n", argv[0]);
        return 1;
    }

    char* dir = "imgs";
    char* file = argv[1];

    char* name = strrchr(file, '/');
    if (name == NULL) { name = file; } 
    else { name++; }
    char *punto = strrchr(name, '.');
    if (punto != NULL) { *punto = '\0'; }

    FILE *gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set terminal png\n");
        fprintf(gnuplotPipe, "set output \"%s/%s.png\"\n",dir,name);

        fprintf(gnuplotPipe, "set title \"Datos - %s\"\n", name);

        fprintf(gnuplotPipe, "set xlabel \"EPOCHS\"\n");
        fprintf(gnuplotPipe, "set ylabel \"LOSS\"\n");

        fprintf(gnuplotPipe, "set datafile sep ';'\n");
        fprintf(gnuplotPipe, "set xrange [*:*]\n");
        fprintf(gnuplotPipe, "set yrange []\n");

        fprintf(gnuplotPipe, "plot \"%s.csv\" using 1:2 with linespoints\n",file);
        
        fprintf(gnuplotPipe, "exit\n");
        pclose(gnuplotPipe);
    } 
    else {
        printf("Error: Impossible to open Gnuplot terminal\n");
        return 2;
    }

    printf(" -- %s plotted --\n");

    return 0;
}