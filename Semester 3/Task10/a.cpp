#include "list2.h"
#include "tree.h"

int list2::m = 0;
int list2::r = 0;

int main (int argc, char *argv[]){
    char* name = 0;
    int r = 0;
    io_status ret;
    int task = 1;
    double t = 0;
    int res = 0;
    int m = 0;
    FILE* fp1;
    FILE* fp2;
    if (!((argc == 4) && sscanf(argv[1], "%d", &r) == 1 && sscanf(argv[3], "%d", &m) == 1)){
        printf("Usage: %s r filename m\n", argv[0]);
        return 1;
    }
    name = argv[2];
    list2::set_m (m);
    list2::set_r (r);
    tree<student> *a = new tree<student>;
    if (!(fp1 = fopen(name, "r"))) return -1;
    ret = a->read(fp1);
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
    t = clock();
    res = a->solve1_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 2;
    printf("\n");
    t = clock();
    res = a->solve2_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 3;
    printf("\n");
    t = clock();
    res = a->solve3_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 4;
    printf("\n");
    t = clock();
    res = a->solve4_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 5;
    printf("\n");
    t = clock();
    res = a->solve5_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 6;
    printf("\n");
    t = clock();
    res = a->solve6();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    printf("\n");
    a->print(r);
    delete a;
    tree<list2> *b = new tree<list2>;
    if (!(fp2 = fopen(name, "r"))) return -1;
    ret = b->read(fp2);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::format: printf("Cannot read file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        return 3;
    }while(0);
    b->print(r);
    task = 1;
    printf("\n");
    t = clock();
    res = b->solve1_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 2;
    printf("\n");
    t = clock();
    res = b->solve2_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 3;
    printf("\n");
    t = clock();
    res = b->solve3_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 4;
    printf("\n");
    t = clock();
    res = b->solve4_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 5;
    printf("\n");
    t = clock();
    res = b->solve5_();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    task = 6;
    printf("\n");
    t = clock();
    res = b->solve6();
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, m, res, t);
    printf("\n");
    b->print(r);
    delete b;
    return 0;
}