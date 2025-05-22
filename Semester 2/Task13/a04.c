#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "solve.h"
int main(int argc, char* argv[]){
    int p = 0, res = 0,task = 4;
    char* name = 0;
    io_status ret;
    double t = 0;
    node* head = 0;
    if (!(argc == 3 && sscanf(argv[1], "%d", &p) == 1)){
        printf("Usage: %s p filename\n", argv[0]);
        return 1;
    }
    name = argv[2];
    ret = read_list(&head, name);
    do{
        switch(ret){
            case SUCCESS: continue;
            case ERROR_OPEN: printf("Cannot open file!\n"); break;
            case ERROR_READ: printf("Cannot read file!\n"); break;
            case ERROR_MEMORY: printf("Not enough memory!\n"); break;
        }
        return 3;
    }while(0);
    print_list(head, p);
    t = clock();
    res = solve4(head);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    delete_list(head);
    return 0;
}