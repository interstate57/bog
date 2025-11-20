#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

int main(int argc, char* argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    int task = 1;
    double t = 0;
    int res = 0;
    int k;
    FILE* fp;
    tree a;
    if (!((argc == 4) && sscanf(argv[1], "%d", &r) == 1 && sscanf(argv[3], "%d", &k) == 1)){
        printf("Usage: %s r filename k\n", argv[0]);
        return 1;
    }
    name = argv[2];
    if (!(fp = fopen(name, "r"))) return -1;
    ret = a.read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        return 3;
    }while(0);
    a.print(r);
    printf("\n");
    t = clock();
    res = a.a1(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);
    task = 2;
    printf("\n");
    t = clock();
    res = a.a2(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    task = 3;
    printf("\n");
    t = clock();
    res = a.a3(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    /*task = 4;
    printf("\n");
    t = clock();
    res = a.a4(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);*/
    task = 5;
    printf("\n");
    t = clock();
    res = a.a5(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    task = 6;
    printf("\n");
    t = clock();
    res = a.a6(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    printf("\n");
    a.print(r);
    return 0;
}