#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#define LEN 1234
int dop(char* s, char* a);
int solve8(char** a, int n, char* s);
int main(int argc, char* argv[]){
    int n = 0, m = 0;
    char* name = 0;
    char** a = 0;
    io_status ret;
    char* s = 0;
    int res = 0, task = 8;
    double t = 0;
    if (!(argc == 5 && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &m) == 1)){
        printf("Usage: %s n m name s\n", argv[0]);
    }
    name = argv[3];
    s = argv[4];
    a = (char**)malloc(n * sizeof(char*));
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    ret = read_array(a, n, name);
    do{
        switch(ret){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
            case ERROR_MEMORY: printf("Not enough memory!\n"); break;
        }
        free(a);
        return 3;
    }while(0);
    print_array(a, n, m);
    t = clock();
    res = solve8(a, n, s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("New array:\n");
    print_array(a, res, m);
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete_array(a, res);
    free(a);
    return 0;
}

int dop(char* s, char* a){
    int i;
    char a1[LEN];
    strcpy(a1, a);
    for (i = 0; a1[i]; i++){
        if (a1[i] >= 'A' && a1[i] <= 'Z') a1[i] += 'a' - 'A';
    }
    return (!(strstr(s, a1)) ? 0 : 1);
}

int solve8(char** a, int n, char* s){
    int vspom[n];
    int j, k, p;
    int i;
    for (i = 0; s[i]; i++){
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A';
    }
    i = 2;
    vspom[i - 2] = (dop(s, a[i - 1]) == 1 ? 1 : 0);
    vspom[i - 1] = ((dop(s, a[i - 2]) == 1) || (dop(s, a[i]) == 1) ? 1 : 0);
    for (i = 3; i < n; i++){
        vspom[i - 1] = ((dop(s, a[i - 2]) == 1) || (dop(s, a[i]) == 1) ? 1 : 0);
    }
    vspom[i - 1] = (dop(s, a[i - 2]) == 1 ? 1 : 0);
    for (p = 0, j = 0; p < n; p++){
        if(vspom[p] == 0){
            if (p != j){
                free(a[j]);
                a[j] = a[p];
                a[p] = 0;
            }
            j += 1;
        }
    }
    for (k = j; k < n; k++) free(a[k]);
    return j;
}

