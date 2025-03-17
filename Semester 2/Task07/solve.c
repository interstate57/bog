#include <math.h>
#include <stdio.h>
#include "solve.h"
#include "array_io.h"


void udalenie_only_j(double* a, int m, int n, int j_ans){
    int i, j;
    int d = 0, k = 0;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if (j == j_ans){
                d += 1;
            }
            else if (d == 0){
                k += 1;
                continue;
            } 
            else{
                if (k != i * n + j){
                    a[k] = a[i * n + j];
                }
                k += 1;
            }
        }
    }
}

void udalenie_i_and_j(double* a, int m, int n, int i_ans, int j_ans){
    int i, j;
    int d = 0, k = 0;
    for (i = 0; i < m; i++){
        if (i == i_ans){
            d += 1;
            continue;
        }
        for (j = 0; j < n; j++){
            if (j == j_ans){
                d += 1;
            }
            else if (d == 0){
                k += 1;
                continue;
            } 
            else{
                if (k != i * n + j){
                    a[k] = a[i * n + j];
                }
                k += 1;
            }
        }
    }
}

int solve1(double* a, int m, int n){
    int i, j;
    int j_ans = 0;
    double min_ = 1e308;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if (a[i * n + j] < min_){
                min_ = a[i * n + j];
                j_ans = j;
            }
        }
    }
    udalenie_only_j(a, m, n, j_ans);
    return j_ans + 1;
}

int solve2(double* a, int m, int n){
    int i, j;
    int j_ans = 0, i_ans = 0;
    double min_ = 1e308;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if (a[i * n + j] < min_){
                min_ = a[i * n + j];
                j_ans = j;
                i_ans = i;
            }
        }
    }
    udalenie_i_and_j(a, m, n, i_ans, j_ans);
    return i_ans * n + j_ans;
}

int solve3(double* a, int m, int n){
    int i, j;
    int j_ans = 0;
    double min_ = 1e308;
    for (j = 0; j < n; j++){
        double* b = a + j;
        double s = 0;
        for (i = 0; i < m; i++){
            s += fabs(b[i * n]);
        }
        if (s < min_){
            min_ = s;
            j_ans = j;
        }
    }
    udalenie_only_j(a, m, n, j_ans);
    return j_ans + 1;
}


int solve4(double* a, int m, int n){
    int i, j, kn, km;
    int j_ans = 0, i_ans = 0;
    double min_ = 1e308;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            double sum = 0;
            double* b = a + i * n;
            double* c = a + j;
            for (kn = 0; kn < n; kn++){
                sum += fabs(b[kn]);
            }
            for (km = 0; km < m; km++){
                sum += fabs(c[km * n]);
            }
            if (sum < min_){
                min_ = sum;
                j_ans = j;
                i_ans = i;
            }
        }
    }
    udalenie_i_and_j(a, m, n, i_ans, j_ans);
    return i_ans * n + j_ans;
}


int solve5(double* a, int m, int n){
    int i, j;
    int j_ans = 0;
    double max_ = -1e308;
    for (j = 0; j < n; j++){
        double* b = a + j;
        double s = 0;
        for (i = 0; i < m; i++){
            if (i == j) continue;
            s += fabs(b[i * n]);
        }
        if (s > max_){
            max_ = s;
            j_ans = j;
        }
    }
    udalenie_only_j(a, m, n, j_ans);
    return j_ans + 1;
}

int solve6(double* a, int m, int n){
    int i, j;
    int j_ans = 0;
    double max_ = -1e308;
    int new_n = (n < m ? n : m);
    for (j = 0; j < new_n; j++){
        double* b = a + j;
        double s = 0;
        double ajj = a[j * n + j];
        for (i = 0; i < m; i++){
            if (i == j) continue;
            s += fabs(b[i * n] - ajj);
        }
        if (s > max_){
            max_ = s;
            j_ans = j;
        }
    }
    udalenie_only_j(a, m, n, j_ans);
    return j_ans + 1;
}

int solve7(double* a, int m, int n){
    int i, j, k;
    int j_ans = 0;
    double min_ = 1e308;
    for (j = 0; j < n; j++){
        double* b = a + j;
        double s = 0;
        double sr_zn = 0;
        for(k = 0; k < m; k++){
            sr_zn += b[k * n];
        }
        //printf("%lf\n", sr_zn);
        sr_zn = sr_zn / m;
        for (i = 0; i < m; i++){
            s += pow(b[i * n] - sr_zn, 2);
        }
        //printf("%d : %lf\n", j_ans, s);
        if (s < min_){
            min_ = s;
            j_ans = j;
        }
    }
    udalenie_only_j(a, m, n, j_ans);
    return j_ans + 1;
}

int solve8(double* a, int m, int n){
    int i, j, kn, km;
    int j_ans = 0, i_ans = 0;
    double max_ = -1e308;
    for (i = 0; i < m; i++){
        double* b = a + i * n;
        for (j = 0; j < n; j++){
            double sum = 0;
            double* c = a + j;
            for (kn = 0; kn < n; kn++){
                if (kn == j) continue;
                sum += fabs(b[kn]);
            }
            for (km = 0; km < m; km++){
                if (km == i) continue;
                sum += fabs(c[km * n]);
            }
            if (sum > max_){
                max_ = sum;
                j_ans = j;
                i_ans = i;
            }
        }
    }
    udalenie_i_and_j(a, m, n, i_ans, j_ans);
    return i_ans * n + j_ans;
}

int solve9(double* a, int m, int n){
    int i, j, kn, km;
    int j_ans = 0, i_ans = 0;
    double max_ = -1e308;
    for (i = 0; i < m; i++){
        double* b = a + i * n;
        for (j = 0; j < n; j++){
            double sum = 0;
            double aij = a[i * n + j];
            double* c = a + j;
            for (kn = 0; kn < n; kn++){
                if (kn == j) continue;
                sum += fabs(b[kn] - aij);
            }
            for (km = 0; km < m; km++){
                if (km == i) continue;
                sum += fabs(c[km * n] - aij);
            }
            if (sum > max_){
                max_ = sum;
                j_ans = j;
                i_ans = i;
            }
        }
    }
    udalenie_i_and_j(a, m, n, i_ans, j_ans);
    return i_ans * n + j_ans;
}

int solve10(double* a, int m, int n){
    int i, j, kn, km, ln, lm;
    int j_ans = 0, i_ans = 0;
    double min_ = 1e308;
    for (i = 0; i < m; i++){
        double* b = a + i * n;
        double sr_zn_i = 0, sum_str = 0;
        for(ln = 0; ln < n; ln++){
            sr_zn_i += b[ln];
        }
        sr_zn_i = sr_zn_i / n;
        for(kn = 0; kn < n; kn++){
            sum_str += pow(b[kn] - sr_zn_i, 2);
        }
        for (j = 0; j < n; j++){
            double sr_zn_j = 0, sum_stol = 0;
            double* c = a + j;
            for(lm = 0; lm < m; lm++){
                sr_zn_j += c[lm * n];
            }
            sr_zn_j = sr_zn_j / m;
            for(km = 0; km < m; km++){
                sum_stol += pow(c[km * n] - sr_zn_i, 2);
            }
            if (sum_stol + sum_str < min_){
                min_ = sum_stol + sum_str;
                j_ans = j;
                i_ans = i;
            }
        }
    }
    udalenie_i_and_j(a, m, n, i_ans, j_ans);
    return i_ans * n + j_ans;
}