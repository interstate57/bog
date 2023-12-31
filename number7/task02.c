#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#define EPS 1e-14
int solve2 (double* a, int n);
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 2;
    double* a;
    double t;
    int res = 0;
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
    res = solve2(a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, res, p);
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    return SUCCESS;
}
int solve2 (double* a, int n){
    int p = 0, q = 0, cnt = 0, f = 0;
    double sum = 0, srar = 0;
    for (int i = 1; i < n; i ++){
        if (equal(a[i - 1], a[i]) && f == 0){
            f = 1;
            cnt += 2;
            sum += a[i - 1] + a[i];
        }
        else if (equal(a[i - 1], a[i]) && f == 1){
            cnt += 1;
            sum += a[i];
        }
        else{
            f = 0;
        }
    }
    if (cnt == 0) return n;
    srar = sum / cnt;
    while (p < n){
        if (a[p] >= srar){
            a[q] = a[p];
            q += 1;
        }
        p += 1;
    }
    return q;
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}
