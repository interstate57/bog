#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "solve.h"

int main(int argc, char* argv[]){
    double t, x, r1, r2, epsilon;
    int task = 5;
    if (!((argc == 3) && sscanf(argv[1], "%lf", &x) == 1 &&\
        sscanf(argv[2], "%lf", &epsilon))){
        printf("Usage %s x eps\n", argv[0]);
        return 1;
    }
    t = clock();
    r1 = solve5(x, epsilon);
    r2 = fabs(r1 - sin(x));
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);
    return 0;
}