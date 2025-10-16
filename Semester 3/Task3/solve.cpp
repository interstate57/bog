#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "solve.h"

int solve1(student* a, int n){
    int j = 1, k = 0;
    if (n <= 1) return n;
    for (int i = 1; i < n; i++){
        if (k == 0){
            if (a[i] < a[i - 1]){
                k = 0;
                continue;
            }
            else{
                k = 1;
                if (i != j){
                    a[j] = (student&&)a[i];
                }
                j++;
            }
        }
        else{
            if (a[i] < a[j - 1]){
                k = 0;
                continue;
            }
            else{
                k = 1;
                if (i != j){
                    a[j] = (student&&)a[i];
                }
                j++;
            }
        }
    }
    return j;
}


int solve2(student* a, int n){
    int fli = 0;
    if (n < 3) return n;
    int fli2 = (a[2] > a[1] && a[2] > a[0]) ? 1 : 0;
    if (n == 3) return 3 - fli2;
    int fli1 = (a[3] > a[2] && a[3] > a[1]) ? 1 : 0;
    if (n == 4){
        if (fli2){
            if (fli1) return 2;
            else{
                a[2] = (student&&)a[3];
                return 3;
            }
        }
        else{
            return 4 - fli1;
        }
    }
    int j = 2;
    int i;
    for (i = 4; i < n; i++){
        if (a[i] > a[i - 1] && a[i] > a[i - 2]){
            fli = 1;
        }
        else{
            fli = 0;
        }
        //printf("\n");
        //printf("i = %d, fli2 = %d, fli1 = %d, fli = %d, j = %d\n", i, fli2, fli1, fli, j);
        if (fli2 != 1){
            if (i - 2 != j)
                a[j] = (student&&)a[i - 2];
            j++;
        }
        fli2 = fli1;
        fli1 = fli;
        //print_array(a, n, 11);
    }
    if (fli2 == 0){
        if (i - 2 != j)
            a[j] = (student&&)a[i - 2];
        j++;
    }
    if (fli1 == 0){
        if (i - 1 != j)
            a[j] = (student&&)a[i - 1];
        j++;
    }
    //printf("\n");
    return j;
}



int solve3(student* a, int n){
    int j = 1, k = 0;
    int i;
    if (n <= 2) return n;
    for (i = 1; i < n - 1; i++){
        if (k == 0){
            if (a[i] < a[i - 1] && a[i] < a[i + 1]){
                k = 0;
                continue;
            }
            else{
                k = 1;
                if (i != j){
                    a[j] = (student&&)a[i];
                }
                j++;
            }
        }
        else{
            if (a[i] < a[j - 1] && a[i] < a[i + 1]){
                k = 0;
                continue;
            }
            else{
                k = 1;
                if (i != j){
                    a[j] = (student&&)a[i];
                }
                j++;
            }
        }
    }
    if (i != j){
        a[j] = (student&&)a[n - 1];
    }
    j++;
    return j;
}

int solve4(student* a, int n){
    if (n <= 4) return n;
    int fli = 0;
    int fli2 = (a[2] > a[1] && a[2] > a[0] && a[2] > a[3] && a[2] > a[4]) ? 1 : 0;
    if (n == 5){
        if (fli2){
            a[2] = (student&&)a[3];
            a[3] = (student&&)a[4];
            return 4;
        }
        else return n;
    }
    int fli1 = (a[3] > a[2] && a[3] > a[1] && a[3] > a[4] && a[3] > a[5]) ? 1 : 0;
    int j = 2;
    int i;
    for (i = 4; i < n - 2; i++){
        if (a[i] > a[i - 1] && a[i] > a[i - 2] && a[i] > a[i + 1] && a[i] > a[i + 2]){
            fli = 1;
        }
        else{
            fli = 0;
        }
        //printf("\n");
        //printf("i = %d, fli2 = %d, fli1 = %d, fli = %d, j = %d\n", i, fli2, fli1, fli, j);
        if (fli2 != 1){
            if (i - 2 != j)
                a[j] = (student&&)a[i - 2];
            j++;
        }
        fli2 = fli1;
        fli1 = fli;
        //print_array(a, n, 11);
    }
    if (n == 5){
        if (fli2){
            a[2] = (student&&)a[3];
            a[3] = (student&&)a[4];
            return 4;
        }
        else return n;
    }
    if (n == 6){
        if (fli2){
            if (fli1){
                a[2] = (student&&)a[4];
                a[3] = (student&&)a[5];
                return 4;
            }
            else{
                a[2] = (student&&)a[3];
                a[3] = (student&&)a[4];
                a[4] = (student&&)a[5];
                return 5;
            }
        }
        else{
            if (fli1){
                a[3] = (student&&)a[4];
                a[4] = (student&&)a[5];
                return 5;
            }
            else{
                return 6;
            }
        }
    }
    if (fli2 == 0){
        if (i - 2 != j)
            a[j] = (student&&)a[i - 2];
        j++;
    }
    if (fli1 == 0){
        if (i - 1 != j)
            a[j] = (student&&)a[i - 1];
        j++;
    }
    for (; i < n; i++){
        if (j != i)
            a[j] = (student&&)a[i];
        j++;
    }
    //printf("\n");
    return j;
}

int solve6(student *a, int n, student &x){
    int i;
    int j = 0;
	if (n == 0) return 0;
	for (i = 0; i < n; i++){
		if (a[i] >= x){
			if (j != i)
				a[j] = (student &&)a[i];
			j++;
		}
	}
	return j;
}

int solve7(student *a, int n, student &x){
    int i;
    int j = 0, k = 0;
	if (n == 0) return 0;
    for (i = 0; i < n; i++){
		if (a[i] < x && k == 0){
			k = 1;
            if (j != i)
				a[j] = (student &&)a[i];
            j++;
		}
        else if (a[i] >= x){
            if (j != i)
				a[j] = (student &&)a[i];
			j++;
            k = 0;
        }
	}
    return j;
}

int solve8(student *a, int n, student &x){
    int i;
    int j = 0, k = 0;
	if (n == 0) return 0;
    for (i = 0; i < n; i++){
		if (a[i] < x && k == 0){
			k = 1;
            if (j != i)
				a[j] = (student &&)a[i];
            j++;
		}
        else if (a[i] >= x){
            if (k == 2){
                if (j != i-1)
                    a[j] = (student &&)a[i-1];
                j++;
            }
            if (j != i)
				a[j] = (student &&)a[i];
			j++;
            k = 0;
        }
        else{
            if (k == 1) k = 2;
        }
	}
    if (k == 2){
        if (j != i-1)
            a[j] = (student &&)a[i-1];
        j++;
    }
    return j;
}

int solve9(student *a, int n, student &x){
    int i;
    int j = 1;
    if (n <= 1) return n;
    if (n == 2){
        if (a[1] < x){
            if (a[0] < x) return 0;
            else{
                a[0] = (student&&)a[1];
                return 1;
            }
        }
        else{
            return 2 - ((a[0] < x) ? 1 : 0); 
        }
    }
    int fl_pred = (a[0] < x) ? 1 : 0;
    for (i = 1; i < n - 1; i++){
		if (fl_pred || a[i + 1] < x){
            fl_pred = (a[i] < x) ? 1 : 0;
        }
        else{
            fl_pred = (a[i] < x) ? 1 : 0;
            if (j != i)
				a[j] = (student &&)a[i];
			j++;
        }
	}
    if (i != j){
        a[j] = (student&&)a[n - 1];
    }
    j++;
    return j;
}

int solve10(student *a, int n, student &x){
    int i;
    int j = 0, k = 0;
	if (n == 0) return 0;
    for (i = 1; i < n; i++){
		if (a[i] > a[i - 1]){
			k = 1;
		}
        else{
            if (k == 1){
                if (a[i - 1] >= x){
                    j = i - 1;
                }
            }
            else{
                if (j != i )
                    a[j] = (student&&)a[i];
                j++;
            }
            k = 0;
        }
	}
    if (k == 1){
        if (a[i - 1] >= x){
            j = i - 1;
        }
    }
    else{
        if (j != i - 1)
            a[j] = (student&&)a[i - 1];
        j++;
    }
    return j;
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