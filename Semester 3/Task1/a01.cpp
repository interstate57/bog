#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "sortirovki.h"

int data::p;

int main(int argc, char* argv[]){
    int n = 0, s = 0;
    int p = 0;
    char* name = 0;
    char* namex = 0;
    data* a;
    io_status ret, retx;
    data x;
    int res = 0, task = 1;
    double t = 0;
    FILE* fpx;
    if (argc == 5 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1 &&\
        (s < 1 || s > 4)){
        printf("Usage: %s x n p s filename\n", argv[0]);
        return 1;
    }
    else if (argc == 6 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1 &&\
        s != 0){
        printf("Usage: %s x n p s filename\n", argv[0]);
        return 1;
    }
    else if (argc != 5 && argc != 6){
        printf("Usage: %s x n p s filename\n", argv[0]);
        return 1;
    }
    data::set_p(p);
    if (argc == 6) name = argv[5];
    namex = argv[1];
    if (!(fpx = fopen(namex, "r"))) return ERROR_OPEN;
    retx = x.read(fpx);
    do{
        switch(retx){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
        }
        return 3;
    }while(0);
    a = new data[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if (name){
        ret = read_array(a, n, name);
        do{
            switch(ret){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("1Cannot open file!\n"); break;
                case ERROR_READ: printf("Cannot read file!\n"); break;
            }
            delete[] a;
            return 3;
        }while(0);
    }
    else{
        init_array(a, n, s);
    }
    for (int i = 0; i < n - 1; i ++){
        if (a[i + 1] < a[i]){
            printf("Array a is not an increasing one\n");
            delete[] a;
            return 5;
        }
    }
    print_array(a, n, p);
    printf("\n");
    t = clock();
    res = sort1(x, a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete[] a;
    return 0;
}
