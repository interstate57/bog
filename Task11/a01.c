#include "vspom_functions.h"
#include "string_io.h"
int sravnenie_bukv(char s1, char s2);
int min(int a, int b);
int solve1(const char* fp1, const char* fp2, const char* s);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    int res = 0, task = 1;
    double t;
    if (argc != 4){
        printf("Usage: %s fname1 fname2 string\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = clock();
    res = solve1(name1, name2, s);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res < SUCCESS){
        switch (res){
            case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
            case ERROR_READ: printf("Cannot read %s;\n", name1); break;
            default: printf("Unknown Error %d in file %s;\n", res, name1);
        }
    }
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}
int solve1(const char* name1, const char* name2, const char* s){
    char buf[LEN];
    int i, j;
    int cnt = 0;
    FILE *fp1;
    FILE *fp2;
    if (!(fp2 = fopen(name2, "w"))){
        return ERROR_OPEN;
    }
    if (!(fp1 = fopen(name1, "r"))){
        fclose(fp2);
        return ERROR_OPEN;
    }
    while (fgets(buf, LEN, fp1)){
        for (i = 0; buf[i]; i ++){
            int f = 0;
            for (j = 0; buf[i + j] && s[j]; j ++){
                if (!sravnenie_bukv(s[j], buf[i + j])){
                    f = 1;
                    break;
                }
            }
            if (f == 0 && !s[j]){
                cnt += 1;
                fprintf(fp2, "%s", buf);
                break;
            }
        }

    }
    if (!feof(fp1)){
        fclose(fp1);
        fclose(fp2);
        return ERROR_READ;
    }
    fclose(fp1);
    fclose(fp2);
    return cnt;
}
int sravnenie_bukv(char s1, char s2){
    if (s1 == s2)
        return 1;
    if ((('A' <= s1 && 'Z' >= s1) || ('A' <= s2 && 'Z' >= s2)) && abs(s1 - s2) == 32 && min(s1, s2) >= 65)
        return 1;
    return 0;
}
int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}