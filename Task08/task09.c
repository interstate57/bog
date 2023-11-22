#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
void solve9 (double* a, int n);
int polov_sort (double x, double* a, int n);
int equal(double x, double y);
int main(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name = 0;
    int task = 9;
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
    solve9(a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
void solve9 (double* a, int n){
    int i = 0, sr = 0; 
    double per = 0;
    while (n > 1){
        sr = (n - 1) / 2;
        i = polov_sort(a[sr], a, n);
        if (i > n - i){
            solve9(a + i, n - i);
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
                solve9(a + 0, i);
                a += i;
                n -= i;
                continue;
            }
        }
    }
}

int polov_sort (double x, double* a, int n){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    double vr = 0;
    while (i <= j){
        while (i < n){
            if (a[i] >= x){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (a[j] < x){
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

