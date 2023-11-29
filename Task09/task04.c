#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 4;
    size_t n;
    char *s = 0;
    char ch = 0;
    char* res;
    char* res_std;
    double t, t_std;
    if (argc != 4 || sscanf(argv[1], "%lu", &n) != 1 || sscanf(argv[3], "%c", &ch) != 1){
        printf("Usage: %s count string integer", argv[0]);
        return 1;
    }
    s = argv[2];
    t = test_3_4(n, &strrchr_, s, ch, &res);
    t_std = test_3_4(n, &strrchr, s, ch, &res_std);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res, t);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res_std, t_std);
}