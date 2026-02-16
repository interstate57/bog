#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "AVL_tree.h"

int main(int argc, char* argv[]){
    char* name = 0;
    char* s = 0;
    int r = 0;
    io_status ret;
    int task;
    double t = 0;
    double t_all = 0;
    int res = 0;
    int res_all = 0;
    FILE* fp;
    if (!((argc == 4) && sscanf(argv[1], "%d", &r) == 1)){
        printf("Usage: %s r s filename\n", argv[0]);
        return 1;
    }
    s = argv[2];
    name = argv[3];
    if (!(fp = fopen(name, "r"))) return -1;
    avl_tree<student> *a = new avl_tree<student>;
    ret = a->read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        return 3;
    }while(0);
    a->print(r);
    printf("\n");
    const char * s_all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    task = 1;
    t_all = clock();
    res_all = a->solve1(s_all);
    t_all = (clock() - t_all) / CLOCKS_PER_SEC;
    t = clock();
    res = a->solve1(s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);
    printf("\n");
    task = 2;
    t_all = clock();
    res_all = a->solve2(s_all);
    t_all = (clock() - t_all) / CLOCKS_PER_SEC;
    t = clock();
    res = a->solve2(s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);
    printf("\n");
    task = 3;
    t_all = clock();
    res_all = a->solve3(s_all);
    t_all = (clock() - t_all) / CLOCKS_PER_SEC;
    t = clock();
    res = a->solve3(s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);
    printf("\n");
    task = 5;
    t_all = clock();
    res_all = a->solve5(s_all);
    t_all = (clock() - t_all) / CLOCKS_PER_SEC;
    t = clock();
    res = a->solve5(s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
    printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);
    delete a;
    return 0;
}