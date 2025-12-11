#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rb_tree.h"

int main(int argc, char* argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    /*int task = 1;
    double t = 0;
    int res = 0;*/
    int k = 0;
    FILE* fp;
    if (!((argc == 4) && sscanf(argv[1], "%d", &r) == 1 && sscanf(argv[2], "%d", &k) == 1)){
        printf("Usage: %s r k filename\n", argv[0]);
        return 1;
    }
    name = argv[3];
    if (!(fp = fopen(name, "r"))) return -1;
    rb_tree<student> a;
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
    return 0;
}