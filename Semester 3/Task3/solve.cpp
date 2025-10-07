#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "solve.h"

int solve1(student* a, int n){
    int j = 1;
    if (n == 0) return 0;
    for (int i = 1; i < n; i++){
        if (a[i] < a[j - 1]){
            delete (a+i);
            continue;
        }
        else{
            if (i != j){
                a[j] = (student&&)a[i];
            }
            j++;
        }
    }
    return j;
}

io_status read_array(student* a, int n, const char* name){
    FILE* fp = 0;
    io_status res;
    int i;
    if (!(fp = fopen(name, "r"))) return io_status::wrong_file;
    for (i = 0; i < n; i++){
        res = a[i].read(fp);
        if (res != io_status::success) return res;
    }
    fclose(fp);
    return io_status::success;
}


void print_array(student* a, int n, int p){
    int min = (n < p ? n : p);
    for (int i = 0; i < min; i++){
        a[i].print();
    }
}

void init_array(student* a, int n, int s){
    for (int i = 0; i < n; i++){
        a[i].init_f(f(s, n, i + 1));
    }
}

int f(int s, int n, int i){
    int res = 0;
    switch(s){
            case 1: res = i; break;
            case 2: res = n - i; break;
            case 3: res = i / 2; break;
            case 4: res = n - i / 2; break;
        }
    return res;
}   