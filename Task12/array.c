#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vspom_functions.h"
int read_array(char** a, int n, const char* name){
    int i, j;
    char buf[LEN];
    FILE* fp;
    if (!(fp = fopen(name, "r")))
        return ERROR_OPEN;
    for (i = 0; i < n; i++){
        if (!fgets(buf, LEN, fp)){
            fclose(fp);
            free_array(a, i);
            return ERROR_READ;
        }
        for (j = 0; buf[j]; j++){
            if (buf[j] == '\n'){
                buf[j] = 0;
                break;
            }
        }
        a[i] = (char*)malloc((j + 1) * sizeof(char));
        if (!a[i]){
            fclose(fp);
            free_array(a, i);
            return ERROR_MEM;
        }
        strcpy_(a[i], buf);
    }
    return SUCCESS;
}
void free_array(char** a, int n){
    int i;
    for (i = 0; i < n; i++){
        free(a[i]);
        a[i] = 0;
    }
}
void print_array(char** a, int n, int max_print){
    int i;
    int m = (n > max_print ? max_print : n);
    for (i = 0; i < m; i++){
        if (a[i])
            printf("%s\n", a[i]);
    }
}