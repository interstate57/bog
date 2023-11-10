#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define EPS 1e-14
#include "array_io.h"
int solve8 (const char* name1, double* a, int n);
int max_suffix_prefix(double* a, int k);
int equal(double x, double y);
int main1(int argc, char* argv[]);
int main1(int argc, char* argv[]){
    int n = 0, p = 0, s = 0;
    char* name1;
    char* name2 = 0;
    int task = 8;
    double* a;
    double t;
    int res = 0;
    if (!((argc == 5 || argc == 6) && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1)){
        printf("Usage: %s name1 n p s [name2]\n", argv[0]);
        return 6;
    }
    name1 = argv[1];
    if (argc == 6 && s == 0) name2 = argv[5];
    a = (double*)malloc(n * sizeof(double));
    if (!a){
        printf("Not enough memory!\n");
        return 2;
    }
    if (name2){
        int res1 = read_array(a, n, name2);
        if (res1 != SUCCESS){
            switch (res1){
                case ERROR_OPEN: printf("Cannot open %s;\n", name2); break;
                case ERROR_READ: printf("Cannot read %s\n", name2); break;
                default: printf("Unknown Error %d in file %s;\n", res1, name2);
            }
            free(a);
            return 3;
        }
    }
    else init_array(a, n, s);
    print_array(a, n, p);
    t = clock();
    res = solve8(name1, a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    return SUCCESS;
}

int solve8 (const char* name1, double* a, int n){
    int ans = 0, k = 0, need_read = 1;
    double current = 0;
    FILE* fp;
    fp = fopen(name1, "r");
    if (!fp) return ERROR_OPEN;
    while (1){
        if (k == n){
            ans += 1;
            k -= max_suffix_prefix(a, k);
        }
        if (need_read){
            if (fscanf(fp, "%lf", &current) != 1){
                break;
            }
            need_read = 0;
        }
        if (!equal(current, a[k])){
            if (k == 0) {
                need_read = 1;
            }
            else {
                k -= max_suffix_prefix(a, k);
            }
        }
        else {
            k += 1;
            need_read = 1;
        }
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
int max_suffix_prefix(double* a, int k){
    for (int i = 1; i < k; i ++){
        int f = 1;
        for (int j = i; j < k; j ++){
            if (!equal(a[j], a[j-i])){
                f = 0;
                break;
            }
            else {
            }
        }
        if (f == 1){
            return i;
        }
    }
    return k;
}
