#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#include "functions.h"
void solve7 (double* a, int n, int (*cmp)(double, double));
int binpoisk (double x, double* a, int n, int (*cmp)(double, double));
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 7;
    int c = 0;
    int (*cmp) (double, double);
    double* a;
    double t;
    int diff = 0;
    if (!((argc == 5 || argc == 6) && sscanf(argv[1], "%d", &c) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1)){
        printf("Usage: %s c n p s [name]\n", argv[0]);
        return 6;
    }
    if (n <= 0 || p < 0){
        printf("Usage: %s c n p s [name]\n", argv[0]);
        return 6;
    }
    if (argc == 6 && s == 0) name = argv[5];
    if (c == 1){
        cmp = vosrastanie;
    }
    else if (c == 2){
        cmp = ubuvanie;
    }
    else{
        return 6;
    }
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
                case ERROR_READ: printf("Cannot read %s;\n", name); break;
                default: printf("Unknown Error %d in file %s;\n", res1, name);
            }
            free(a);
            return 3;
        }
    }
    else init_array(a, n, s);
    print_array(a, n, p);
    t = clock();
    solve7(a, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n, cmp);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
void solve7 (double* a, int n, int (*cmp)(double, double)){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1, cmp);
        double vr = 0;
        if (nuzh != i + 1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}
int binpoisk (double x, double* a, int n, int (*cmp)(double, double)){
    int inach = 0, ikon = n, s = 0;
    if (cmp(a[n - 1], x) > 0){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (cmp(a[s], x) > 0){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}