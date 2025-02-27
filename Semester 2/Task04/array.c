#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "sravneniya.h"
#define LEN 1234

io_status read_array(char** a, int n, const char* name){
    char buf[LEN] = {0};
    FILE* fp = 0;
    int i, j;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    for (i = 0; i < n; i++){
        if (!fgets(buf, LEN, fp)){
            fclose(fp);
            delete_array(a, i);
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
            delete_array(a, i);
            return ERROR_MEMORY;
        }
        strcpy(a[i], buf);
    }
    fclose(fp);
    return SUCCESS;
}

void delete_array(char** a, int n){
    int i;
    for (i = 0; i < n; i++) free(a[i]);
}

void print_array(char** a, int n, int m){
    int e = (n > m ? m : n);
    int i;
    for (i = 0; i < e; i++){
        printf("%s\n", a[i]);
    }
}

int difference (char** a, int n, int (*cmp)(const char*, const char*)){
    int i;
    int ans = 0;
    for (i = 1; i < n; i ++){
        if (cmp(a[i], a[i - 1]) < 0) ans += 1;
    }
    return ans;
}