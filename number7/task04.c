#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define EPS 1e-14
#include "array_io.h"
int solve4 (int k, double* a, int n);
int equal(double x, double y);
double maxch(double a, double b);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    int k = 0; 
    char* name = 0;
    int task = 4;
    double* a;
    double t;
    int res = 0;
    if (!((argc == 5 || argc == 6) && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1 && sscanf(argv[1], "%d", &k) == 1)){
        printf("Usage: %s k n p s [name]\n", argv[0]);
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
    res = solve4(k, a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, res, p); 
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",argv[0], task, res, t);
    free(a);
    return SUCCESS;
}

int solve4 (int k, double* a, int n){
    double max = a[0];
    int p = 0, q = 0, cnt_current = 0, f = 0, f1 = 0;
    double current_max = 0;
    for (int i = 1; i < n; i ++){
        if (equal(a[i - 1], a[i]) && f == 0){
            f = 1;
            cnt_current += 2;
            current_max = a[i];
            f1 = 1;
        }
        else if (equal(a[i - 1], a[i]) && f == 1){
            cnt_current += 1;
        }
        else{
            if (cnt_current >= k){
                max = maxch(max, current_max);
            }
            cnt_current = 0;
            f = 0;
        }
    }
    if (cnt_current >= k){
        max = maxch(max, current_max);
    }
    if (f1 == 0){
      return n;
    }
    while (p < n){
        if (a[p] >= max){
            a[q] = a[p];
            q += 1;
        }
        p += 1;
    }
    return q;
}
double maxch(double a, double b){
    if (a > b) return a;
    return b;
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}
