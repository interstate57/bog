#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "sortirovki.h"

int main(int argc, char* argv[]){
    int n = 0, s = 0, diff = 0;
    char* name = 0;
    int p = 0;
    student* a;
    student* b;
    io_status ret;
    student x;
    int task = 8;
    double t = 0;
    if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 &&\
     sscanf(argv[3], "%d", &s) == 1)){
        printf("Usage: %s n p s filename\n", argv[0]);
        return 1;
    }
    if (argc == 5) name = argv[4];
    a = new student[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if (name){
        if (s != 0){
            printf("Usage: %s n p s filename\n", argv[0]);
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
            printf("Usage: %s n p s filename\n", argv[0]);
            delete[] a;
            return 1;
        }
        init_array(a, n, s);
    }
    b = new student[n];
    if (!b){
        printf("Cannot allocate memory!\n");
        delete[] a;
        return 2;
    }
    print_array(a, n, p);
    printf("\n");
    t = clock();
    sort8(a, b, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    print_array(a, n, p);
    diff = difference(a, n);
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    delete[] a;
    delete[] b;
    return 0;
}
