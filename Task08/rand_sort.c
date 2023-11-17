#include <stdio.h>
#include <stdlib.h>

void solve4 (double* a, int n);
void solve5 (double* a, int n);
void solve6 (double* a, int n);
void solve7 (double* a, int n);
void solve8 (double* a, int n);
void solve9 (double* a, int n);

int binpoisk (double x, double* a, int n);
int polov_sort (double x, double* a, int n);

int difference(double* a, int n);
void print_array (double* a, int n, int p);
double randfrom(double min, double max);

double randfrom(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void solve4 (double* a, int n){
    int i, j;
    double per = 0;
    for (i = 0; i < n; i ++){
        for (j = 0; j < n - 1 - i; j ++){
            if (a[j] > a[j + 1]){
                per = a[j];
                a[j] = a[j + 1];
                a[j + 1] = per;
            }
        }
    }
}

void solve5 (double* a, int n){
    int i, j;
    double per = 0;
    for (i = 0; i < n - 1; i ++){
        int mini = n;
        double minch = 1e304;
        for (j = i; j < n; j ++){
            if (a[j] < minch){
                mini = j;
                minch = a[j];
            }
        }
        per = a[i];
        a[i] = a[mini];
        a[mini] = per;

    }
}

void solve6 (double* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        double vr = 0;
        for (j = 0; j < i ; j ++){
            if (a[j] > a[i]){
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

void solve7 (double* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1);
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

int binpoisk (double x, double* a, int n){
    int inach = 0, ikon = n, s = 0;
    if (x > a[n - 1]){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (a[s] < x){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}

void solve9 (double* a, int n){
    int i = 0, j = n - 1; 
    double sr = 0;
    //printf("\n");
    //print_array(a, n, n);

    if (n <= 1){
        return;
    }
    sr = a[(i + j) / 2];
    i = polov_sort(sr, a, n);
    if (i == 0) {
        int temp = a[i];
        a[i] = a[n/2];
        a[n/2] = temp;
    }

    //printf("border element: %lf;    border: i = %d;   a[i] = %lf\n", sr, i, a[i]);
    solve9(a + 0, i);
    solve9(a + i + 1, n - i - 1);
    //printf("after sort:\n");
    //print_array(a, n, n);
}
int polov_sort (double x, double* a, int n){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    double vr = 0;
    while (i <= j){
        while (i < n){
            if (a[i] >= x){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (a[j] < x){
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
        double *a_copy = (double *) malloc (n * sizeof(double));

        for (int j = 0; j < n; j++) {
            a[j] = randfrom(-INT_MAX, INT_MAX);
            a_copy[j] = a[j];
        }

        solve9(a, n);
        err = difference(a, n);
        if (err > 0) {
            printf("ERROR\n");
            print_array(a_copy, n, n);
            break;
        }
        else {
            printf("OK\n");
        }
    }
}
