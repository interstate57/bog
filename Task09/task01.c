#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 1;
    size_t n;
    char *s;
    size_t res = 0, res_std = 0;
    double t, t_std;
    if (argc != 3 || sscanf(argv[1], "%lu", &n) != 1){
        printf("Usage: %s count string", argv[0]);
        return 1;
    }
    s = argv[2];
    t = test_1(n, &strlen_, s, &res);
    t_std = test_1(n, &strlen, s, &res_std);
    printf ("%s : Task = %d Res = %zd Elapsed = %.2f\n", argv[0], task, res, t);
    printf ("%s : Task = %d Res = %zd Elapsed = %.2f\n", argv[0], task, res_std, t_std);
    return 0;
}