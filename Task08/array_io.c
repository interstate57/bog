#include <stdio.h>
#include "array_io.h"
int read_array (double* a, int n, const char* name){
    FILE* fp;
    int i;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    for (i = 0; i < n; i++){
        if (fscanf(fp, "%lf", a + i) != 1){
            fclose(fp);
            return ERROR_READ;
        }
    }
    fclose(fp);
    return SUCCESS;
}
double f_i (int s, int n, int i){
    switch (s){
        case 1: return i;
        case 2: return n - i;
        case 3: return i / 2.0;
        case 4: return n - i / 2.0;
        case 5: return i * 2.0;
        case 6: return n - i * 2.0;
        default: printf("I know nothing, my friend!");
    }
    return 2;
}
void init_array (double* a, int n, int s){
    int i;
    for (i = 1; i < n + 1; i ++){
        a[i - 1] = f_i(s, n, i);
    }
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
int difference (double* a, int n, int (*cmp)(double, double)){
    int i;
    int ans = 0;
    for (i = 1; i < n; i ++){
        if (cmp(a[i], a[i - 1]) > 0) ans += 1;
    }
    return ans;
}
