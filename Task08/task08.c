#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#define EPS 1e-14
void solve8 (double* a, double* b, int n);
void merge (double* a, double* b, int n, int m, double* c);
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 8;
    double* a;
    double* b;
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
    b = (double*)malloc(n * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        return 2;
    }
    t = clock();
    solve8(a, b, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
void solve8 (double* a, double* b, int n){
    int i;
    int j = 1;
    double* a_orig = a;
    double* c;
    while (j < n){
        for (i = 0; i < n; i += 2 * j){
            if (i + 2 * j >= n){
                if (i + j >= n){
                    merge(a + i, a, n - i, 0, b + i);
                }
                else{
                    merge(a + i, a + i + j, j, n - i - j, b + i);
                }
                
            }
            else{
                merge(a + i, a + i + j, j, j, b + i);
            }
        }
        c = a;
        a = b;
        b = c;
        j *= 2;
    }
    if (a != a_orig){
        for (int k = 0; k < n; k ++){
            a_orig[k] = a[k];
        }
    }
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}
void merge (double* a, double* b, int n, int m, double* c){
    int i = 0, j = 0, k = 0;
    while (i != n && j != m){
        if (a[i] < b[j]){
            c[k] = a[i];
            i += 1;
            k += 1;
        }
        else if (a[i] > b[j]){
            c[k] = b[j];
            j += 1;
            k += 1;
        }
        else{
            c[k] = a[i];
            i += 1;
            k += 1;
        }
    }
    if (i == n){
        for (; j < m; j ++){
            c[k] = b[j];
            k += 1;
        }
    }
    else if (j == m){
        for (; i < n; i ++){
            c[k] = a[i];
            k += 1;
        }
    }
}