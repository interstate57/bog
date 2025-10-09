#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "student.h"
#include "sortirovki.h"

int sort1(const student& x, student* a, int n){
    int inach = 0, ikon = n, s = 0;
    if (x > a[n - 1]){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (x > a[s]){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}


int sort3 (student* a, int n, int m){
    return polov_sort(a[m], a, n);
}

void sort4 (student* a, int n){
    int i, j;
    student per;
    for (i = 0; i < n; i ++){
        for (j = 0; j < n - 1 - i; j ++){
            if (a[j + 1] < a[j]){
                per = (student&&)a[j];
                a[j] = (student&&)a[j + 1];
                a[j + 1] = (student&&)per;
            }
        }
    }
}

void sort5_old (student* a, int n){
    int i, j;
    student per;
    for (i = 0; i < n - 1; i ++){
        int mini = i;
        student minch = a[i];
        for (j = i; j < n; j ++){
            if (minch > a[j]){
                mini = j;
                minch = (student&&)a[j];
            }
        }
        per = (student&&)a[i];
        a[i] = (student&&)a[mini];
        a[mini] = (student&&)per;
    }
}

void sort5 (student* a, int n){
    int i, j;
    student per;
    for (i = 0; i < n - 1; i ++){
        int mini = i;
        for (j = i; j < n; j ++){
            if (a[mini] > a[j]){
                mini = j;
            }
        }
        per = (student&&)a[i];
        a[i] = (student&&)a[mini];
        a[mini] = (student&&)per;
    }
}

void sort6 (student* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        student vr;
        for (j = 0; j < i ; j ++){
            if (a[i] < a[j]){
                nuzh = j;
                break;
            }
        }
        if (nuzh != -1){
            vr = (student&&)a[i];
            for (j = i; j > nuzh; j --){
                a[j] = (student&&)a[j - 1];
            }
            a[nuzh] = (student&&)vr;
        }
    }
}

void sort7 (student* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1);
        student vr;
        if (nuzh != i + 1){
            vr = (student&&)a[i];
            for (j = i; j > nuzh; j --){
                a[j] = (student&&)a[j - 1];
            }
            a[nuzh] = (student&&)vr;
        }
    }
}

int binpoisk (student x, student* a, int n){
    int inach = 0, ikon = n, s = 0;
    if (a[n - 1] < x){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (a[s] < x){
            inach = s + 1;
        }
        else{
            ikon = s;
        }
    }
    return inach;
}

void sort8 (student* a, student* b, int n){
    int i;
    int j = 1;
    student* a_orig = a;
    student* c;
    while (j < n){
        for (i = 0; i < n; i += 2 * j){
            if (i + 2 * j >= n){
                if (i + j >= n){
                    merge(a + i, a, n - i, 0, b + i);
                }
                else{
                    merge(a + i, a + i + j, j, n - i - j, b + i);
                }
                
            }
            else{
                merge(a + i, a + i + j, j, j, b + i);
            }
        }
        c = a;
        a = b;
        b = c;
        j *= 2;
    }
    if (a != a_orig){
        for (int k = 0; k < n; k ++){
            a_orig[k] = (student&&)a[k];
        }
    }
}

void merge (student* a, student* b, int n, int m, student* c){
    int i = 0, j = 0, k = 0;
    while (i != n && j != m){
        if (a[i] < b[j]){
            c[k] = a[i];
            i += 1;
            k += 1;
        }
        else if (b[j] < a[i]){
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

void sort9 (student* a, int n){
    int i = 0, sr = 0; 
    student per;
    while (n > 1){
        i = 0;
        sr = n / 2;
        i = polov_sort(a[sr], a, n);
        if (i > n - i && n - i - 1 > 1){
            sort9(a + i + 1, n - i - 1);
            n = i;
            continue;
        }
        else{
            if (i == 0){
                a += 1;
                n -= 1;
                continue;
            }
            if (i > 0) {
                sort9(a + 0, i);
                a = a + i + 1;
                n = n - i - 1;
                continue;
            }
        }
    }
}

int polov_sort (student x, student* a, int n){
    int i = 0, j = n - 1;
    student vr;
    while (i < j){
        while (i < n - 1){
            if (x <= a[i]){
                break;
            }
            i += 1;
        }
        while (j > 0){
            if (a[j] <= x){
                break;
            }
            j -= 1;
        }
        if (i < j){
            if (a[i] == a[j]){
                i++;
            } else {
                vr = (student&&)a[j];
                a[j] = (student&&)a[i];
                a[i] = (student&&)vr;
            }
        }
    }
    return i;
}

io_status read_array(student* a, int n, const char* name){
    FILE* fp = 0;
    io_status res;
    int i;
    if (!(fp = fopen(name, "r"))) return io_status::wrong_file;
    for (i = 0; i < n; i++){
        res = a[i].read(fp);
        if (res != io_status::success) return res;
    }
    fclose(fp);
    return io_status::success;
}

int difference(student* a, int n){
    int cnt = 0;
    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]){
            cnt += 1;
        }
    }
    return cnt;
}

void print_array(student* a, int n, int p){
    int min = (n < p ? n : p);
    for (int i = 0; i < min; i++){
        a[i].print();
    }
}

void init_array(student* a, int n, int s){
    for (int i = 0; i < n; i++){
        a[i].init_f(f(s, n, i + 1));
    }
}

int f(int s, int n, int i){
    int res = 0;
    switch(s){
            case 1: res = i; break;
            case 2: res = n - i; break;
            case 3: res = i / 2; break;
            case 4: res = n - i / 2; break;
        }
    return res;
}   