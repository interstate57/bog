#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#include "functions.h"
void solve9 (double* a, int n, int (*cmp)(double, double));
int polov_sort (double x, double* a, int n, int (*cmp)(double, double));
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 9;
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
    solve9(a, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n, cmp);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
void solve9 (double* a, int n, int (*cmp)(double, double)){
    int i = 0, sr = 0; 
    double per = 0;
    while (n > 1){
        sr = (n - 1) / 2;
        i = polov_sort(a[sr], a, n, cmp);
        if (i > n - i){
            solve9(a + i, n - i, cmp);
            continue;
        }
        else{
            if (i == 0){
                per = a[i];
                a[i] = a[sr];
                a[sr] = per;
                a += 1;
                n -= 1;
                continue;
            }
            if (i > 0) {
                solve9(a + 0, i, cmp);
                a += i;
                n -= i;
                continue;
            }
        }
    }
}

int polov_sort (double x, double* a, int n, int (*cmp)(double, double)){
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

