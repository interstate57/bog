#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "functions.h"

extern int count;

int main(int argc, char* argv[]){
    double a = 0, b = 0, res = 0;
    int k = 0, n = 0;
    int task = 6;
    double t = 0;
    double (*f[])(double) = {f0, f1, f2, f3, f4, f5, f6};
    double (*f_current)(double);
    if (!((argc == 5) && sscanf(argv[1], "%le", &a) &&\
        sscanf(argv[2], "%le", &b) && sscanf(argv[3], "%d", &n) && sscanf(argv[4], "%d", &k) && (k >= 0 && k <= 6))){
        printf("Usage %s a b n k\n", argv[0]);
        return 1;
    }
    f_current = f[k];
    t = clock();
    res = solve6(f_current, a, b, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Res = %e Count = %d T = %.2f\n", argv[0], task, res, count, t);
    return 0;
}