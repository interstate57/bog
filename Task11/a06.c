#include "vspom_functions.h"
#include "string_io.h"
void trimm(char *buf);
void delete_spaces(const char* buf1, char* buf2, const char* spaces);
int sravnenie_bukv(char s1, char s2);
int solve4(const char* name1, const char* name2, const char* s, const char* t);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    char* t = 0;
    int res = 0, task = 6;
    double t1;
    if (argc != 5){
        printf("Usage: %s fname1 fname2 string\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = argv[4];
    t1 = clock();
    res = solve4(name1, name2, s, t);
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    if (res < SUCCESS){
        switch (res){
            case ERROR_OPEN: printf("Cannot open %s;\n", name1); break;
            case ERROR_READ: printf("Cannot read %s;\n", name1); break;
            default: printf("Unknown Error %d in file %s;\n", res, name1);
        }
    }
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t1);
    return 0;
}
int solve4(const char* name1, const char* name2, const char* s, const char* t){
    char buf1[LEN];
    char buf2[LEN];
    int cnt = 0, i = 0;
    char spaces[256] = {0};
    char s1[LEN];
    FILE *fp1;
    FILE *fp2;
    if (!(fp2 = fopen(name2, "w"))){
        return ERROR_OPEN;
    }
    if (!(fp1 = fopen(name1, "r"))){
        return ERROR_OPEN;
    }
    for (i = 0; t[i]; i ++)
        spaces[(unsigned char) t[i]] = 1;
    delete_spaces(s, s1, spaces);
    //printf("s with deleted spaces: %s\n", s1);
    while (fgets(buf1, LEN, fp1)){
        int j;
        trimm(buf1);
        delete_spaces(buf1, buf2, spaces);
        //printf("buf with deleted spaces: %s\n", buf2);
        for (i = 0; buf2[i]; i ++){
            int f = 0;
            for (j = 0; buf2[i + j] && s1[j]; j ++){
                if (!sravnenie_bukv(s1[j], buf2[i + j])){
                    f = 1;
                    break;
                }
            }
            if (f == 0 && !s1[j]){
                cnt += 1;
                fprintf(fp2, "%s", buf1);
                break;
            }
        }
    }
    if (!feof(fp1)){
        fclose(fp1);
        return ERROR_READ;
    }
    fclose(fp1);
    return cnt;
}
void trimm(char *buf){
    int i = strlen_(buf) - 1;
    for (; i >= 0; i--){
        if (buf[i] == '\n'){
            buf[i] = 0;
            break;
        }
    }
}
void delete_spaces(const char* buf1, char* buf2, const char* spaces){
    int i = 0, j = 0;
    for (; buf1[i]; i ++){
        if (!spaces[(unsigned int) buf1[i]]){
            buf2[j] = buf1[i];
            j += 1;
        }
    }
    buf2[j] = 0;
}
int sravnenie_bukv(char s1, char s2){
    if (s1 == s2)
        return 1;
    return 0;
}
//добавить триммы в другие задачи