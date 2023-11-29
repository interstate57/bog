#include "vspom_functions.h"
int main(int argc, char *argv[]){
    int task = 3;
    size_t n, len;
    char *s = 0;
    char* s1 = 0;
    char* s2 = 0;
    char* res;
    char* res_std;
    double t, t_std;
    if (argc != 4 || sscanf(argv[1], "%zu", &n) != 1){
        printf("Usage: %s count string string", argv[0]);
        return 1;
    }
    s = argv[2];
    s2 = argv[3];
    len = strlen(s) + strlen(s2) + 1;
    s1 = (char*)malloc(len * sizeof(char));
    if (!s1){
        printf("Not enough memory!\n");
        return 2;
    }
    s1 = strcpy(s1, s);
    t = test_2_5(n, &strcat_, s1, s2, &res);
    t_std = test_2_5(n, &strcat, s1, s2, &res_std);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res, t);
    printf ("%s : Task = %d Res = %s Elapsed = %.2f\n", argv[0], task, res_std, t_std);
}