#include "vspom_functions.h"
#define BACKSLASH '\\'
int pattern1(char* s, char* s1, char* s2){
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
    return 0;
}
int task1(char* s1, char* s2, char* buf){
    int i = 0, maybe_equal = 1;
    while (s1[i]){
        if (s2[i] == '1'){
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
        return 1;
    }
    return 0;
}




int task3(char* s3, int* s4, char* s5, char* buf){
    int i = 0, cnt = 0;
    int j = 0;
    cnt = 0;
    //printf("*****\n");
    for(i = 0; s3[i]; i++){
        //printf("Symbol %c: ", s3[i]);
        cnt = 0;
        while (buf[j + cnt] == s3[i]){
            cnt += 1;
        }
        //printf("found %d occurrences\n", cnt);
        if (s5[i] == '0' && cnt != s4[i]) return 0;
        if (s5[i] == '1' && cnt < s4[i]) return 0;
        j += cnt;
    }
    return 1;
}


int pattern3(char* s, char*s3, int* s4, char* s5){
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
    return 0;
}



int pattern5(char* s, char* s1, char* s2, char*s3, char* s4){
    int i = 0, j = 0, prev_back = 0;
    while (s[i]){
        if (s[i] == BACKSLASH){
            if (prev_back){
                s1[j] = s[i];
                s2[j] = '0';
                s3[j] = s[i];
                s4[i] = s[i];
                j += 1;
                prev_back = 0;
                i += 1;
                continue;
            }
            i += 1;
            prev_back = 1;
            if (!s[i]) return ERROR_LAST_BACKSLASH;
        }
        else if (s[i] == '[' && !prev_back){
            i += 1;
            if (!s[i]){
                printf("%d\n", i);
                return PATTERN_ERROR;
            }
            s1[j] = '@';
            s2[j] = '1';
            // start symbol
            if (s[i] == BACKSLASH){
                if (!s[i + 1])
                    return ERROR_LAST_BACKSLASH;
                s3[j] = s[i + 1];
                i += 1;
            }
            else {
                s3[j] = s[i];
            }
            i += 1;

            if (s[i] != '-') {
                printf("%d\n", i);
                return PATTERN_ERROR;
            }
            i += 1;

            // last symbol
            if (!s[i]){
                printf("%d\n", i);
                return PATTERN_ERROR;
            }
            if (s[i] == BACKSLASH){
                if (!s[i + 1])
                    return ERROR_LAST_BACKSLASH;
                s4[j] = s[i + 1];
                i += 1;
            }
            else {
                s4[j] = s[i];
            }
            i += 1;

            if (!s[i] || s[i] != ']'){
                printf("%d\n", i);
                return PATTERN_ERROR;
            }
            i += 1;
            j += 1;
        }
        else{
            if (s[i] == ']' && !prev_back){
                printf("%d\n", i);
                return PATTERN_ERROR;
            }
            s1[j] = s[i];
            s2[j] = '0';
            s3[j] = '@';
            s4[j] = '@';
            j += 1;
            i += 1;
            prev_back = 0;
        }
    }
    s1[j] = 0;
    s2[j] = 0;
    s3[j] = 0;
    s4[j] = 0;
    return 0;
}



int task5(char* s1, char* s2, char* s3, char* s4, char* buf){
    int i = 0, maybe_equal = 1;
    while (s1[i]){
         if (s2[i] == '0'){
            if (s1[i] == buf[i]){
                i += 1;
            }
            else{
                maybe_equal = 0;
                break;
            }
        }
        else{
            if (s3[i] <= buf[i] && buf[i] <= s4[i]){
                i += 1;
            }
            else{
                maybe_equal = 0;
                break;
            }
        }
    }
    if (maybe_equal && !buf[i]){
        return 1;
    }
    return 0;
}
int pattern2(char* s, char* s1, char* s2){
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
        else if (s[i] == '?' && !prev_back){
            if (i == 0){
                s1[is1] = s[i];
                s2[is2] = '0';
                is1 += 1;
                is2 += 2;
                i += 1;
            }
            else{
                s2[is2 - 1] = '1';
                i += 1;
            }
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
    return 0;
}

int task2(char * buf, char * s1, char * s2)
{
    int with = 0;
    while (s2[0] == '0') {
        if (!buf[0])
            return 0;
        
        if (buf[0] != s1[0])
            return 0;
        
        buf++;
        s1++;
        s2++;
    }

    if (!s2 && !buf)
        return 1;
    
    if (!s2)
        return 0;

    if (buf[0] == s1[0]) {
        with = task2(buf + 1, s1 + 1, s2 + 1);
    }
    if (with)
        return 1;

    return task2(buf, s1 + 1, s2 + 1);
}
