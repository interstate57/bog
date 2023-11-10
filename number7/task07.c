#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define EPS 1e-14
#include "array_io.h"
int equal(double x, double y);
int solve7 (const char* name1, double* a, int n);
int maybe_insert(double* a, int current_size, int n, double current_number);
int main(int argc, char* argv[]){
    int n = 0, p = 0;
    char* name1;
    int task = 7;
    double* a;
    double t;
    int res = 0;
    if (!((argc == 4) && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1)){
        printf("Usage: %s name1 n p\n", argv[0]);
    }
    name1 = argv[3];
    a = (double*)malloc(n * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    t = clock();
    res = solve7(name1, a, n);
    if (res < SUCCESS){
        switch (res){
            case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
            case ERROR_READ: printf("Cannot read %s;\n", name1); break;
            default: printf("Unknown Error %d in file %s;\n", res, name1);
        }
        free(a);
        return 4;
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, res, p); 
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",argv[0], task, res, t);
    free(a);
    return SUCCESS;
}
int solve7 (const char* name1, double* a, int n){
    int ans = 0, f = 0;
    double prev = 0, seredina = 0, current_number = 0;
    FILE* fp;
    if (n == 0){
        return 0;
    }
    fp = fopen(name1, "r");
    if (!fp) return ERROR_OPEN;
    while (fscanf(fp, "%lf", &current_number) == 1){
        if (f == 2){
            if (seredina > current_number && seredina > prev){
                ans = maybe_insert(a, ans, n, seredina);
            }
        }
        else if (f == 1){
            f += 1;
            seredina = current_number;
            continue;
        }
        else{
            prev = current_number;
            f += 1;
            continue;
        }
        prev = seredina;
        seredina = current_number;
    }
    if (!feof(fp)){
        fclose(fp);
        return ERROR_READ;
    }
    fclose(fp);
    return ans;
}
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}
int maybe_insert(double* a, int current_size, int n, double current_number){
    int k = -1;
    for (int i = 0; i < n; i ++){
        if (current_number > a[i]){
            k = i;
            break;
        }
        if (equal(current_number, a[i])) 
            return current_size;
    }
    if (k == -1){
        a[current_size] = current_number;
        current_size += 1;
        return current_size;
    }
    if (current_size == n){
        double per = 0;
        for (int i = k; i < current_size; i ++){
            per = a[i];
            a[i] = current_number;
            current_number = per;
        }
        return current_size;
    }
    else{
        double per = 0;
        if (current_size != 0){
            for (int i = k; i < current_size + 1; i ++){
                per = a[i];
                a[i] = current_number;
                current_number = per;
            }
        }
        else{
            a[0] = current_number;
        }
        current_size += 1;
        return current_size;
    }
}
