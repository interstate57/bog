#include "vspom_functions.h"
int solve3(const char* in, const char* out, const char* s, const char* t);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    char* t = 0;
    int res = 0, task = 3;
    double t1 = 0;
    if (argc != 5){
        printf("Usage: %s name1 name2 s t\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = argv[4];
    t1 = clock();
    res = solve3(name1, name2, s, t);
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    if (res < SUCCESS){
        switch (res){
            case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
            case ERROR_READ: printf("Cannot read %s;\n", name1); break;
            case ERROR_LAST_BACKSLASH: printf("Error backslash %s;\n", name1); break;
            default: printf("Unknown Error %d in file %s;\n", res, name1);
        }
        return 4;
    }
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t1);
    return 0;
}
int solve3(const char* in, const char* out, const char* s, const char* t){
    FILE *fin, *fout;
    char buf[LEN];
    int i;
    int cnt = 0;
    if (!(fin = fopen(in, "r")))
        return ERROR_OPEN;
    if (!(fout = fopen(out, "w"))){
        fclose(fin);
        return ERROR_OPEN;
    }
    while (fgets(buf, LEN, fin)){
        for (i = 0; buf[i]; i++)
            if (buf[i] == '\n'){
                buf[i] = 0;
                break;
            }
        if (task3(s, t, buf)){
            if (task3(s, t, buf) != ERROR_LAST_BACKSLASH){
                fprintf(fout, "%s\n", buf);
                cnt += 1;
            }
            else{
                fclose(fin);
                fclose(fout);
                return ERROR_LAST_BACKSLASH;
            }
        }
    }
    fclose(fout);
    if (!feof(fin)){
        fclose(fin);
        return ERROR_READ;
    }
    fclose(fin);
    return cnt;
}