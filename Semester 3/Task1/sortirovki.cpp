#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "data.h"
#include "sortirovki.h"

int sort1(const data& x, data* a, int n){
    int inach = 0, ikon = n, s = 0;
    if (x > a[n - 1]){
        return n;
    }
    while (inach != ikon){
        s = (inach + ikon) / 2;
        if (x > a[s]){
            inach = s + 1;
            printf("nach : %d\n", inach);
        }
        else{
            ikon = s;
            printf("kon : %d\n", ikon);
        }
    }
    return inach;
}


int sort3 (data* a, int n, int m){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    data vr;
    data am = a[m];
    while (i <= j){
        while (i < n){
            if (am < a[i]){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (am >= a[j]){ //***
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

void sort4 (data* a, int n){
    int i, j;
    data per;
    for (i = 0; i < n; i ++){
        for (j = 0; j < n - 1 - i; j ++){
            if (a[j + 1] < a[j]){
                per = a[j];
                a[j] = a[j + 1];
                a[j + 1] = per;
            }
        }
    }
}

void sort5 (data* a, int n){
    int i, j;
    data per;
    for (i = 0; i < n - 1; i ++){
        int mini = i;
        data minch = a[i];
        for (j = i; j < n; j ++){
            if (minch > a[j]){
                mini = j;
                minch = a[j];
            }
        }
        per = a[i];
        a[i] = a[mini];
        a[mini] = per;
    }
}

void sort6 (data* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = -1;
        data vr;
        for (j = 0; j < i ; j ++){
            if (a[i] < a[j]){
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

void sort7 (data* a, int n){
    int i, j;
    for (i = 1; i < n; i ++){
        int nuzh = binpoisk(a[i], a, i + 1);
        data vr;
        if (nuzh != i + 1){
            vr = a[i];
            for (j = i; j > nuzh; j --){
                a[j] = a[j - 1];
            }
            a[nuzh] = vr;
        }
    }
}

int binpoisk (data x, data* a, int n){
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

void sort8 (data* a, data* b, int n){
    int i;
    int j = 1;
    data* a_orig = a;
    data* c;
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
            a_orig[k] = a[k];
        }
    }
}

void merge (data* a, data* b, int n, int m, data* c){
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

void sort9 (data* a, int n){
    int i = 0, sr = 0; 
    data per;
    while (n > 1){
        sr = (n - 1) / 2;
        i = polov_sort(a[sr], a, n);
        if (i > n - i){
            sort9(a + i, n - i);
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
                sort9(a + 0, i);
                a += i;
                n -= i;
                continue;
            }
        }
    }
}

int polov_sort (data x, data* a, int n){
    int inuzh = 0, jnuzh = n - 1;
    int i = 0, j = n - 1;
    data vr;
    while (i <= j){
        while (i < n){
            if (x <= a[i]){
                inuzh = i;
                break;
            }
            i += 1;
        }
        while (j > -1){
            if (a[j] < x){
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

io_status read_array(data* a, int n, const char* name){
    FILE* fp = 0;
    int i;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    for (i = 0; i < n; i++){
        int resai = 0;
        resai = a[i].read(fp);
        if (resai != 0) return ERROR_READ;
    }
    fclose(fp);
    return SUCCESS;
}

int difference(data* a, int n){
    int cnt = 0;
    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]){
            cnt += 1;
        }
    }
    return cnt;
}

void print_array(data* a, int n, int p){
    int min = (n < p ? n : p);
    for (int i = 0; i < min; i++){
        a[i].print();
    }
}

void init_array(data* a, int n, int s){
    for (int i = 0; i < n; i++){
        a[i].init(s, n, i);
    }
}