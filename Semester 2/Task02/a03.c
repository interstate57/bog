#include "vspom_functions.h"
int solve3(const char* in, const char* out, char* s);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    int res = 0, task = 3;
    double t = 0;
    if (argc != 4){
        printf("Usage: %s name1 name2 s\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = clock();
    res = solve3(name1, name2, s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res < SUCCESS){
        switch (res){
            case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
            case ERROR_READ: printf("Cannot read %s;\n", name1); break;
            case ERROR_LAST_BACKSLASH: printf("Error backslash %s;\n", name1); break;
            default: printf("Unknown Error %d in file %s;\n", res, name1);
        }
        return 4;
    }
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}
int solve3(const char* in, const char* out, char* s){
    FILE *fin, *fout;
    char s3[LEN];
    int s4[LEN];
    char s5[LEN];
    char buf[LEN];
    int i;
    int lol = 0;
    int cnt = 0, r = 0;
    if (!(fin = fopen(in, "r")))
        return ERROR_OPEN;
    if (!(fout = fopen(out, "w"))){
        fclose(fin);
        return ERROR_OPEN;
    }
    r = pattern3(s, s3, s4, s5);
    if (r == ERROR_LAST_BACKSLASH){
        fclose(fin);
        fclose(fout);
        return ERROR_LAST_BACKSLASH;
    }
    while (fgets(buf, LEN, fin)){
        for (i = 0; buf[i]; i++)
            if (buf[i] == '\n'){
                buf[i] = 0;
                break;
            }
        lol = task3(s3, s4, s5, buf);
        if (lol){
            fprintf(fout, "%s\n", buf);
            cnt += 1;
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