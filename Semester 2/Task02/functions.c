#include "vspom_functions.h"
#define BACKSLASH '\\'
int task1(const char* s, char* buf){
    char s1[LEN];
    char s2[LEN];
    int i = 0, is1 = 0, is2 = 0, prev_back = 0;
    while (s[i]){
        if (s[i] == BACKSLASH){
            if (prev_back){
                s1[is1] = s[i];
                s2[is2] = '0';
                is1 += 1;
                is2 += 1;
                prev_back = 0;
                i += 1;
                continue;
            }
            i += 1;
            prev_back = 1;
            if (!s[i]) return ERROR_LAST_BACKSLASH;
        }
        else if (s[i] == '.' && !prev_back){
            s1[is1] = s[i];
            s2[is2] = '1';
            is1 += 1;
            is2 += 1;
            i += 1;
        }
        else{
            s1[is1] = s[i];
            s2[is2] = '0';
            is1 += 1;
            is2 += 1;
            i += 1;
            prev_back = 0;
        }
    }
    s1[is1] = 0;
    s2[is2] = 0;
    i = 0;
    while (buf[i]){
        int maybe_equal = 1;
        int j = 0;
        is1 = 0;
        is2 = 0;
        while (s2[is2]){
            if (s2[is2] == '1'){
                is1 += 1;
                is2 += 1;
                j += 1;
            }
            else{
                if (s1[is1] == buf[i + j]){
                    is1 += 1;
                    is2 += 1;
                    j += 1;
                }
                else{
                    maybe_equal = 0;
                    break;
                }
            }
        }
        if (maybe_equal){
            return 1;
        }
        i += 1;
    }
    return 0;
}




int task3(const char* s, /*char* buf,*/ const char* out){
    char s1[LEN];
    char s2[LEN];
    char s3[LEN];
    int s4[LEN];
    char s5[LEN];
    FILE* fout;
    int i = 0, is1 = 0, is2 = 0, is3 = 0, is4 = 0, is5 = 0, special = 0, gruppa = 0, cnt = 0, prev_back = 0;
    if (!(fout = fopen(out, "w"))){
        return ERROR_OPEN;
    }
    while (s[i]){
        if (s[i] == BACKSLASH){
            if (prev_back){
                s1[is1] = s[i];
                s2[is2] = '0';
                is1 += 1;
                is2 += 1;
                prev_back = 0;
                i += 1;
                continue;
            }
            i += 1;
            prev_back = 1;
            if (!s[i]) return ERROR_LAST_BACKSLASH;
        }
        else if (s[i] == '+' && !prev_back){
            if (i == 0){
                s1[is1] = s[i];
                s2[is2] = '0';
                is1 += 1;
                is2 += 1;
            }
            else{
                s2[is2 - 1] = '1';
            }
            i += 1;
        }
        else{
            s1[is1] = s[i];
            s2[is2] = '0';
            is1 += 1;
            is2 += 1;
            i += 1;
            prev_back = 0;
        }
    }
    s1[is1] = 0;
    s2[is2] = 0;
    for (i = 0; i < is1 - 1; i++){
        if (s1[i] == s1[i + 1] && !gruppa){
            s3[is3] = s1[i];
            special = (s2[i] || s2[i + 1]);
            gruppa = 1;
            cnt += 2;
        }
        else if (s1[i] == s1[i + 1] && gruppa){
            special = (special || s2[i + 1]);
            cnt += 1;
        }
        else{
            is3 += 1;
            s4[is4] = cnt;
            is4 += 1;
            s5[is5] = special;
            special = 0;
            is5 += 1;
            cnt = 0;
        }
    }
    s3[is3] = 0;
    s4[is4] = 0;
    s5[is5] = 0;
    fprintf(fout, "%s\n", s1);
    fprintf(fout, "%s\n", s2);
    fprintf(fout, "%s\n", s3);
    fprintf(fout, "%ls\n", s4);
    fprintf(fout, "%s\n", s5);
    /*
    for (i = 0; buf[i]; i++){
        int maybe_equal = 1;
        int j = 0;
        is1 = 0;
        is2 = 0;
        while (s2[is2]){
            if (s2[is2] == '1'){
                if (buf[i + j] == s1[is1]){
                    is1 += 1;
                    is2 += 1;
                    j += 1;
                }
                else if ((buf[i + j] == s1[is1 + 1]) || (!s1[is1 + 1])){
                    if (!s1[is1 + 1]) break;
                    is1 += 2;
                    is2 += 2;
                    j += 1;
                }
                else{
                    maybe_equal = 0;
                    break;
                }
            }
            else{
                if (s1[is1] == buf[i + j]){
                    is1 += 1;
                    is2 += 1;
                    j += 1;
                }
                else{
                    maybe_equal = 0;
                    break;
                }
            }
        }
        if (maybe_equal){
            return 1;
        }
    }
    */
    return 0;
}








/*int task3(const char* s, const char* t, char* buf){
    int SLOVA[LEN / 2];
    int i;
    int nach = (s[0] == BACKSLASH && s[1] == '<') ? 2 : 0;
    int k = 0, slovo = 0, j = nach, p = 0;
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2]))
        return 1;
    for (i = 0; i < LEN; i++){
        if (!strchr(t, buf[i]) && !slovo){
            SLOVA[p] = i;
            slovo = 1;
            p ++;
        }
        else if ((strchr(t, buf[i]) || buf[i] == 0) && slovo){
            SLOVA[p] = i;
            slovo = 0;
            p ++;
        }
        else if (buf[i] == 0) break;
    }
    for (i = 0; i < p; i += 2){
        for (int q = SLOVA[i]; q < SLOVA[i + 1]; q++){
            int maybe_equal = 1;
            j = nach;
            k = 0;
            if (q != SLOVA[i] && nach){
                maybe_equal = 0;
                break;
            }
            while (s[j]){
                if (s[j] == BACKSLASH){
                    j += 1;
                    if (!s[j]) return ERROR_LAST_BACKSLASH;
                }
                if (s[j] != buf[q + k]){
                    j = nach;
                    k = 0;
                    maybe_equal = 0;
                    break;
                }
                j += 1;
                k += 1;
            }
            if (maybe_equal)
                return 1;
        }
    }
    return 0;
}











int task4(const char* s, char* buf){
    int SLOVA[LEN / 2];
    int i;
    int k = 0, slovo = 0, j = 0, p = 0;
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2]))
        return 1;
    for (i = 0; i < LEN; i++){
        if (!strchr(t, buf[i]) && !slovo){
            SLOVA[p] = i;
            slovo = 1;
            p ++;
        }
        else if ((strchr(t, buf[i]) || buf[i] == 0) && slovo){
            SLOVA[p] = i;
            slovo = 0;
            p ++;
        }
        else if (buf[i] == 0) break;
    }
    for (i = 0; i < p; i += 2){
        for (int q = SLOVA[i]; q < SLOVA[i + 1]; q++){
            int maybe_equal = 1;
            j = 0;
            k = 0;
            while (s[j]){
                if (s[j] == BACKSLASH){
                    j += 1;
                    if (!s[j]) return ERROR_LAST_BACKSLASH;
                }
                if (s[j] == '>' && !s[j + 1] && j > 0 && s[j - 1] == BACKSLASH){
                    if (q + k == SLOVA[i + 1])
                        return 1;
                    else {
                        maybe_equal = 0;
                        break;
                    }
                }
                else if (s[j] != buf[q + k]){
                    maybe_equal = 0;
                    break;
                }
                j += 1;
                k += 1;
            }
            if (maybe_equal)
                return 1;
        }
    }
    return 0;
}
*/