#include "vspom_functions.h"
#include "string_io.h"
void trimm(char *buf);
int solve8(const char* name1, const char* name2, const char* s, const char* l, const char* r);
int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* s = 0;
    char* l = 0;
    char* r = 0;
    int res = 0, task = 8;
    double t1;
    if (argc != 6){
        printf("Usage: %s fname1 fname2 string string string\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    l = argv[4];
    r = argv[5];
    t1 = clock();
    res = solve8(name1, name2, s, l, r);
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
int solve8(const char* name1, const char* name2, const char* s, const char* l, const char* r){
    char buf[LEN];
    int cnt = 0, len_s = strlen_(s);
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
        int k = 0;
        char* current = buf;
        while (1){
            char* f = strstr_(current, s);
            if (!f){
                fprintf(fp2, "%s", current);
                break;
            }
            else{
                *f = 0;
                fprintf(fp2, "%s", current);
                fprintf(fp2, "%s", l);
                fprintf(fp2, "%s", s);
                fprintf(fp2, "%s", r);
                current = f + len_s;
                if (k == 0){
                    cnt += 1;
                    k = 1;
                }
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
void trimm(char *buf){
    int i = strlen_(buf) - 1;
    for (; i >= 0; i--){
        if (buf[i] == '\n'){
            buf[i] = 0;
        }
    }
}