#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "functions.h"

extern int count;

int main(int argc, char* argv[]){
    double a = 0, b = 0, epsilon = 0, x = 0, fx = 0;
    int M = 0, k = 0;
    int task = 10, res = 0;
    double t = 0;
    double (*f[])(double) = {f0, f1, f2, f3, f4, f5, f6};
    double (*f_current)(double);
    if (!((argc == 6) && sscanf(argv[1], "%le", &a) &&\
        sscanf(argv[2], "%le", &b) && sscanf(argv[3], "%le", &epsilon) &&\
        sscanf(argv[4], "%d", &M) && sscanf(argv[5], "%d", &k) && (k >= 0 && k <= 6))){
        printf("Usage %s a b epsilon M k\n", argv[0]);
        return 1;
    }
    f_current = f[k];
    t = clock();
    res = solve10(f_current, a, b, epsilon, M, &x);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res < 0){
        printf ("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, count, t);
    }
    else{
        fx = f_current(x);
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, fx, res + 1, count, t);
    }
    return 0;
}