#include "vspom_functions.h"
size_t strlen_(const char *s){
    size_t i = 0;
    while (s[i]) i ++;
    return i;
}
char *strcpy_(char *s1, const char *s2){
    char * initial = s1;
    while ((*(s1++) = *(s2++))) {};
    return initial;
}
char *strchr_ (const char *s, int ch){
    for (; *s; s++) {
        if (*s == ch)
            return (char *) s;
    }
    return (ch == 0) ? (char *) s : 0;
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
        return (ch == 0) ? (char *) (s + i) : 0;
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
char *strstr_ (const char *s1, const char *s2){
    size_t i, j;
    /*if (!*s1 && !*s2){
        return (char*)s1;
    }*/
    if (!*s2)
        return (char *) s1;

    for (i = 0; s1[i]; i ++){
        int f = 0;
        for (j = 0; s1[i + j] && s2[j]; j ++){
            if (s2[j] != s1[i + j]){
                f = 1;
                break;
            }
        }
        if (f == 0 && !s2[j]){
            return (char*)(s1 + i);
        }
    }
    return 0;
}
char *strtok_r_ (char *str, const char *delim, char **saveptr){
    char a[256];
    size_t i, j, nach;
    int f = 1;
    for (i = 0; i < 256; i ++) a[i] = 0;
    for (i = 0; delim[i]; i ++)
        a[(unsigned char) delim[i]] = 1;
    for (i = 0; str[i]; i ++){
        if (a[(unsigned char) str[i]] == 0){
            f = 0;
            break;
        }
    }
    if (f == 1){
        return NULL;
    }   
    nach = i;
    for (j = i; str[j]; j ++){
        if (a[(unsigned char) str[j]] == 1){
            break;
        }
    }
    *saveptr = str + j + 1;
    return str + nach;
}
