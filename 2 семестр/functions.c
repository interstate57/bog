#include "vspom_functions.h"
#define BACKSLASH '\\'
int task1(const char* s, char* buf){
    int nach = (s[0] == '^') ? 1 : 0;
    int dls = strlen(s) - 1;
    int j = nach, k = 0;
    for (int i = 0; buf[i]; i++){
        while (j <= dls){
            if (i != 0 && nach){
                return 0;
            }
            if (s[j] == BACKSLASH){
                j += 1;
                if (j > dls) return ERROR_LAST_BACKSLASH;
            }
            if (s[j] != buf[i + k]){
                j = nach;
                break;
            }
            else if (j < dls){
                j += 1;
                k += 1;
            }
            else{
                return 1;
            }
        }
    }
    return 0;
}
int task2(const char* s, char* buf){
    int dls = strlen(s) - 1;
    int j = 0, k = 0;
    for (int i = 0; buf[i]; i++){
        while (j <= dls){
            if (s[j] == BACKSLASH){
                j += 1;
                if (j > dls) return ERROR_LAST_BACKSLASH;
            }
            if (s[j] != buf[i + k]){
                j = 0;
                break;
            }
            else if (j < dls){
                j += 1;
                k += 1;
            }
            else if (j == dls && s[j] == '$' && buf[i + k] == 0){
                return 1;
            }
        }
    }
    return 0;
}
/*
int task03(const char* s, const char* t, char* buf, int dl){
    char SLOVA[672];
    int i;
    int nach = (s[0] == BACKSLASH && s[1] == '<') ? 2 : 0;
    int k = 0, slovo = 0, j = nach, p = 0;
    int dls = strlen(s) - 1;
    for (i = 0; i <= dl; i++){
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
    }
    for (i = 0; i <= 671; i + 2){
        if (SLOVA[i + 1] - SLOVA[i] < dls) continue;
        for (int q = SLOVA[i]; q <= SLOVA[i + 1] - dls; q++){
            while (j <= dls){
                if (q != 0 && nach){
                    break;
                }
                if (s[j] == BACKSLASH){
                    j += 1;
                    if (j > dls) return ERROR_LAST_BACKSLASH;
                }
                if (s[j] != buf[i + k]){
                    j = nach;
                    break;
                }
                else if (j < dls){
                    j += 1;
                    k += 1;
                }
                else{
                    return 1;
                }
            }
        }
    }
    return 0;
}
*/