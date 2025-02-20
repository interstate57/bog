#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "io_status.h"
#include "array.h"
int solve4(char** a, int n, char* s);
int main(int argc, char argv[]){
    int n = 0, m = 0;
    char* name = 0;
    char** a = 0;
    io_status ret;
    char* s = 0;
    int res = 0, task = 4;
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
    res = solve4(a, n, s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("New array:\n");
    print_array(a, res, m);
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete_array(a, res);
    free(a);
    return 0;
}

int solve4(char** a, int n, char* s){
    int i, j, k;
    int flag = 0;
    size_t lens = strlen(s);
    for (i = 0, j = 0; i < n; i++){
        size_t lenai = strlen(a[i]);
        if (lens >= lenai && flag == 0){
            flag = 1;
        }
        else if (lens >= lenai && flag == 1){
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
                j += 1;
            }
        }
        else{
            flag = 0;
        }
            
    }
    for (k = j; k < n; k++) free(a[k]);
    return j;
}