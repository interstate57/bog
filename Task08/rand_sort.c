#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void solve4 (double* a, int n, int (*cmp) (double, double));
void solve5 (double* a, int n, int (*cmp) (double, double));
void solve6 (double* a, int n, int (*cmp) (double, double));
void solve7 (double* a, int n, int (*cmp) (double, double));
void solve8 (double* a, double * b, int n, int (*cmp) (double, double));
void solve9 (double* a, int n, int (*cmp) (double, double));
void solve10 (double* a, int n, int (*cmp) (double, double));

int binpoisk (double x, double* a, int n, int (*cmp) (double, double));
void merge (double* a, double* b, int n, int m, double* c, int (*cmp)(double, double));
int polov_sort (double x, double* a, int n, int (*cmp) (double, double));

void heapify(double *a, int n, int (*cmp)(double, double));
void perestroika_snizu(double *a, int n, int (*cmp)(double, double));
void perestroika_sverhu(double *a, int n, int (*cmp)(double, double));
int parent(int a);
int left_son(int a);
int right_son(int a);

int difference(double* a, int n, int (*cmp) (double, double));
void print_array (double* a, int n, int p);
double randfrom(double min, double max);
int parent(int a);
void perestroika_snizu(double *a, int n);
void perestroika_sverhu(double *a, int n);
void solve10(double *a, int n);
void heapify(double *a, int n);
int left_son(int i);
int right_son(int i);
void solve10(double *a, int n){
    double per = 0;
    heapify(a, n);
    for (int i = 1; i < n; i ++){
        per = a[0];
        a[0] = a[n - i];
        a[n - i] = per;
        perestroika_sverhu(a, n - i);
    }
}
// incorrect element is the last element
void perestroika_snizu(double *a, int n){
    double per = 0;
    int wrong = n - 1;
    while (wrong != 0){
        if (a[wrong] <= a[parent(wrong)]){
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
int difference (double* a, int n){
    int i;
    int ans = 0;
    for (i = 1; i < n; i ++){
        if (a[i] < a[i - 1]) ans += 1;
    }
    return ans;
}
void print_array (double* a, int n, int p){
    int i;
    if (n == 0 || p == 0){
      printf("Empty array\n");
      return;
    }
    if (p <= n){
        for (i = 0; i < p; i ++){
            printf("%lf\n", a[i]);
        }
    }
    else{
        for (i = 0; i < n; i ++){
            printf("%lf\n", a[i]);
        }
    }
}
void perestroika_sverhu(double *a, int n){
    double per = 0;
    int wrong = 0;
    while (right_son(wrong) < n){
        if (a[wrong] >= a[left_son(wrong)] && a[wrong] >= a[right_son(wrong)]){
            break;
        }
        else{
            if (a[left_son(wrong)] >= a[right_son(wrong)]){
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
    if (left_son(wrong) == n - 1 && a[wrong] < a[left_son(wrong)]){
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
void heapify(double *a, int n){
    for (int i = 1; i < n; i ++){
        perestroika_snizu(a, i + 1);
    }
}
double randfrom(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void solve4 (double* a, int n, int (*cmp)(double, double)){
    int i, j;
    double per = 0;
    for (i = 0; i < n; i ++){
        for (j = 0; j < n - 1 - i; j ++){
            if (cmp(a[j + 1], a[j]) > 0){
                per = a[j];
                a[j] = a[j + 1];
                a[j + 1] = per;
            }
        }
    }
}

void solve5 (double* a, int n, int (*cmp)(double, double)){
    int i, j;
    double per = 0;
    for (i = 0; i < n - 1; i ++){
        int mini = i;
        double minch = a[i];
        for (j = i; j < n; j ++){
            if (cmp(minch, a[j]) < 0){
                mini = j;
                minch = a[j];
            }
        }
        per = a[i];
        a[i] = a[mini];
        a[mini] = per;
    }
}

void solve6 (double* a, int n, int (*cmp)(double, double)){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        double vr = 0;
        for (j = 0; j < i ; j ++){
            if (cmp(a[i], a[j]) > 0){
                nuzh = j;
                break;
            }
        }
        if (nuzh != -1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}

void solve7 (double* a, int n, int (*cmp)(double, double)){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1, cmp);
        double vr = 0;
        if (nuzh != i + 1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}
int binpoisk (double x, double* a, int n, int (*cmp)(double, double)){
    int inach = 0, ikon = n, s = 0;
    if (cmp(a[n - 1], x) > 0){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (cmp(a[s], x) > 0){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
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
void solve9 (double* a, int n, int (*cmp)(double, double)){
    int i = 0, sr = 0; 
    double per = 0;
    while (n > 1){
        sr = (n - 1) / 2;
        i = polov_sort(a[sr], a, n, cmp);
        if (i > n - i){
            solve9(a + i, n - i, cmp);
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
                solve9(a + 0, i, cmp);
                a += i;
                n -= i;
                continue;
            }
        }
    }
}

int polov_sort (double x, double* a, int n, int (*cmp)(double, double)){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    double vr = 0;
    while (i <= j){
        while (i < n){
            if (cmp(x, a[i]) >= 0){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (cmp(a[j], x) > 0){
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

int main(void)
{
    int ATTEMPTS = 10000;
    int N_MAX = 100;
    int INT_MAX = 100;

    int err;

    //srand(time(NULL));

    for (int i = 0; i < ATTEMPTS; i++) {
        int n = rand() % N_MAX + 1;
        double *a = (double *) malloc (n * sizeof(double));
        double *aa = (double *) malloc (n * sizeof(double));
        double *a_copy = (double *) malloc (n * sizeof(double));

        int (* cmp) (double, double);
        void (* taskXX) (double *, int, int (*) (double, double));

        for (int j = 0; j < n; j++) {
            a[j] = randfrom(-INT_MAX, INT_MAX);
            aa[j] = a[j];
            a_copy[j] = a[j];
        }

        for (int task = 4; task < 11; task++)
        {
            switch(task) {
                case 4: taskXX = solve4; break;
                case 5: taskXX = solve5; break;
                case 6: taskXX = solve6; break;
                case 7: taskXX = solve7; break;
                case 9: taskXX = solve9; break;
                case 10: taskXX = solve10; break;
            }
            for (int i = 1; i < 3; i++) {
                if (i == 1)
                    cmp = vosrastanie;
                else
                    cmp = ubuvanie;

                taskXX(a, n, cmp);
                err = difference(a, n, cmp);
                if (err > 0) {
                    printf("ERROR in task %d, order: %d\n", task, i);
                    print_array(a_copy, n, n);
                    break;
                }
                else {
                    printf("OK\n");
                }
            }
        }
    }
}
void solve8 (double* a, double* b, int n){
    int i;
    int j = 1;
    double* a_orig = a;
    double* c;
    while (j < n){
        for (i = 0; i < n; i += 2 * j){
            if (i + 2 * j >= n){
                if (i + j >= n){
                    merge(a + i, a, n - i, 0, b + i);
                }
                else{
                    merge(a + i, a + i + j, j, n - i - j, b + i);
                }
                
            }
            else{
                merge(a + i, a + i + j, j, j, b + i);
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
void merge (double* a, double* b, int n, int m, double* c){
    int i = 0, j = 0, k = 0;
    while (i != n && j != m){
        if (a[i] < b[j]){
            c[k] = a[i];
            i += 1;
            k += 1;
        }
        else if (a[i] > b[j]){
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
