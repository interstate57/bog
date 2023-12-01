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
    if (!s1){
        printf("Not enough memmory!");
        return 2;
    }
    t = test_2_5(n, &strcpy_, s1, s2, &res);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res, t);
    s1[0] = 0;
    t_std = test_2_5(n, &strcpy, s1, s2, &res_std);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res_std, t_std);
    free (s1);
    return 0;
}