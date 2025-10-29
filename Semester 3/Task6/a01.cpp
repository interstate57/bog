#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int main(int argc, char* argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    int task = 1;
    double t = 0;
    int diff = 0;
    FILE* fp;
    list a;
    if (!((argc == 3) && sscanf(argv[1], "%d", &r) == 1)){
        printf("Usage: %s r filename\n", argv[0]);
        return 1;
    }
    name = argv[2];
    if (!(fp = fopen(name, "r"))) return -1;
    ret = a.read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        a.delete_list();
        return 3;
    }while(0);
    a.print(r);
    printf("\n");
    t = clock();
    a.sort1();
    t = (clock() - t) / CLOCKS_PER_SEC;
    a.print(r);
    printf("\n");
    diff = a.diff();
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    a.delete_list();
    return 0;
}