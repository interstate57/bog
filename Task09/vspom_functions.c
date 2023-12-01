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
    size_t len = strlen(s1) + 1;
    printf("%zu\n", len);
    t = clock();
    for (i = 0; i < n; i ++){
        s1[len] = 0;
        r = (*p)(s1, s2);
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    *res = r;
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
double test_6 (size_t n, int (*p) (const char*, const char *), const char *s1, const char *s2, int *res){
    double t;
    int r = 0;
    size_t i = 0;
    t = clock();
    for (; i < n; i ++){
        r = (*p)(s1, s2);
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    *res = r;
    return t;
}
double test_7_8 (size_t n, size_t (*p) (const char*, const char *), const char *s1, const char *s2, size_t *res){
    double t;
    size_t r = 0;
    size_t i = 0;
    t = clock();
    for (; i < n; i ++){
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
int strcmp_ (const char *s1, const char *s2){
    size_t i = 0;
    while (s1[i] != 0 && s2[i] != 0){
        if (s1[i] > s2[i]){
            return 1;
        }
        else if (s2[i] > s1[i]){
            return -1;
        }
        i += 1;
    }
    if (s1[i] == 0 && s2[i] == 0){
        return 0;
    }
    else if (s1[i] == 0){
        return -1;
    }
   return 1;
}
size_t strcspn_ (const char *s1, const char *s2){
    char a[256];
    size_t i;
    for (i = 0; i < 256; i ++) a[i] = 0;
    for (i = 0; s2[i]; i ++)
        a[(unsigned char) s2[i]] = 1;
    for (i = 0; s1[i]; i ++){
        if (a[(unsigned char) s1[i]]){
            return i;
        }
    }
    return i;
}
size_t strspn_ (const char *s1, const char *s2){
    char a[256];
    size_t i;
    for (i = 0; i < 256; i ++) a[i] = 0;
    for (i = 0; s2[i]; i ++)
        a[(unsigned char) s2[i]] = 1;
    for (i = 0; s1[i]; i ++){
        if (a[(unsigned char) s1[i]] == 0){
            return i;
        }
    }
    return i;
}