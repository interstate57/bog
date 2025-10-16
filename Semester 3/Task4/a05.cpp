#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "solve.h"
#include "dop.h"

int main(int argc, char* argv[]){
    int res = 0;
    char* name = 0;
    int p = 0;
    io_status ret;
    int task = 5;
    double t = 0;
    FILE* fp;
    list_node* phead = nullptr;
    if (!((argc == 3) && sscanf(argv[1], "%d", &p) == 1)){
        printf("Usage: %s p filename\n", argv[0]);
        return 1;
    }
    name = argv[2];
    if (!(fp = fopen(name, "r"))) return -1;
    ret = read_list(&phead, fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        delete_list(phead);
        return 3;
    }while(0);
    print_list(phead, p);
    printf("\n");
    t = clock();
    res = solve5(phead);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete_list(phead);
    return 0;
}
