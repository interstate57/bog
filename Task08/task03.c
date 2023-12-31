#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"
#include "array_io.h"
int solve3 (double x, double* a, int n, int (*cmp)(double, double));
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    double x = 0;
    int c = 0; 
    char* name = 0;
    int task = 3;
    int (*cmp) (double, double);
    double* a;
    double t;
    int res = 0;
    if (!((argc == 6 || argc == 7) && sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &s) == 1 
    && sscanf(argv[1], "%lf", &x) == 1 && sscanf(argv[2], "%d", &c) == 1)){
        printf("Usage: %s x c n p s [name]\n", argv[0]);
        return 6;
    }
    if (argc == 7 && s == 0) name = argv[6];
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
    res = solve3(x, a, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    return SUCCESS;
}

int solve3 (double x, double* a, int n, int (*cmp)(double, double)){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    double vr = 0;
    while (i <= j){
        while (i < n){
            if (cmp(x, a[i]) >= 0){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (cmp(a[j], x) > 0){
                jnuzh = j;
                break;
            }
            j -= 1;
        }
        if (i <= j){
            vr = a[jnuzh];
            a[jnuzh] = a[inuzh];
            a[inuzh] = vr;
        }
    }
    return i;
}