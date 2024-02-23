#include "vspom_functions.h"
int solve2(const char* in, const char* out, char* s);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    int res = 0, task = 2;
    double t = 0;
    if (argc != 4){
        printf("Usage: %s name1 name2 s\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = clock();
    res = solve2(name1, name2, s);
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
int solve2(const char* in, const char* out, char* s){
    FILE *fin, *fout;
    char buf[LEN];
    char s1[LEN];
    char s2[LEN];
    int i;
    int lol = 0;
    int cnt = 0, r = 0;
    if (!(fin = fopen(in, "r")))
        return ERROR_OPEN;
    if (!(fout = fopen(out, "w"))){
        fclose(fin);
        return ERROR_OPEN;
    }
    r = pattern2(s, s1, s2);
    printf("s1, s2: %s %s\n", s1, s2);
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
        lol = task2(s1, s2, buf);
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