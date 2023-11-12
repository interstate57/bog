#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#define EPS 1e-14
int solve6 (double* a, int n);
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 6;
    double* a;
    double t;
    int diff = 0;
    if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &s) == 1)){
        printf("Usage: %s n p s [name]\n", argv[0]);
        return 6;
    }
    if (n <= 0 || p < 0){
        printf("Usage: %s n p s [name]\n", argv[0]);
        return 6;
    }
    if (argc == 5 && s == 0) name = argv[4];
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
    diff = solve6(a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
int solve6 (double* a, int n){
    int i, j;
    int ans = 0;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        double vr = 0;
        for (j = 0; j < i ; j ++){
            if (a[j] > a[i]){
                nuzh = j;
                break;
            }
        }
        if (nuzh != -1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
    for (i = 0; i < n - 1; i ++){
        if (a[i] < a[i + 1]) ans += 1;
    }
    return ans;
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}