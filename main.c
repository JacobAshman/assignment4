#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#include "functions.c"

//Creates structure
typedef struct {
    char name[100];
    char coefficient[20];
    char area[20];
    double mph60[20];
    double mph70[20];
    double mph80[20];
} Car;


void main(int argc, char **argv) {

    //allows input and output files to be called in ./a.out command
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];  
    printf("Processing text file [%s] . . . \n", inputFileName);

    //reads input file and writes output file
    FILE *f = fopen(inputFileName, "r"); 
    FILE *out = fopen(outputFileName, "w");

    //Declares strings, integers, and arrays
    int *areaCars = (int *) malloc(10000 * sizeof(int));
    char buffer[100];
    char *line = fgets(buffer, 100, f);
    int totLines = 0;
    int areaLines = 0;
    int i = 0;
    const int m = 1000;
    Car c[m];


    while(line != NULL) {

        //Removes \n from the end of the string
        int n = strlen(buffer); 
        if(buffer[n-1] == '\n'){
            buffer[n-1] = '\0';
        }

        //Breaks string when it hits a "," and stores it as a token 
        char *nameToken = strtok(line, ",");
        char *coefficientToken = strtok(NULL, ",");
        char *areaToken = strtok(NULL, ",");

        //Converts to a double
        double coefficient = atof(coefficientToken);
        double area = atof(areaToken);

        //Stores car data in structure if the drag area isn't -1
        //calculates power
        if(area != -1) {
            strcpy(c[i].name, nameToken);
            strcpy(c[i].coefficient, coefficientToken);
            strcpy(c[i].area, areaToken);
            c[i].mph60[i] = power(26.8224, coefficient, area);
            c[i].mph70[i] = power(31.2928, coefficient, area);
            c[i].mph80[i] = power(35.7632, coefficient, area);
            fprintf(out, "%s,%s,%s,%.02f,%.02f,%.02f\n", c[i].name, c[i].coefficient, c[i].area, c[i].mph60[i], c[i].mph70[i], c[i].mph80[i]);
            areaCars[areaLines] = i;
            areaLines = areaLines + 1;
            }

        line = fgets(buffer, 100, f);
        totLines = 1 + totLines;
        i = i + 1;
    }

    printf("--- completed reading %d lines of data\n", totLines);
    printf("Computing the power requirements at 60 mph, 70 mph, and 80 mph ...\nWriting out all automobiles that have a positive drag area to output file %s ... \n", outputFileName);
    printf("--- completed writing %d lines\n", areaLines);
    printf("Computing pair-based comparisons w.r.t. to drag coefficients and power @ 60 mph ...\n");

    //Prints information comparing drag area and power.
    for(i=0; i<areaLines; i++){
        double area0 = atof(c[areaCars[i]].area);
            for(int j=0; j<areaLines; j++){
                double area1 = atof(c[areaCars[j]].area);
                    if(area0 > area1 && c[areaCars[i]].mph60[areaCars[i]] < c[areaCars[j]].mph60[areaCars[j]]){
                        printf("--- %s has a larger drag area than %s, but a smaller power required.\n", c[areaCars[i]].name, c[areaCars[j]].name);
                        }
                }   
        }

    //closes both files
    fclose(f);
    fclose(out);  
    }