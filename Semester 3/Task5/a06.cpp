#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"

int main(int argc, char* argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    int task = 6, k = 0;
    double t = 0;
    unsigned int len1 = 0, len2 = 0;
    FILE* fp;
    list2 a;
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
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        a.delete_list();
        return 3;
    }while(0);
    len1 = a.get_length();
    a.print(r);
    printf("\n");
    t = clock();
    a.solve6(k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    len2 = a.get_length();
    a.print(r);
    printf("\n");
    printf ("%s : Task = %d Len Old = %u Len New = %u Elapsed = %.2f\n", argv[0], task, len1, len2, t);
    a.delete_list();
    return 0;
}