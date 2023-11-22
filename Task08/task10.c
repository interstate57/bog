#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array_io.h"
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

int main(void)
{
    int n = 14;
    double * a = (double *) malloc (n * sizeof(double));
    a[0] = 8;
    a[1] = 51;
    a[2] = 95;
    a[3] = 27;
    a[4] = 41;
    a[5] = 8;
    a[6] = 96;
    a[7] = 1;
    a[8] = 10;
    a[9] = 9;
    a[10] = 1;
    a[11] = 1;
    a[12] = 0;
    a[13] = 55;
    solve10(a, n);
    print_array(a, n, n);
    return 0;
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