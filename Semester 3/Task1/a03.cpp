#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "sortirovki.h"

int data::p = 0;

int main(int argc, char* argv[]){
    int n = 0, s = 0, m = 0;
    int p = 0;
    char* name = 0;
    data* a = 0;
    io_status ret;
    data x;
    int task = 3, res = 0;
    double t = 0;
    if (!((argc == 5 || argc == 6) && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 &&\
     sscanf(argv[4], "%d", &s) == 1)){
        printf("Usage: %s m n p s filename\n", argv[0]);
        return 1;
    }
    if (argc == 6) name = argv[5];
    data::set_p(p);
    a = new data[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if (name){
        if (s != 0){
            printf("Usage: %s m n p s filename\n", argv[0]);
            delete[] a;
            return 1;
        }
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
        if (s < 1 || s > 4){
            printf("Usage: %s m n p s filename\n", argv[0]);
            delete[] a;
            return 1;
        }
        init_array(a, n, s);
    }
    print_array(a, n, p);
    printf("\n");
    t = clock();
    res = sort3(a, n, m);
    t = (clock() - t) / CLOCKS_PER_SEC;
    print_array(a, n, p);
    printf ("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete[] a;
    return 0;
}
