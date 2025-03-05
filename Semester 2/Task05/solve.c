#define EPS 1e-14
#include <math.h>
#include "solve.h"

int equal(double x, double y){
    if ((fabs (x - y)) < (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

int solve1(double* a, int n){
    int i, j;
    for (i = 0; i < n; i ++){
        for (j = i + 1; j < n; j++){
            if (!equal(a[i * n + j], a[i + j * n]))
                return 0;
        }
    }
    return 1;
}

double solve2(double* a, int n){
    double sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += *a;
        a += (n + 1);
    }
    return sum;
}

void solve3(double* a, int n){
    int i, j;
    double vr = 0;
    for (i = 0; i < n; i ++){
        for (j = i + 1; j < n; j++){
            vr = a[i * n + j];
            a[i * n + j] = a[i + j * n];
            a[i + j * n] = vr;
        }
    }
}

void solve4(double* a, int n){
    int i, j;
    double vr = 0;
    for (i = 0; i < n; i ++){
        for (j = i + 1; j < n; j++){
            vr = (a[i * n + j] + a[i + j * n]) / 2;
            a[i * n + j] = vr;
            a[i + j * n] = vr;
        }
    }
}

void solve5(double* a, int n){
    int i, j;
    double vr = 0;
    for (i = 0; i < n; i ++){
        for (j = i + 1; j < n; j++){
            vr = (a[i * n + j] - a[i + j * n]) / 2;
            a[i * n + j] = vr;
            a[i + j * n] = vr * (-1);
        }
    }
    for (i = 0; i < n; i++) {
        *a = 0;
        a += (n + 1);
    }
}

void solve6(double* a, int n, int m, int i, int j){
    int k;
    double vr = 0;
    double* b = a + m * (i - 1);
    double* c = a + m * (j - 1);
    (void) n;
    for (k = 0; k < m; k ++){
        vr = b[k];
        b[k] = c[k];
        c[k] = vr;
    }
}

void solve7(double* a, int n, int m, int i, int j){
    int k;
    double vr = 0;
    double* b = a + (i - 1);
    double* c = a + (j - 1);
    for (k = 0; k < n; k ++){
        vr = b[k * m];
        b[k * m] = c[k * m];
        c[k * m] = vr;
    }
}

void solve8(double* a, int n, int m, int i, int j, double r){
    int k;
    double* b = a + m * (i - 1);
    double* c = a + m * (j - 1);
    (void) n;
    for (k = 0; k < m; k ++){
        c[k] += b[k] * r;
    }
}

void solve9(double* a, double* b, double* c, int n, int m){
    int i, j;
    for (i = 0; i < n; i++){
        double sum = 0;
        double* astr = a + m * i;
        for (j = 0; j < m; j++){
            sum += astr[j] * b[j];
        }
        c[i] = sum;
    }
}

void solve10(double* a, double* b, double* c, int n, int m, int k){
    int i, j, p; 
    for(i = 0; i < n; i ++){
        for (p = 0; p < k; p++){
            double sum = 0;
            double* astr = a + m * i;
            double* bstolb = b + p;
            for (j = 0; j < m; j ++){
                sum += astr[j] * bstolb[j * k];
            }
            c[i * k + p] = sum;
        }
    }
}