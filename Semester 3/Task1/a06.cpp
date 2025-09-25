#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "sortirovki.h"

int data::p = 0;

int main(int argc, char* argv[]){
    int n = 0, s = 0, diff = 0;
    char* name = 0;
    int p = 0;
    data* a = 0;
    io_status ret;
    data x;
    int task = 6;
    double t = 0;
    FILE* fpx;
    if (!(argc == 5 && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 &&\
     sscanf(argv[3], "%d", &s) == 1 && s >= 1 && s <= 4)){
        printf("Usage: %s m n p s filename\n", argv[0]);
        return 1;
    }
    else if (!(argc == 6 && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 &&\
     sscanf(argv[3], "%d", &s) == 1 && s == 0)){
        printf("Usage: %s m n p s filename\n", argv[0]);
        return 1;
    }
    if (argc == 6) name = argv[5];
    a = new data[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if (name){
        if (!(fpx = fopen(name, "r"))) return ERROR_OPEN;
        ret = read_array(a, n, name);
        do{
            switch(ret){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open file!\n"); break;
                case ERROR_READ: printf("Cannot read file!\n"); break;
            }
            delete[] a;
            return 3;
        }while(0);
    }
    else{
        init_array(a, n, s);
    }
    print_array(a, n, p);
    t = clock();
    sort6(a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    print_array(a, n, p);
    diff = difference(a, n);
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    delete[] a;
    return 0;
}
