#include "solves.h"
#include "vspom_functions.h"
int sravnenie_bukv(char s1, char s2);
int min(int a, int b);
int dop_funct(const char* buf, const char* s);
int solve1(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    for (i = 0; i < n; i++){
        if (strcmp_(a[i], s) >= 0){
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
    }
        for(k = j; k < n; k++){
            if (a[k]){
                free(a[k]);
                a[k] = 0;
            }
        }
    return j;
}
int solve2(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    for (i = 0; i < n; i++){
        if (!strstr_(s, a[i])){
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}
int solve3(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    size_t len_s = strlen_(s);
    for (i = 0; i < n; i++){
        if (strcspn_(s, a[i]) != len_s){
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}
int solve4(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    int f = 0;
    size_t len_s = strlen_(s);
    for (i = 0; i < n; i++){
        size_t len_ai = strlen_(a[i]);
        if (len_ai >= len_s || (len_ai < len_s && f == 0)){
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
            if (len_ai < len_s && f == 0) f = 1;
            else if (len_ai >= len_s && f == 1) f = 0;
        }
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}
int solve5(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    int f = 0;
    size_t len_s = strlen_(s);
    for (i = 0; i < n; i++){
        size_t len_ai = strlen_(a[i]);
        if (strcmp_(s, a[i] + len_ai - len_s) != 0 || (strcmp_(s, a[i] + len_ai - len_s) == 0 && f == 0)){
            if (strcmp_(s, a[i] + len_ai - len_s) == 0 && f == 0) f = 1;
            else if (strcmp_(s, a[i] + len_ai - len_s) != 0 && f == 1) f = 0;
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}
int solve6(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    int f = 0;
    size_t len_s = strlen_(s);
    for (i = 0; i < n; i++){
        if (strcspn_(s, a[i]) != len_s || (strcspn_(s, a[i]) == len_s && f == 0)){
            if (strcspn_(s, a[i]) == len_s && f == 0) f = 1;
            else if (strcspn_(s, a[i]) != len_s && f == 1) f = 0;
            if (i != j){
                free(a[j]);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}
int solve7(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    int res_left = 0;
    if (strcmp_(a[1], s) >= 0) j++;
    res_left = (strcmp_(a[0], s) >= 0 ? 1 : 0);
    for (i = 1; i < n - 1; i++){
        int f1 = 0;
        if (res_left && strcmp_(a[i + 1], s) >= 0){
            if (i != j){
                free(a[j]);
                res_left = (strcmp_(a[i], s) >= 0 ? 1 : 0);
                f1 += 1;
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
        if (!f1)
            res_left = (strcmp_(a[i], s) >= 0 ? 1 : 0);
    }
    if (res_left){
        if (i != j){
            free(a[j]);
            a[j] = a[i];
            a[i] = 0;
        }
        j++;
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
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
int dop_funct(const char* buf, const char* s){
    int i, j;
    int cnt = 0;
    for (i = 0; s[i]; i ++){
        int f = 0;
        for (j = 0; s[i + j] && buf[j]; j ++){
            if (!sravnenie_bukv(buf[j], s[i + j])){
                f = 1;
                break;
            }
        }
        if (f == 0 && !buf[j]){
            cnt = 1;
            break;
        }
    }
    return cnt;
}
int solve8(char** a, int n, const char* s){
    int i, k;
    int j = 0;
    int res_left = 0;
    if (strcmp_(a[1], s) >= 0) j++;
    res_left = (dop_funct(a[1], s) == 0 ? 1 : 0);
    for (i = 1; i < n - 1; i++){
        int f1 = 0;
        if (res_left && dop_funct(a[1], s) == 0){
            if (i != j){
                free(a[j]);
                f1 += 1;
                res_left = (dop_funct(a[i], s) == 0 ? 1 : 0);
                a[j] = a[i];
                a[i] = 0;
            }
            j++;
        }
        if (!f1)
        res_left = (dop_funct(a[i], s) == 0 ? 1 : 0);
    }
    if (res_left){
        if (i != j){
            free(a[j]);
            a[j] = a[i];
            a[i] = 0;
        }
        j++;
    }
    for(k = j; k < n; k++){
        if (a[k]){
            free(a[k]);
            a[k] = 0;
        }
    }
    return j;
}