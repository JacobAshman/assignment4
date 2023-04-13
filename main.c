#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#include "functions.c"

typedef struct {
    char name[100];
    char coefficient[20];
    char area[20];
} Car;


void main(int argc, char **argv) {



    char *inputFileName = argv[1];
    char *outputFileName = argv[2];  //allows input and output files to be called in ./a.out command
    printf("Processing text file [%s] . . . \n", inputFileName);

    FILE *f = fopen(inputFileName, "r"); //reads input file
    FILE *out = fopen(outputFileName, "w"); //writes in output file





    int *dragCar = (int *) malloc(10000 * sizeof(int));

    char buffer[100];
    char *line = fgets(buffer, 100, f);
    int totLines = 0;
    int goodLines = 0;
    int i = 0;
    const int m = 1000;
    Car c[m];
    while(line != NULL) {
        int n = strlen(buffer);
        if(buffer[n-1] == '\n'){
            buffer[n-1] = '\0';
        }


        char *name = strtok(line, ",");
        char *coefficientToken = strtok(NULL, ",");
        char *areaToken = strtok(NULL, ",");
        double coefficient = atof(coefficientToken);
        double area = atof(areaToken);
        if(area != -1) {
            strcpy(c[i].name, name);
            strcpy(c[i].coefficient, coefficientToken);
            strcpy(c[i].area, areaToken);
            fprintf(out, "%s,%s,%s,%.02f,%.02f,%.02f\n", c[i].name, c[i].coefficient, c[i].area,
            power(26.8224, coefficient, area), power(31.2928, coefficient, area), power(35.7632, coefficient, area));
            dragCar[goodLines] = i;
            goodLines = goodLines + 1;
            }
        line = fgets(buffer, 100, f);
        totLines = 1 + totLines;
        i = i + 1;
    }

    printf("--- completed reading %d lines of data\n", totLines);
    printf("Computing the power requirements at 60 mph, 70 mph, and 80 mph ...\nWriting out all automobiles that have a positive drag area to output file %s ... \n", outputFileName);
    printf("--- completed writing %d lines\n", goodLines);
    printf("Computing pair-based comparisons w.r.t. to drag coefficients and power @ 60 mph ...\n");
    for(i=0; i<goodLines; i++){
        double area0 = atof(c[dragCar[i]].area);
        double power0 = power(26.8224, atof(c[dragCar[i]].coefficient) ,atof(c[dragCar[i]].area));
        for(int j=0; j<goodLines; j++){
            double area1 = atof(c[dragCar[j]].area);
            double power1 = power(26.8224, atof(c[dragCar[j]].coefficient) ,atof(c[dragCar[j]].area));
            if(area0 > area1 && power0 < power1){
                printf("--- %s has a larger drag area then %s, but a smaller power required.\n", c[dragCar[i]].name, c[dragCar[j]].name);
            }
        }
    }

    fclose(f);
    fclose(out);  //closes both files


}