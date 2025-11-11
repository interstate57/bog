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
    FILE* fp;
    tree a;
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
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        return 3;
    }while(0);
    printf ("Original tree:\n");
    a.print (r);
    int T = a.get_count_total ();
    int L = a.get_count_leaf ();
    int C1 = a.get_count_1 ();
    int C2 = a.get_count_2 ();
    int H = a.get_height ();
    int W = a.get_width ();
    int B = a.get_balance ();
    printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d \n", argv[0], task, T, L, C1, C2, H, W, B);
    t = clock ();
    a.a1();
    t = (clock() - t)/CLOCKS_PER_SEC;
    printf ("Modified tree:\n");
    a.print (r);
    T = a.get_count_total ();
    L = a.get_count_leaf ();
    C1 = a.get_count_1 ();
    C2 = a.get_count_2 ();
    H = a.get_height ();
    W = a.get_width ();
    B = a.get_balance ();
    printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d Elapsed = %.2f\n", argv[0], task, T, L, C1, C2, H, W, B, t);
    return 0;
}