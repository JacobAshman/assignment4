#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h> 
#include <limits.h>

void main(int argc, char **argv) {

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];  //allows input and output files to be called in ./a.out command
    printf("Processing text file [%s] . . . \n", inputFileName);

    FILE *f = fopen(inputFileName, "r"); //reads input file
    FILE *out = fopen(outputFileName, "w"); //writes in output file

    double power(double speed, double coef, double dragArea){
        double force = coef * .5 * 1.18 * speed * speed *dragArea;
        return force * speed;
    }

    char buffer[100];
    char *line = fgets(buffer, 100, f);
    int lineNum = 0;
    while(line != NULL) {
        int n = strlen(buffer);
        if(buffer[n-1] == '\n'){
            buffer[n-1] = '\0';
        }
        
        lineNum = 1 + lineNum;
        char *name = strtok(line, ",");
        char *coefficientToken = strtok(NULL, ",");
        char *areaToken = strtok(NULL, ",");   
        double coefficient = atof(coefficientToken);
        double area = atof(areaToken);
        if(area != -1) {
            fprintf(out, "%s,%s,%s,%.2f,%.2f,%.2f\n", name, coefficientToken, areaToken, power(26.8224, coefficient, area),
            power(31.2928, coefficient, area), power(35.7632, coefficient, area));
            printf("%s", areaToken);
        }

        line = fgets(buffer, 100, f);

    }
    printf("Number of lines %d\n", lineNum);

    fclose(f);
    fclose(out);  //closes both files


}