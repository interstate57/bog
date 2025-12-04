#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "b_tree.h"

int main(int argc, char* argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    int task = 1;
    double t = 0;
    int res = 0;
    int k = 0, m = 0;
    FILE* fp;
    if (!((argc == 5) && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%d", &r) == 1 && sscanf(argv[3], "%d", &k) == 1)){
        printf("Usage: %s m r k filename\n", argv[0]);
        return 1;
    }
    name = argv[4];
    if (!(fp = fopen(name, "r"))) return -1;
    b_tree<student> *a = new b_tree<student>(m);
    ret = a->read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
            case io_status::create: printf("Cannot read file!\n"); break;
        }
        return 3;
    }while(0);
    a->print(r);
    task = 1;
    t = clock();
    res = a->solve1(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, k, res, t);
    task = 2;
    t = clock();
    res = a->solve2(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, k, res, t);
    task = 3;
    t = clock();
    res = a->solve3(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, k, res, t);
    task = 5;
    t = clock();
    res = a->solve5(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, k, res, t);
    /*task = 6;
    t = clock();
    res = a->solve6(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, k, res, t);*/
    delete a;
    return 0;
}