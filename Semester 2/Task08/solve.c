#include <math.h>
#include "solve.h"
#define EPS 1e-14
 

double solve1(double* a, double* x, double* xm, int n, int m){
    int i;
    xm = x;
    vectcpy(xm, x, n);
    for (i = 1; i <= m; i ++){
        vectcpy(x, xm, n);
        proisv_matr_na_vect(a, x, xm, n);
    }
    if (equal(skal_proisv(x, x, n), 0)){
        return 1e308;
    }
    else{
        return skal_proisv(xm, x, n) / skal_proisv(x, x, n);
    }
}

void solve2(double* a, double* x, double* b, double* xm, int n, int m, double tau){
    int i;
    vectcpy(xm, x, n);
    for (i = 1; i <= m; i++){
        vectcpy(x, xm, n);
        proisv_matr_na_vect(a, x, xm, n);
        razn_vect(b, xm, xm, n);
        umnozh_vect_na_ch(xm, xm, n, tau);
        sum_vect(xm, x, xm, n);
    }
}

void solve3(double* a, double* x, double* b, double* xm, double* r, int n, int m){
    int i;
    double tau = 0;
    vectcpy(xm, x, n);
    proisv_matr_na_vect(a, x, r, n);
    for (i = 1; i <= m; i++){
        razn_vect(r, b, r, n);
        proisv_matr_na_vect(a, r, xm, n);
        if (equal(skal_proisv(xm, r, n), 0)){
            vectcpy(xm, x, n);
            return;
        }
        else{
            tau = skal_proisv(r, r, n) / skal_proisv(xm, r, n);
        }
        xk(r, x, x, n, tau * (-1));
        sum_vect(r, b, r, n);
        xk(xm, r, r, n, tau * (-1));
    }
}

void solve4(double* a, double* x, double* b, double* xm, double* r, int n, int m){
    int i;
    double tau = 0;
    vectcpy(xm, x, n);
    proisv_matr_na_vect(a, x, r, n);
    for (i = 1; i <= m; i++){
        razn_vect(r, b, r, n);
        proisv_matr_na_vect(a, r, xm, n);
        if (equal(skal_proisv(xm, xm, n), 0)){
            vectcpy(xm, x, n);
            return;
        }
        else{
            tau = skal_proisv(xm, r, n) / skal_proisv(xm, xm, n);
        }
        xk(r, x, x, n, tau * (-1));
        sum_vect(r, b, r, n);
        xk(xm, r, r, n, tau * (-1));
    }
}

void solve7(double* a, double* x, double* b, double* xm, double* r, int n, int m, double tau){
    int i;
    vectcpy(xm, x, n);
    for (i = 1; i <= m; i++){
        vectcpy(x, xm, n);
        proisv_matr_na_vect(a, x, r, n);
        razn_vect(b, r, r, n);
        umnozh_vect_na_ch(r, r, n, tau);
        if (!proizv_d_obr_na_vect(a, r, n)){
            vectcpy(xm, x, n);
            return;
        }
        sum_vect(r, x, xm, n);
        
    }
}

void solve8(double* a, double* x, double* b, double* xm, double* r, double* w, int n, int m, double tau){
    int i;
    vectcpy(xm, x, n);
    for (i = 1; i <= m; i++){
        vectcpy(x, xm, n);
        proisv_matr_na_vect(a, x, r, n);
        razn_vect(b, r, r, n);
        umnozh_vect_na_ch(r, r, n, tau);
        if (!gauss_nizhn(a, r, w, n)){
            vectcpy(xm, x, n);
            return;
        }
        sum_vect(w, x, xm, n);
    }
}

void solve9(double* a, double* x, double* b, double* xm, double* r, double* w, int n, int m, double tau){
    int i;
    vectcpy(xm, x, n);
    for (i = 1; i <= m; i++){
        vectcpy(x, xm, n);
        proisv_matr_na_vect(a, x, r, n);
        razn_vect(b, r, r, n);
        umnozh_vect_na_ch(r, r, n, tau);
        if (!gauss_verh(a, r, w, n)){
            vectcpy(xm, x, n);
            return;
        }
        sum_vect(w, x, xm, n);
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

double r1_(double* a, double* b, double* xm, int n){
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

double r2_(double* xm, int n){
    int i;
    double res = 0;
    int sum = 0;
    for (i = 0; i < n; i++){
        res += fabs(xm[i] - (i % 2));
    }
    for (i = 0; i < n; i++){
        sum += (i % 2);
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

void sum_vect(double* a, double* b, double* c, int n){
    int i;
    for (i = 0; i < n; i++){
        c[i] = a[i] + b[i];
    }
}

void umnozh_vect_na_ch(double* a, double* b, int n, double tau){
    int i;
    for (i = 0; i < n; i++){
        b[i] = a[i] * tau;
    }
}

void vectcpy(double* a, double* b, int n){
    int i;
    for (i = 0; i < n; i++){
        a[i] = b[i];
    }
}

int equal(double x, double y){
    if ((fabs (x - y)) < (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

void xk(double* a, double* b, double* c, int n, double tau){
    int i;
    for (i = 0; i < n; i++){
        c[i] = a[i] * tau + b[i];
    }
}

int proizv_d_obr_na_vect(double* a, double* b, int n){
    int i;
    for (i = 0; i < n; i++){
        if (!equal(a[i * n + i], 0)){
            b[i] = b[i] / a[i * n + i];
        }
        else{
            return 0;
        }
    }
    return 1;
}

int gauss_nizhn(double* a, double* r, double* w, int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < i; j++){
            r[i] -= a[i * n + j] * w[j];
        }
        if (!equal(a[i * n + i], 0))
            w[i] = r[i] / a[i * n + i];
        else{
            return 0;
        }
    }
    return 1;
}

int gauss_verh(double* a, double* r, double* w, int n){
    int i, j;
    for (i = n - 1; i > -1; i++){
        for (j = n - 1; j < i; j++){
            r[i] -= a[i * n + j] * w[j];
        }
        if (!equal(a[i * n + i], 0))
            w[i] = r[i] / a[i * n + i];
        else{
            return 0;
        }
    }
    return 1;
}