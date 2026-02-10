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
    int task = 1;
    double t = 0;
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
    a->print();
    return 0;
}