#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "functions.h"
int equal(double x, double y);
void solve2 (double* a, double* b, int n, int m, double* c, int (*cmp)(double, double));
int main(int argc, char* argv[]){
    int n = 0, pa = 0, sa = 0, m = 0, pb = 0, sb = 0, diff = 0;
    char* name1 = 0;
    char* name2 = 0;
    int task = 2;
    int c1 = 0;
    int (*cmp) (double, double);
    double* a;
    double* b;
    double* c;
    double t;
    int has_formula_1 = 0, has_formula_2 = 0;
    if (argc == 10 || argc == 9 || argc == 8){
        if (!(sscanf(argv[1], "%d", &c1) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &pa) == 1 && sscanf(argv[4], "%d", &sa) == 1)){
            printf("Usage: %s c n pa sa [name1] m pb sb [name2]\n", argv[0]);
            return 6;
        }
        else{
            has_formula_1 = (sa != 0);
            if (has_formula_1){
                if (!(sscanf(argv[5], "%d", &m) == 1 && sscanf(argv[6], "%d", &pb) == 1 && sscanf(argv[7], "%d", &sb) == 1)){
                    printf("Usage: %s c n pa sa [name1] m pb sb [name2]\n", argv[0]);
                    return 6;
                }
                has_formula_2 = (sb != 0); 
            }
            else{
                if (!(sscanf(argv[6], "%d", &m) == 1 && sscanf(argv[7], "%d", &pb) == 1 && sscanf(argv[8], "%d", &sb) == 1)){
                    printf("Usage: %s c n pa sa [name1] m pb sb [name2]\n", argv[0]);
                    return 6;
                }
                has_formula_2 = (sb != 0);
            }
        }
    }
    else {
        printf("Usage: %s c n pa sa [name1] m pb sb [name2]\n", argv[0]);
        return 6;
    }
    if (!has_formula_1 && !has_formula_2){
        name1 = argv[5];
        name2 = argv[9];
    }
    else if (!has_formula_1 && has_formula_2){
        name1 = argv[5];
    }
    else if (has_formula_1 && !has_formula_2){
        name2 = argv[8];
    }
    if (c1 == 1){
        cmp = vosrastanie;
    }
    else if (c1 == 2){
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
    if (name1){
        int res1 = read_array(a, n, name1);
        if (res1 != SUCCESS){
            switch (res1){
                case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
                case ERROR_READ: printf("Cannot read %s;\n", name1); break;
                default: printf("Unknown Error %d in file %s;\n", res1, name1);
            }
            free(a);
            return 3;
        }
    }
    else init_array(a, n, sa);
    for (int i = 0; i < n - 1; i ++){
        if (cmp(a[i], a[i + 1]) < 0){
            printf("Araay a is not an increasing one\n");
            free(a);
            return 5;
        }
    }
    b = (double*)malloc(m * sizeof(double));
    if (!b){
        printf("Not enough memory!\n");
        free(a);
        return 2;
    }
    if (name2){
        int res2 = read_array(b, m, name2);
        if (res2 != SUCCESS){
            switch (res2){
                case ERROR_OPEN: printf("Cannot open %s;\n", name2); break;
                case ERROR_READ: printf("Cannot read %s;\n", name2); break;
                default: printf("Unknown Error %d in file %s;\n", res2, name2);
            }
            free(a);
            free(b);
            return 3;
        }
    }
    else init_array(b, m, sb);
    for (int i = 0; i < m - 1; i ++){
        if (cmp(b[i], b[i + 1]) < 0){
            printf("Araay b is not an increasing one\n");
            free(a);
            free(b);
            return 5;
        }
    }
    print_array(a, n, pa);
    print_array(b, m, pb);
    c = (double*)malloc((m + n) * sizeof(double));
    if (!c){
        printf("Not enough memory!\n");
        free(a);
        free(b);
        return 2;
    }
    t = clock();
    solve2(a, b, n, m, c, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference (c, n + m, cmp);
    printf ("New array:\n");
    print_array (c, n + m, pa + pb); /* вывод нового состояния массива c */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    free(b);
    free(c);
    return SUCCESS;
}
void solve2 (double* a, double* b, int n, int m, double* c, int (*cmp)(double, double)){
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