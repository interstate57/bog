#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "solve.h"


int main(int argc, char* argv[]){
    int n = 0, s = 0;
    int p = 0;
    char* name = 0;
    char* namex = 0;
    int xv = 0;
    student* a;
    io_status ret;
    int res = 0, task = 9;
    double t = 0;
    if (!((argc == 6 || argc == 7) && sscanf(argv[2], "%d", &xv) == 1 && sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 &&\
        sscanf(argv[5], "%d", &s) == 1)){
        printf("Usage: %s x_name x_value n p s filename\n", argv[0]);
        return 1;
    }
    if (argc == 7) name = argv[6];
    namex = argv[1];
    student x(namex, xv);
    a = new student[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if (name){
        if (s != 0){
            printf("Usage: %s x_name x_value n p s filename\n", argv[0]);
            delete[] a;
            return 1;
        }
        ret = read_array(a, n, name);
        do{
            switch(ret){
                case io_status::success: continue;
                case io_status::wrong_file: printf("Cannot open file!\n"); break;
                case io_status::format: printf("Cannot read file!\n"); break;
                case io_status::eof: printf("Cannot read file!\n"); break;
                case io_status::memory: printf("Cannot allocate memory!\n"); break;
            }
            delete[] a;
            return 3;
        }while(0);
    }
    else{
        if (s < 1 || s > 4){
            printf("Usage: %s x_name x_value n p s filename\n", argv[0]);
            delete[] a;
            return 1;
        }
        init_array(a, n, s);
    }
    print_array(a, n, p);
    printf("\n");
    t = clock();
    res = solve9(a, n, x);
    t = (clock() - t) / CLOCKS_PER_SEC;
    print_array(a, n, res);
    printf ("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete[] a;
    return 0;
}
