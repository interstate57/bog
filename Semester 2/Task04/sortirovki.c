#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "sortirovki.h"

int sort1(char* x, char** a, int n, int (*cmp)(const char* , const char*)){
    int inach = 0, ikon = n, s = 0;
    if (cmp(x, a[n - 1]) > 0){
        return n;
    }
    printf("1\n");
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (cmp(x, a[s]) > 0){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}

int sort3 (char* x, char** a, int n, int (*cmp)(const char* , const char*)){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    char* vr = 0;
    while (i <= j){
        while (i < n){
            if (cmp(x, a[i]) >= 0){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (cmp(a[j], x) > 0){
                jnuzh = j;
                break;
            }
            j -= 1;
        }
        if (i <= j){
            vr = a[jnuzh];
            a[jnuzh] = a[inuzh];
            a[inuzh] = vr;
        }
    }
    return i;
}

void sort4 (char** a, int n, int (*cmp)(const char* , const char*)){
    int i, j;
    char* per = 0;
    for (i = 0; i < n; i ++){
        for (j = 0; j < n - 1 - i; j ++){
            if (cmp(a[j + 1], a[j]) > 0){
                per = a[j];
                a[j] = a[j + 1];
                a[j + 1] = per;
            }
        }
    }
}

void sort5 (char** a, int n, int (*cmp)(const char* , const char*)){
    int i, j;
    char* per = 0;
    for (i = 0; i < n - 1; i ++){
        int mini = i;
        char* minch = a[i];
        for (j = i; j < n; j ++){
            if (cmp(minch, a[j]) < 0){
                mini = j;
                minch = a[j];
            }
        }
        per = a[i];
        a[i] = a[mini];
        a[mini] = per;
    }
}

void sort6 (char** a, int n, int (*cmp)(const char* , const char*)){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        char* vr = 0;
        for (j = 0; j < i ; j ++){
            if (cmp(a[i], a[j]) > 0){
                nuzh = j;
                break;
            }
        }
        if (nuzh != -1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}

void sort7 (char** a, int n, int (*cmp)(const char* , const char*)){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1, cmp);
        char* vr = 0;
        if (nuzh != i + 1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}

int binpoisk (char* x, char** a, int n, int (*cmp)(const char* , const char*)){
    int inach = 0, ikon = n, s = 0;
    if (cmp(a[n - 1], x) > 0){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (cmp(a[s], x) > 0){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}

void sort8 (char** a, char** b, int n, int (*cmp)(const char* , const char*)){
    int i;
    int j = 1;
    char** a_orig = a;
    char** c;
    while (j < n){
        for (i = 0; i < n; i += 2 * j){
            if (i + 2 * j >= n){
                if (i + j >= n){
                    merge(a + i, a, n - i, 0, b + i, cmp);
                }
                else{
                    merge(a + i, a + i + j, j, n - i - j, b + i, cmp);
                }
                
            }
            else{
                merge(a + i, a + i + j, j, j, b + i, cmp);
            }
        }
        c = a;
        a = b;
        b = c;
        j *= 2;
    }
    if (a != a_orig){
        for (int k = 0; k < n; k ++){
            a_orig[k] = a[k];
        }
    }
}

void merge (char** a, char** b, int n, int m, char** c, int (*cmp)(const char* , const char*)){
    int i = 0, j = 0, k = 0;
    while (i != n && j != m){
        if (cmp(a[i], b[j]) > 0){
            c[k] = a[i];
            i += 1;
            k += 1;
        }
        else if (cmp(b[j], a[i]) > 0){
            c[k] = b[j];
            j += 1;
            k += 1;
        }
        else{
            c[k] = a[i];
            i += 1;
            k += 1;
        }
    }
    if (i == n){
        for (; j < m; j ++){
            c[k] = b[j];
            k += 1;
        }
    }
    else if (j == m){
        for (; i < n; i ++){
            c[k] = a[i];
            k += 1;
        }
    }
}

void sort9 (char** a, int n, int (*cmp)(const char* , const char*)){
    int i = 0, sr = 0; 
    char* per = 0;
    while (n > 1){
        sr = (n - 1) / 2;
        i = polov_sort(a[sr], a, n, cmp);
        if (i > n - i){
            sort9(a + i, n - i, cmp);
            continue;
        }
        else{
            if (i == 0){
                per = a[i];
                a[i] = a[sr];
                a[sr] = per;
                a += 1;
                n -= 1;
                continue;
            }
            if (i > 0) {
                sort9(a + 0, i, cmp);
                a += i;
                n -= i;
                continue;
            }
        }
    }
}

int polov_sort (char* x, char** a, int n, int (*cmp)(const char* , const char*)){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    char* vr = 0;
    while (i <= j){
        while (i < n){
            if (cmp(x, a[i]) >= 0){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (cmp(a[j], x) > 0){
                jnuzh = j;
                break;
            }
            j -= 1;
        }
        if (i <= j){
            vr = a[jnuzh];
            a[jnuzh] = a[inuzh];
            a[inuzh] = vr;
        }
    }
    return i;
}