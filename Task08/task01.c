#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define EPS 1e-14
#include "array_io.h"
int solve1 (double x, double* a, int n);
double maxch(double a, double b);
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    double x = 0; 
    char* name = 0;
    int task = 1;
    double* a;
    double t;
    int res = 0;
    if (!((argc == 5 || argc == 6) && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1 && sscanf(argv[1], "%lf", &x) == 1)){
        printf("Usage: %s x n p s [name]\n", argv[0]);
        return 6;
    }
    if (argc == 6 && s == 0) name = argv[5];
    a = (double*)malloc(n * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (name){
        int res1 = read_array(a, n, name);
        if (res1 != SUCCESS){
            switch (res1){
                case ERROR_OPEN: printf("Cannot open %s;\n", name); break;
                case ERROR_READ: printf("Cannot read %s\n", name); break;
                default: printf("Unknown Error %d in file %s;\n", res1, name);
            }
            free(a);
            return 3;
        }
    }
    else init_array(a, n, s);
    print_array(a, n, p);
    t = clock();
    res = solve1(x, a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    return SUCCESS;
}

int solve1 (double x, double* a, int n){
    int inach = 0, ikon = n, s = 0;
    if (x > a[n - 1]){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (a[s] > x){
            ikon = s;
        }
        else{
            inach = s + 1;
        }
    }
    return inach;
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}