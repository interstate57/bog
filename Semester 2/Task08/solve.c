#include <math.h>
#include "solve.h"


double solve1(double* a, double* x, double* xm, int n, int m){
    /*деление на 0*/
    int i;
    for (i = 1; i <= m; i ++){
        proisv_matr_na_vect(a, x, xm, n);
    }
    return skal_proisv(xm, x, n) / skal_proisv(x, x, n);
}

void solve2(double* a, double* x, double* b, double* xm, int n, int m, double tau){
    int i;
    for (i = 1; i <= m; i++){
        proisv_matr_na_vect(a, x, xm, n);
        razn_vect(b, xm, xm, n);
        umnozh_vect_na_ch(xm, xm, n, tau);
        razn_vect(xm, x, xm, n);
    }
}

double r2_1(double* a, double* xm, int n, double r1){
    int i, j;
    double res = 0;
    double sum = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            res += a[i * n + j] * xm[j];
        }
        res += fabs(res - r1 * xm[i]);
    }
    for (i = 0; i < n; i++){
        sum += fabs(r1 * xm[i]);
    }
    return res / sum;
}

double r1(double* a, double* b, double* xm, int n){
    int i, j;
    double res = 0;
    double sum = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            res += a[i * n + j] * xm[j];
        }
        res += fabs(res - b[i]);
    }
    for (i = 0; i < n; i++){
        sum += fabs(b[i]);
    }
    return res / sum;
}

double r2(double* xm, int n){
    int i, j;
    double res = 0;
    double sum = 0;
    for (i = 0; i < n; i++){
        res += fabs(xm[i] - (i % 2));
    }
    for (i = 0; i < n; i++){
        sum += fabs(i % 2);
    }
    return res / sum;
}

double skal_proisv(double* a, double* b, int n){
    double res = 0;
    for (int i = 0; i < n; i++){
        res += a[i] * b[i];
    }
    return res;
}

void proisv_matr_na_vect(double* a, double* b, double* c, int n){
    int i, j;
    for (i = 0; i < n; i++){
        double sum = 0;
        double* astr = a + n * i;
        for (j = 0; j < n; j++){
            sum += astr[j] * b[j];
        }
        c[i] = sum;
    }
}

void razn_vect(double* a, double* b, double* c, int n){
    int i;
    for (i = 0; i < n; i++){
        c[i] = a[i] - b[i];
    }
}
void umnozh_vect_na_ch(double* a, double* b, int n, double tau){
    int i;
    for (i = 0; i < n; i++){
        b[i] = a[i] * tau;
    }
}