#include "vspom_functions.h"
io_status solve3(const char* in, const char* out, const char* s, const char* t, int* r);
int main(int argc, char* argv[]){
    char* f_in = 0;
    char* f_out = 0;
    char* s = 0;
    char* t = 0;
    io_status ret;
    int r = 0, task = 3;
    double time = 0;
    if (argc != 5){
        printf("Usage: %s <f_in> <f_out> <s> <t>\n", argv[0]);
        return 1;
    }
    f_in = argv[1];
    f_out = argv[2];
    s = argv[3];
    t = argv[4];
    time = clock();
    ret = solve3(f_in, f_out, s, t, &r);
    time = (clock() - time) / CLOCKS_PER_SEC;
    switch (ret){
        case SUCCESS: printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, r, time); break;
        case ERROR_OPEN: printf("Cannot open %s\n", f_in); return 1;
        case ERROR_READ: printf("Cannot read %s\n", f_out); return 2;
        case ERROR_PATTERN: printf("Error in pattern %s\n", s); return 3;
    }
    return 0;
}
io_status solve3(const char* in, const char* out, const char* s, const char* t, int* r){
    FILE *fin, *fout;
    char buf[LEN];
    int i;
    int lol = 0;
    int per = 0;
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
        per = *r;
        lol = task3(s, t, buf, r);
        if (lol == ERROR_PATTERN){
            fclose(fin);
            fclose(fout);
            return ERROR_PATTERN;
        }
        else{
            if(per != *r) fprintf(fout, "%s\n", buf);
        }
    }
    fclose(fout);
    if (!feof(fin)){
        fclose(fin);
        return ERROR_READ;
    }
    fclose(fin);
    return SUCCESS;
}