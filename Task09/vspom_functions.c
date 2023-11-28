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
    char *r = 0;
    size_t i;
    size_t len = strlen_(s1);
    t = clock();
    for (i = 0; i < n; i ++){
        s1[len] = 0;
        r = (*p)(s1, s2);
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    *res = r;
    return t;
}
size_t strlen_(const char *s){
    size_t i = 0;
    while (s[i]) i ++;
    return i;
}
char *strcpy_(char *s1, const char *s2){
    while ((*(s1 ++) = *(s2 ++)));
    return s1;
}