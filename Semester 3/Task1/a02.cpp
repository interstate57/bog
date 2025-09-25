#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "sortirovki.h"

int data::p = 0;

int main(int argc, char* argv[]){
    int n = 0, sa = 0, m = 0, sb = 0, diff = 0;
    int pa = 0, pb = 0;
    char* name1 = 0;
    char* name2 = 0;
    int task = 2;
    data* a;
    data* b;
    data* c;
    double t;
    FILE* fpa;
    FILE* fpb;
    io_status reta;
    io_status retb;
    int has_formula_1 = 0, has_formula_2 = 0;
    if (argc == 9 || argc == 8 || argc == 7){
        if (!(sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &pa) == 1 && sscanf(argv[3], "%d", &sa) == 1 &&\
        sa >= 0 && sa <= 4)){
            printf("Usage: %s n pa sa [name1] m pb sb [name2]\n", argv[0]);
            return 6;
        }
        else{
            has_formula_1 = (sa != 0);
            if (has_formula_1){
                if (!(sscanf(argv[4], "%d", &m) == 1 && sscanf(argv[5], "%d", &pb) == 1 && sscanf(argv[6], "%d", &sb) == 1 &&\
                sb >= 0 && sb <= 4)){
                    printf("Usage: %s n pa sa [name1] m pb sb [name2]\n", argv[0]);
                    return 6;
                }
                has_formula_2 = (sb != 0); 
            }
            else{
                if (!(sscanf(argv[5], "%d", &m) == 1 && sscanf(argv[6], "%d", &pb) == 1 && sscanf(argv[7], "%d", &sb) == 1 &&\
                sb >= 0 && sb <= 4)){
                    printf("Usage: %s n pa sa [name1] m pb sb [name2]\n", argv[0]);
                    return 6;
                }
                has_formula_2 = (sb != 0);
            }
        }
    }
    else {
        printf("Usage: %s c n pa sa [name1] m pb sb [name2]\n", argv[0]);
        return 6;
    }
    if (!has_formula_1 && !has_formula_2){
        name1 = argv[4];
        name2 = argv[8];
    }
    else if (!has_formula_1 && has_formula_2){
        name1 = argv[4];
    }
    else if (has_formula_1 && !has_formula_2){
        name2 = argv[7];
    }
    data::set_p(pa);
    a = new data[n];
    if (!a){
        printf("Cannot allocate memory!\n");
        return 2;
    }
    if(name1){
        if (!(fpa = fopen(name1, "r"))) {
            delete[] a;
            return ERROR_OPEN;
        }    
        reta = read_array(a, n, name1);
        do{
            switch(reta){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open file!\n"); break;
                case ERROR_READ: printf("Cannot read file!\n"); break;
            }
            delete[] a;
            return 3;
        }while(0);
    }
    else{
        init_array(a, n, sa);
    }
    for (int i = 0; i < n - 1; i ++){
        if (a[i + 1] < a[i]){
            printf("Array a is not an increasing one\n");
            delete[] a;
            return 5;
        }
    }
    print_array(a, n, pa);
    printf("\n");
    data::set_p(pb);
    b = new data[m];
    if (!b){
        printf("Cannot allocate memory!\n");
        delete[] a;
        return 2;
    }
    if(name2){
        if (!(fpb = fopen(name2, "r"))){
            delete[] a;
            delete[] b;
            return ERROR_OPEN;
        } 
        retb = read_array(b, m, name2);
        do{
            switch(retb){
                case SUCCESS: continue;
                case ERROR_OPEN: printf("Cannot open file!\n"); break;
                case ERROR_READ: printf("Cannot read file!\n"); break;
            }
            delete[] a;
            delete[] b;
            return 3;
        }while(0);
    }
    else{
        init_array(b, m, sb);
    }
    for (int i = 0; i < m - 1; i ++){
        if (b[i + 1] < b[i]){
            printf("Array b is not an increasing one\n");
            delete[] a;
            delete[] b;
            return 5;
        }
    }
    print_array(b, m, pb);
    printf("\n");
    data::set_p(pa + pb);
    c = new data[n + m];
    if (!c){
        printf("Cannot allocate memory!\n");
        delete[] a;
        delete[] b;
        return 2;
    }
    t = clock();
    merge(a, b, n, m, c);
    t = (clock() - t) / CLOCKS_PER_SEC;
    print_array(c, n + m, pb + pa);
    diff = difference(c, n + m);
    printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}