#include "vspom_functions.h"
#define BACKSLASH '\\'
io_status task1(const char* s, char* buf, int* r){
    int nach = (s[0] == '^') ? 1 : 0;
    int j = nach, k = 0;
    if ((!buf[0] && !s[0]) || (s[0] == '^' && !s[1])){
        *r += 1;
        return SUCCESS;
    } 
    for (int i = 0; buf[i]; i++){
        int maybe_equal = 1;
        if (i != 0 && nach){
            return SUCCESS;
        }
        while (s[j]){
            if (s[j] == BACKSLASH){
                j += 1;
                if (!s[j]) {
                    return ERROR_PATTERN;
                }
            }
            if (s[j] != buf[i + k]){
                j = nach;
                k = 0;
                maybe_equal = 0;
                break;
            }
            j += 1;
            k += 1;
        }
        if (maybe_equal){
            *r += 1;
            return SUCCESS;
        }
    }
    return SUCCESS;
}

io_status pattern2(const char* s, char* s1, int* s2){
    int i = 0, is1 = 0, prev_back = 0;
    while (s[i]){
        if (s[i] == BACKSLASH){
            if (prev_back){
                s1[is1] = s[i];
                is1 += 1;
                prev_back = 0;
                i += 1;
                continue;
            }
            i += 1;
            prev_back = 1;
            if (!s[i]) return ERROR_PATTERN;
        }
        else if (s[i] == '$' && !prev_back){
            *s2 += 1;
            s1[is1] = s[i];
            i += 1;
            if (!s[i]) s1[is1] = 0;
            else{
                is1 += 1;
                *s2 -= 1;
            }
            
        }
        else{
            s1[is1] = s[i];
            is1 += 1;
            i += 1;
            prev_back = 0;
        }
    }
    return SUCCESS;
}

io_status task2(const char* s, char* buf, char* s1, int s2, int* r){
    int j, k;
    if ((!buf[0] && !s[0]) || (s[0] == '$' && !s[1])){
        *r += 1;
        return SUCCESS;
    }
    for (int i = 0; buf[i]; i++){
        int maybe_equal = 1;
        j = 0;
        k = 0;
        while (s1[j]){
            if (s[j] != buf[i + k]){
                maybe_equal = 0;
                break;
            }
            j += 1;
            k += 1;
        }
        if (maybe_equal){
            if ((s2 == 0) || ((s2 == 1) && !buf[i + k])){
                *r += 1;
                return SUCCESS;
            }
        }
    }
    return SUCCESS;
}

io_status task3(const char* s, const char* t, char* buf, int* r){
    int SLOVA[LEN / 2];
    int i;
    int nach = (s[0] == BACKSLASH && s[1] == '<') ? 2 : 0;
    int k = 0, slovo = 0, j = nach, p = 0;
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2])){
        *r += 1;
        return SUCCESS;
    }
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
                    if (!s[j]) return ERROR_PATTERN;
                }
                if (s[j] != buf[q + k]){
                    maybe_equal = 0;
                    break;
                }
                j += 1;
                k += 1;
            }
            if (maybe_equal){
                *r += 1;
                return SUCCESS;
            }
        }
    }
    return SUCCESS;
}
io_status task4(const char* s, const char* t, char* buf, int* r){
    int SLOVA[LEN / 2];
    int i;
    int k = 0, slovo = 0, j = 0, p = 0;
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2])){
        *r += 1;
        return SUCCESS;
    }
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
                    if (!s[j]) return ERROR_PATTERN;
                }
                if (s[j] == '>' && !s[j + 1] && j > 0 && s[j - 1] == BACKSLASH){
                    if (q + k == SLOVA[i + 1]){
                        *r += 1;
                        return SUCCESS;
                    }
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
            if (maybe_equal){
                *r += 1;
                return SUCCESS;
            }
        }
    }
    return SUCCESS;
}
io_status pattern6(const char* s, char* s1, char* s2){
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
            if (!s[i]) return ERROR_PATTERN;
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
    return SUCCESS;
}

io_status task6(char* s1, char* s2, char* buf, int* r){
    int i = 0, maybe_equal = 1;
    while (s1[i]){
        if (s2[i] == '1' && buf[i]){
            i += 1;
        }
        else{
            if (s1[i] == buf[i]){
                i += 1;
            }
            else{
                maybe_equal = 0;
                break;
            }
        }
    }
    if (maybe_equal && !buf[i]){
        *r += 1;
        return SUCCESS;
    }
    return SUCCESS;
}

io_status pattern8(const char* s, char*s3, int* s4, char* s5){
    char s1[LEN];
    char s2[LEN];
    int i = 0, is1 = 0, is2 = 0, is3 = 0, is4 = 0, is5 = 0, special = 0, gruppa = 0, cnt = 0, prev_back = 0;
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
            if (!s[i]) return ERROR_PATTERN;
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
    printf("%s\n", s1);
    printf("%s\n", s2);
    for (i = 0; i < is1 - 1; i++){
        if (s1[i] == s1[i + 1] && !gruppa){
            s3[is3] = s1[i];
            special = ((s2[i] == '1') || (s2[i + 1] == '1'));
            gruppa = 1;
            cnt += 2;
        }
        else if (s1[i] == s1[i + 1] && gruppa){
            special = (special || (s2[i + 1] == '1'));
            cnt += 1;
        }
        else if (gruppa){
            is3 += 1;
            s4[is4] = cnt;
            is4 += 1;
            s5[is5] = special ? '1' : '0';
            special = 0;
            is5 += 1;
            cnt = 0;
            gruppa = 0;
        }
        else{
            s3[is3] = s1[i];
            is3 += 1;
            s4[is4] = 1;
            is4 += 1;
            s5[is5] = (s2[i] == '1') ? '1' : '0';
            is5 += 1;
        }
    }
    if (gruppa){
            is3 += 1;
            s4[is4] = cnt;
            is4 += 1;
            s5[is5] = special ? '1' : '0';
            special = 0;
            is5 += 1;
            cnt = 0;
            gruppa = 0;
        }
    else{
            s3[is3] = s1[i];
            is3 += 1;
            s4[is4] = 1;
            is4 += 1;
            s5[is5] = (s2[i] == '1') ? '1' : '0';
            is5 += 1;
    }
    s3[is3] = 0;
    s4[is4] = 0;
    s5[is5] = 0;
    return SUCCESS;
}

io_status task8(char* s3, int* s4, char* s5, char* buf, int* r){
    int i = 0, cnt = 0;
    int j = 0;
    cnt = 0;
    for(i = 0; s3[i]; i++){
        cnt = 0;
        while (buf[j + cnt] == s3[i]){
            cnt += 1;
        }
        if (s5[i] == '0' && cnt != s4[i]) return SUCCESS;
        if (s5[i] == '1' && cnt < s4[i]) return SUCCESS;
        j += cnt;
    }
    *r += 1;
    return SUCCESS;
}