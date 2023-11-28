#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 1;
    size_t n;
    char *s1;
    char *s2;
    size_t res = 0, res_std = 0;
    double t, t_std;
    if (argc != 3 || sscanf(argv[1], "%lu", &n) != 1){
        printf("Usage: %s count string", argv[0]);
        return 1;
    }
    s2 = argv[2];
    t = test_2_5(n, &strcpy_, s1, s2, &res);
    t_std = test_2_5(n, &strcpy, s1, s2, &res_std);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res, t);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res_std, t_std);
}