#include "vspom_functions.h"
io_status solve2(const char* in, const char* out, const char* s, int* r);
int main(int argc, char* argv[]){
    char* f_in = 0;
    char* f_out = 0;
    char* s = 0;
    io_status ret;
    int r = 0, task = 2;
    double t = 0;
    if (argc != 4){
        printf("Usage: %s <f_in> <f_out> <s>\n", argv[0]);
        return 1;
    }
    f_in = argv[1];
    f_out = argv[2];
    s = argv[3];
    t = clock();
    ret = solve2(f_in, f_out, s, &r);
    t = (clock() - t) / CLOCKS_PER_SEC;
    switch (ret){
        case SUCCESS: printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, r, t); break;
        case ERROR_OPEN: printf("Cannot open %s\n", f_in); return 1;
        case ERROR_READ: printf("Cannot read %s\n", f_out); return 2;
        case ERROR_PATTERN: printf("Error in pattern %s\n", s); return 3;
    }
    return 0;
}
io_status solve2(const char* in, const char* out, const char* s, int* r){
    FILE *fin, *fout;
    char buf[LEN];
    int s2 = 0;
    char s1[LEN];
    int i;
    io_status lol;
    io_status kek;
    int per = 0;
    if (!(fin = fopen(in, "r")))
        return ERROR_OPEN;
    if (!(fout = fopen(out, "w"))){
        fclose(fin);
        return ERROR_OPEN;
    }
    kek = pattern2(s, s1, &s2);
    if (kek == ERROR_PATTERN){
        fclose(fin);
        fclose(fout);
        return ERROR_PATTERN;
    }
    while (fgets(buf, LEN, fin)){
        for (i = 0; buf[i]; i++)
            if (buf[i] == '\n'){
                buf[i] = 0;
                break;
            }
        per = *r;
        lol = task2(s, buf, s1, s2, r);
        if(per != *r && lol == SUCCESS) fprintf(fout, "%s\n", buf);
    }
    fclose(fout);
    if (!feof(fin)){
        fclose(fin);
        return ERROR_READ;
    }
    fclose(fin);
    return SUCCESS;
}