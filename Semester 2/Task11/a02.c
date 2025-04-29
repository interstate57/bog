#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "functions.h"

extern int count;

int main(int argc, char* argv[]){
    double x0 = 0, epsilon = 0, x = 0, fx = 0;
    int M = 0, k = 0;
    int task = 2, res = 0;
    double t = 0;
    double (*f[])(double) = {f0, f1, f2, f3, f4, f5, f6};
    double (*f_current)(double);
    double (*d[])(double) = {d0, d1, d2, d3, d4, d5, d6};
    double (*d_current)(double);
    if (!((argc == 5) && sscanf(argv[1], "%le", &x0) &&\
        sscanf(argv[2], "%le", &epsilon) &&\
        sscanf(argv[3], "%d", &M) && sscanf(argv[4], "%d", &k) && (k >= 0 && k <= 6))){
        printf("Usage %s x0 epsilon M k\n", argv[0]);
        return 1;
    }
    f_current = f[k];
    d_current = d[k];
    t = clock();
    res = solve2(f_current, d_current, x0, epsilon, M, &x);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res < 0){
        printf ("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, count, t);
    }
    else{
        fx = f_current(x);
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, fx, res, count, t);
    }
    return 0;
}