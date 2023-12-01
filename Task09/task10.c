#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 10;
    size_t n;
    char* s1 = 0;
    char* s2 = 0;
    char* res;
    char* res_std;
    char* next;
    char* next_std;
    double t, t_std;
    if (argc != 4 || sscanf(argv[1], "%zu", &n) != 1){
        printf("Usage: %s count string string", argv[0]);
        return 1;
    }
    s1 = argv[2];
    s2 = argv[3];
    t = test_10(n, &strtok_r_, s1, s2, &next, &res);
    printf ("%s : Task = %d Res = %s Saveptr = %s Elapsed = %.2f\n", 
            argv[0], task, res, next, t);
    t_std = test_10(n, &strtok_r_, s1, s2, &next_std, &res_std);
    printf ("%s : Task = %d Res = %s Saveptr = %s Elapsed = %.2f\n", 
            argv[0], task, res_std, next_std, t_std);
    return 0;
}