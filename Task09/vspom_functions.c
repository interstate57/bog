#include "vspom_functions.h"
double test_1(size_t n, size_t (*p)(const char *), const char *s, size_t *res){
    double t;
    size_t r = 0;
    size_t i;
    t = clock();
    for (i = 0; i < n; i ++){
        r = (*p)(s);
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    *res = r;
    return t;
}
double test_2_5 (size_t n, char* (*p) (char*, const char *), char *s1, const char *s2, char **res){
    double t;
    double t1 = 0;
    char *r = 0;
    size_t i;
    size_t len = strlen(s1) + 1;
    char* per;
    per = (char*)malloc(len * sizeof(char));
    per = strcpy(per, s1);
    t = clock();
    for (i = 0; i < n; i ++){
        s1 = strcpy(s1, per);
        t = clock();
        r = (*p)(s1, s2);
        t1 += clock() - t;
    }
    t1 = t1 / CLOCKS_PER_SEC;
    *res = r;
    free(per);
    return t;
}
double test_3_4 (size_t n, char* (*p) (const char *, int), const char *s, int ch, char **res){
    double t;
    char* r = 0;
    size_t i = 0;
    char* otv = (char *)"Not found";
    t = clock();
    for (; i < n; i ++){
        r = (*p)(s, ch);
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    *res = r;
    if (*res == 0){
        *res = otv;
    }
    return t;
}
size_t strlen_(const char *s){
    size_t i = 0;
    while (s[i]) i ++;
    return i;
}
char *strcpy_(char *s1, const char *s2){
    int i;
    for(i = 0; s2[i]; i ++){
        s1[i] = s2[i];
    }
    s1[i] = 0;
    return s1;
}
char *strchr_ (const char *s, int ch){
    int i;
    for(i = 0; s[i]; i ++){
        if (s[i] == ch){
            return (char *) (s + i);
        }
    }
    return 0;
}
char *strrchr_ (const char *s, int ch){
    int i;
    int k = -1;
    for(i = 0; s[i]; i ++){
        if (s[i] == ch){
            k = i;
        }
    }
    if (k == -1){
        return 0;
    }
    return (char*)(s + k);
}
char *strcat_ (char *s1, const char *s2){
    int i = 0;
    while (s1[i]){
        i++;
    }
    strcpy_(s1 + i, s2);
    return s1;
}