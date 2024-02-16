#include "vspom_functions.h"
#define BACKSLASH '\\'
int task1(const char* s, char* buf){
    int nach = (s[0] == '^') ? 1 : 0;
    int j = nach, k = 0;
    if ((!buf[0] && !s[0]) || (s[0] == '^' && !s[1])) return 1;
    for (int i = 0; buf[i]; i++){
        int maybe_equal = 1;
        if (i != 0 && nach){
            return 0;
        }
        while (s[j]){
            if (s[j] == BACKSLASH){
                j += 1;
                if (!s[j]) {
                    return ERROR_LAST_BACKSLASH;
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
        if (maybe_equal)
            return 1;
    }
    return 0;
}
int task2(const char* s, char* buf){
    int j, k;
    if ((!buf[0] && !s[0]) || (s[0] == '$' && !s[1]))
        return 1;
    for (int i = 0; buf[i]; i++){
        int maybe_equal = 1;
        j = 0;
        k = 0;
        while (s[j]){
            if (s[j] == BACKSLASH){
                j += 1;
                if (!s[j]) return ERROR_LAST_BACKSLASH;
            }
            if (s[j] == '$' && !s[j + 1]){
                if (!buf[i + k])
                    return 1;
                else {
                    maybe_equal = 0;
                    break;
                }
            }
            else if (s[j] != buf[i + k]){
                maybe_equal = 0;
                break;
            }
            j += 1;
            k += 1;
        }
        if (maybe_equal)
            return 1;
    }
    return 0;
}

int task3(const char* s, const char* t, char* buf){
    int SLOVA[672];
    int i;
    int nach = (s[0] == BACKSLASH && s[1] == '<') ? 2 : 0;
    int k = 0, slovo = 0, j = nach, p = 0;
    //int dls = strlen(s);
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2]))
        return 1;
    for (i = 0; i <= 1233; i++){
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
    for (i = 0; i <= p / 2; i += 2){
        for (int q = SLOVA[i]; q < SLOVA[i + 1]; q++){
            int maybe_equal = 1;
            if (q != SLOVA[i] && nach){
                maybe_equal = 0;
                break;
            }
            while (s[j]){
                if (s[j] == BACKSLASH){
                    j += 1;
                    if (!s[j]) return ERROR_LAST_BACKSLASH;
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
            if (maybe_equal)
                return 1;
        }
    }
    return 0;
}
int task4(const char* s, const char* t, char* buf){
    int SLOVA[672];
    int i;
    int k = 0, slovo = 0, j = 0, p = 0;
    if ((!buf[0] && !s[0]) || (s[0] == BACKSLASH && s[1] == '<' && !s[2]))
        return 1;
    for (i = 0; i <= 1233; i++){
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
    // ---------------------------------------------
    for (i = 0; i <= p / 2; i += 2){
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