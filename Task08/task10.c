#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
#include "functions.h"
int parent(int a);
void perestroika_snizu(double *a, int n, int (*cmp)(double, double));
void perestroika_sverhu(double *a, int n, int (*cmp)(double, double));
void solve10(double *a, int n, int (*cmp)(double, double));
void heapify(double *a, int n, int (*cmp)(double, double));
int left_son(int i);
int right_son(int i);
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
    solve10(a, n, cmp);
    t = (clock() - t) / CLOCKS_PER_SEC;
    diff = difference(a, n, cmp);
    printf ("New array:\n");
    print_array (a, n, p); /* вывод нового состояния массива a */
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    free(a);
    return SUCCESS;
}
void solve10(double *a, int n, int (*cmp)(double, double)){
    double per = 0;
    heapify(a, n, cmp);
    for (int i = 1; i < n; i ++){
        per = a[0];
        a[0] = a[n - i];
        a[n - i] = per;
        perestroika_sverhu(a, n - i, cmp);
    }
}
// incorrect element is the last element
void perestroika_snizu(double *a, int n, int (*cmp)(double, double)){
    double per = 0;
    int wrong = n - 1;
    while (wrong != 0){
        if (cmp(a[wrong], a[parent(wrong)]) >= 0) /*a[wrong] <= a[parent(wrong)]*/{
            break;
        }
        else{
            per = a[wrong];
            a[wrong] = a[parent(wrong)];
            a[parent(wrong)] = per;
            wrong = parent(wrong);
        }
    }
}
void perestroika_sverhu(double *a, int n, int (*cmp)(double, double)){
    double per = 0;
    int wrong = 0;
    while (right_son(wrong) < n){
        if (cmp(a[left_son(wrong)], a[wrong]) >= 0 /*a[wrong] >= a[left_son(wrong)]*/ && cmp(a[right_son(wrong)], a[wrong]) >= 0 /*a[wrong] >= a[right_son(wrong)]*/){
            break;
        }
        else{
            if (cmp(a[right_son(wrong)], a[left_son(wrong)]) >= 0 /*a[left_son(wrong)] >= a[right_son(wrong)]*/){
                per = a[wrong];
                a[wrong] = a[left_son(wrong)];
                a[left_son(wrong)] = per;
                wrong = left_son(wrong);
            }
            else{
                per = a[wrong];
                a[wrong] = a[right_son(wrong)];
                a[right_son(wrong)] = per;
                wrong = right_son(wrong);
            }
        }
    }
    if (left_son(wrong) == n - 1 && cmp(a[wrong], a[left_son(wrong)]) > 0 /*a[wrong] < a[left_son(wrong)]*/){
        per = a[wrong];
        a[wrong] = a[left_son(wrong)];
        a[left_son(wrong)] = per;
        wrong = left_son(wrong);
    }
}
int parent(int a){
    return (a - 1) / 2;
}
int left_son(int i){
    return i * 2 + 1;
}
int right_son(int i){
    return i * 2 + 2;
}
void heapify(double *a, int n, int (*cmp)(double, double)){
    for (int i = 1; i < n; i ++){
        perestroika_snizu(a, i + 1, cmp);
    }
}