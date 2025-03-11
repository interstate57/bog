#define EPS 1e-14
#include <math.h>
#include <stdio.h>
#include "solve.h"
#include "array_io.h"

int equal(double x, double y){
    if ((fabs (x - y)) <= (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

double solve1(double* a, int n, int m){
    double max_s = 0;
    int i, j;
    for (i = 0; i < n; i++){
        double* b = a + m * i;
        double s = 0;
        for (j = 0; j < m; j++){
            s += fabs(b[j]);
        }
        if (s > max_s){
            max_s = s;
        }
    }
    return max_s;
}

double solve2(double* a, int n, int m){
    double max_s = 0;
    int i, j;
    for (i = 0; i < n; i++){
        double* b = a + i;
        double s = 0;
        for (j = 0; j < m; j++){
            s += fabs(b[j * m]);
        }
        if (s > max_s){
            max_s = s;
        }
    }
    return max_s;
}

void per_strok(double* a, int n, int m, int i, int j){
    int k;
    double vr = 0;
    double* b = a + m * (i - 1);
    double* c = a + m * (j - 1);
    (void) n;

    if (i == j)
        return;
    for (k = 0; k < m; k ++){
        vr = b[k];
        b[k] = c[k];
        c[k] = vr;
    }
}

void per_stolb(double* a, int n, int m, int i, int j){
    int k;
    double vr = 0;
    double* b = a + (i - 1);
    double* c = a + (j - 1);
    
    if (i == j)
        return;
    for (k = 0; k < n; k ++){
        vr = b[k * m];
        b[k * m] = c[k * m];
        c[k * m] = vr;
    }
}

double solve11(double* a, int n, int m){
    double max_a = 0;
    int max_i = 0, max_j = 0;
    int i, j;
    for (i = 0; i < n; i++){
        double* b = a + m * i;
        for (j = 0; j < m; j++){
            if (fabs(b[j]) > max_a){
                max_a = b[j];
                max_i = i;
                max_j = j;
            }
        }
    }
    per_strok(a, n, m, 1, max_i);
    per_stolb(a, n, m, 1, max_j);
    return fabs(a[0]);
}

double solve7(double* a, int n, int m){
    double max_a = 0;
    int i, j;
    for (i = 1; i < n - 1; i++){
        double* b = a + m * (i - 1);
        for (j = 1; j < m - 1; j++){
            b[m + j] = (b[j] + b[m + j + 1] + b[2 * m + j] + b[m + j - 1]) / 5;
        }
    }
    for(i = 0; i < n; i++){
        double* c = a + i * m;
        for (j = 0; j < m; j++){
            max_a = max_zn(max_a, fabs(c[j]));
        }
    }
    return max_a;
}

double solve8(double* a, int n, int m){
    double max_a = 0;
    int i, j;
    for (i = n - 1; i > 1; i--){
        double* b = a + m * (i - 1);
        for (j = m - 1; j > 1; j--){
            b[m + j] = (b[j] + b[m + j + 1] + b[2 * m + j] + b[m + j - 1]) / 5;
        }
    }
    for(i = 0; i < n; i++){
        double* c = a + i * m;
        for (j = 0; j < m; j++){
            max_a = max_zn(max_a, fabs(c[j]));
        }
    }
    return max_a;
}

double solve9(double* a, int n, int m){
    double max_a = 0;
    int i, j;
    for (i = 1; i < n - 1; i++){
        double* b = a + m * (i - 1);
        for (j = m - 1; j > 1; j--){
            b[m + j] = (b[j] + b[m + j + 1] + b[2 * m + j] + b[m + j - 1]) / 5;
        }
    }
    for(i = 0; i < n; i++){
        double* c = a + i * m;
        for (j = 0; j < m; j++){
            max_a = max_zn(max_a, fabs(c[j]));
        }
    }
    return max_a;
}

double solve10(double* a, int n, int m){
    double max_a = 0;
    int i, j;
    for (i = n - 1; i > 1; i--){
        double* b = a + m * (i - 1);
        for (j = 1; j < m - 1; j++){
            b[m + j] = (b[j] + b[m + j + 1] + b[2 * m + j] + b[m + j - 1]) / 5;
        }
    }
    for(i = 0; i < n; i++){
        double* c = a + i * m;
        for (j = 0; j < m; j++){
            max_a = max_zn(max_a, fabs(c[j]));
        }
    }
    return max_a;
}

double solve3(double* a, double* x, double* b, int n, int m){
    double sum = 0;
    int i, j;
    for (i = 0; i < n; i++){
        double sum_m = 0;
        double* astr = a + m * i;
        for (j = 0; j < m; j++){
            sum_m += astr[j] * x[j];
        }
        sum += fabs(sum_m - b[i]);
    }
    return sum;
}

double solve4(double* a, double* x, double* b, int n, int m){
    double max_a = 0;
    int i, j;
    for (i = 0; i < n; i++){
        double sum = 0;
        double* astr = a + m * i;
        for (j = 0; j < m; j++){
            sum += astr[j] * x[j];
        }
        max_a = max_zn(max_a, fabs(sum - b[i]));
    }
    return max_a;
}

double solve5(double* a, double* b, int n, int m){
    double max_str = 0;
    int i, j, p;
    for(i = 0; i < n; i ++){
        double sum_str = 0;
        for (p = 0; p < n; p++){
            double sum = 0;
            double* astr = a + m * i;
            double* bstolb = b + p;
            for (j = 0; j < m; j ++){
                sum += astr[j] * bstolb[j * n];
            }
            sum_str += fabs(sum);
        }
        max_str = max_zn(sum_str, max_str);
    }
    return max_str;
}

double solve6(double* a, double* b, int n, int m){
    double max_st = 0;
    int i, j, st;
    for (st = 0; st < n; st++){
        double sum_st = 0;
        for(i = 0; i < n; i ++){
            double sum = 0;
            double* astr = a + m * i;
            double* bstolb = b + st;
            for (j = 0; j < m; j ++){
                sum += astr[j] * bstolb[j * n];
            }
            sum_st += fabs(sum);
        }
        max_st = max_zn(sum_st, max_st);
    }
    return max_st;
}