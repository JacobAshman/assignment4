#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "functions.h"

    double power(double speed, double coef, double dragArea) {
        double force = coef * .5 * 1.18 * speed * speed *dragArea;
        return force * speed;
    }