#include <math.h>
#include <stdio.h>
#include "solve.h"
#include "array_io.h"
#define EPS 1e-16

double norma_mtrx(double* a, int n){
    int i, j;
    double max = 0;
    for (i = 0; i < n; i++){
        double cur = 0;
        for (j = 0; j < n; j++){
            cur += fabs(a[i * n + j]);
        }
        if (cur > max){
            max = cur;
        }
    }
    return max;
}

int equal_zero(double a, double b){
    if (fabs(a) <= EPS * b) return 1;
    return 0;
}

int equal(double x, double y){
    if ((fabs (x - y)) <= (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

int solve(int n, double* a, double* b, double* x){
    int i, j, k;
    double norma = norma_mtrx(a, n);
    for (i = 0; i < n; i++){
        double del = a[i * n + i];
        if (equal_zero(del, norma)) return -1;
        for (j = i; j < n; j++){
            a[i * n + j] /= del;
        }
        b[i] /= del;
        for (k = 0; k < n; k++){
            double chislo = a[k * n + i];
            if (k == i){
                continue;
            }
            for (j = i; j < n; j++){
                a[k * n + j] -= chislo * a[i * n + j];
            }
            b[k] -= chislo * b[i];
            
        }
    }
    vectcpy(x, b, n);
    return 0;
}

void vectcpy(double* a, double* b, int n){
    int i;
    for (i = 0; i < n; i++){
        a[i] = b[i];
    }
}

void razn_vect(double* a, double* b, double* c, int n){
    int i;
    for (i = 0; i < n; i++){
        c[i] = a[i] - b[i];
    }
}

double norma_vect(double* a, int n){
    int i;
    double sum = 0;
    for (i = 0; i < n; i++){
        sum += fabs(a[i]);
    }
    return sum;
}

double calc_r1(double* a, double* b, double* x, int n, int* error){
    int i, j;
    double norma_x = 0;
    double norma_b = norma_vect(b, n);
    *error = 0;
    if (equal(0., norma_b)){
        *error = 1;
        return -1.;
    }
    for (i = 0; i < n; i++){
        double sum = 0;
        for (j = 0; j < n; j++){
            sum += a[i * n + j] * x[j];
        }
        b[i] = sum - b[i];
    }
    norma_x = norma_vect(b, n);
    return norma_x / norma_b;
}

double calc_r2(double* x, int n){
    double chisl = 0;
    double znam = 0;
    int i;
    for (i = 0; i < n; i++){
        chisl += fabs(x[i] - ((i + 1) % 2));
        znam += ((i + 1) % 2);
    }
    return chisl / znam;
}