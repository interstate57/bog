#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#include "functions.h"
void solve8 (double* a, double* b, int n, int (*cmp)(double, double));
void merge (double* a, double* b, int n, int m, double* c, int (*cmp)(double, double));
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 8;
    double* a;
    double* b;
    int c = 0;
    int (*cmp) (double, double);
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
    b = (double*)malloc(n * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        return 2;
    }
    t = clock();
    solve8(a, b, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n, cmp);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    free(b);
    return SUCCESS;
}
void solve8 (double* a, double* b, int n, int (*cmp)(double, double)){
    int i;
    int j = 1;
    double* a_orig = a;
    double* c;
    while (j < n){
        for (i = 0; i < n; i += 2 * j){
            if (i + 2 * j >= n){
                if (i + j >= n){
                    merge(a + i, a, n - i, 0, b + i, cmp);
                }
                else{
                    merge(a + i, a + i + j, j, n - i - j, b + i, cmp);
                }
                
            }
            else{
                merge(a + i, a + i + j, j, j, b + i, cmp);
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
void merge (double* a, double* b, int n, int m, double* c, int (*cmp)(double, double)){
    int i = 0, j = 0, k = 0;
    while (i != n && j != m){
        if (cmp(a[i], b[j]) > 0){
            c[k] = a[i];
            i += 1;
            k += 1;
        }
        else if (cmp(b[j], a[i]) > 0){
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