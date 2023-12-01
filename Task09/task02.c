#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 2;
    size_t n, len;
    char *s1 = 0;
    char *s2 = 0;
    char* res;
    char* res_std;
    double t, t_std;
    if (argc != 3 || sscanf(argv[1], "%lu", &n) != 1){
        printf("Usage: %s count string", argv[0]);
        return 1;
    }
    s2 = argv[2];
    len = strlen(s2) + 1;
    s1 = (char*)malloc(len * sizeof(char));
    res = (char*)malloc(len * sizeof(char));
    res_std = (char*)malloc(len * sizeof(char));
    t = test_2_5(n, &strcpy_, s1, s2, &res);
    t_std = test_2_5(n, &strcpy, s1, s2, &res_std);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res, t);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res_std, t_std);
    return 0;
}