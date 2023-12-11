#include "vspom_functions.h"
#include "solves.h"
int main(int argc, char* argv[]){
    int n, m, i, ret;
    int res = 0, task = 5;
    char* name;
    char* s;
    char** a;
    double t;
    if (!(argc == 5 && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &m) == 1)){
        printf("Usage: %s int int name string\n", argv[0]);
        return 1;
    }
    name = argv[3];
    s = argv[4];
    a = (char**)malloc(n* sizeof(char*));
    if (!a){
        printf("Cannot allocate a!\n");
        return 2;
    }
    for (i = 0; i < n; i++) a[i] = 0;
    ret = read_array(a, n, name);
    if (ret != SUCCESS){
        switch (ret)
        {
        case ERROR_OPEN:
            printf("Cannot open %s\n", name);
            break;
        case ERROR_READ:
            printf("Cannot read %s\n", name);
            break;
        case ERROR_MEM:
            printf("Cannot allocate string %s\n", name);
            break;
        default:
            printf("Unknown error in %s\n", name);
            break;
        }
        free(a);
        return 3;
    }
    print_array(a, n, m);
    t = clock();
    res = solve5(a, n, s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("New array:\n");
    print_array (a, res, m); 
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free_array (a, res); 
    free(a);
    return SUCCESS;
}