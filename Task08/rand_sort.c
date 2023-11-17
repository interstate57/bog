#include <stdio.h>
#include <stdlib.h>

void solve4 (double* a, int n);
int solve5 (double* a, int n);
int solve6 (double* a, int n);
int solve7 (double* a, int n);
//int solve8 (double* a, int n);
int solve9 (double* a, int n);
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

int main(void)
{
    int ATTEMPTS = 100;
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

        solve4(a, n);
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
