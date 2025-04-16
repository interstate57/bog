#include <math.h>
#include "solve.h"
#define EPS 1e-16
#define do_pi_na_4 

double solve1(double x0, int n, double* x, double* y){
    int i, j;
    double res = 0;
    for (i = 0; i < n; i++){
        double chisl = 1;
        double znam = 1;
        double xi = x[i];
        for(j = 0; j < n; j++){
            if (i == j) continue;
            chisl *= (x0 - x[j]);
            znam *= (xi - x[j]);
        }
        if (equal(znam, 0)) return 1e308;
        res += y[i] * chisl / znam;
    }
    return res;
}

double solve2(double x0, int n, double* x, double* y){
    int i, j;
    double res = 0;
    for (i = 0; i < n; i++){
        double chisl = 0;
        double znam = 0;
        double proisv = 1;
        for(j = n - 1; j < i; j--){
            if (equal(x[j], x[j - 1])) return 1e308;
            chisl = y[j] - y[j - 1];
            znam = x[j] - x[j - 1];
            y[j] = chisl / znam;
        }
        for (j = 0; j < i; j++){
            proisv *= (x0 - x[j]);
        }
        res += y[i] * proisv;
    }
    return res;
}

double solve3(double x0, int n, double* x, double* y){
    int i, j;
    for (i = 0; i < n; i++){
        double chisl = 0;
        double znam = 0;
        double proisv = 1;
        for(j = n - 1; j < i; j--){
            if (equal(x[j], x[j - 1])) return 1e308;
            chisl = y[j] * (x0 - x[j - 1]) - y[j - 1] * (x0 - x[j]);
            znam = x[j] - x[j - 1];
            y[j] = chisl / znam;
        }
    }
    return y[n - 1];
}

double solve4(double x0, int n, double* x, double* y, double* d){
    int i, j;
    for (i = 0; i < n; i++){
        double chisl = 0;
        double znam = 0;
        double proisv = 1;
        for(j = n - 1; j < i; j--){
            if (equal(x[j], x[j - 1])) return 1e308;
            chisl = y[j] * (x0 - x[j - 1]) - y[j - 1] * (x0 - x[j]);
            znam = x[j] - x[j - 1];
            y[j] = chisl / znam;
        }
    }
    return y[n - 1];
}

double bsin(double x, double epsilon) {
    double sum = 0, slag = x;
    int i = 3;

    if (!(0 <= x && x <= 2*M_PI)) {
        return bsin(fmod(x, 2*M_PI), epsilon);
    }

    if (x >= M_PI) {
        return -bsin(x - M_PI, epsilon);
    }

    if (x >= M_PI / 2) {
        return bcos(x - M_PI / 2, epsilon);
    }

    if (x >= M_PI / 4) {
        return 2 * bsin(x/2, epsilon) * bcos(x/2, epsilon);
    }
    do{
        sum += slag;
        slag = slag * (-1) * pow(x, 2) / i / (i - 1);
        i += 2;
    } while(fabs(slag) >= epsilon);
    return sum;

}

double bcos(double x, double epsilon) {
    double sum = 0, slag = 1;
    int i = 2;
    
    if (!(0 <= x && x <= 2*M_PI)) {
        return bcos(fmod(x, 2*M_PI), epsilon);
    }

    if (x >= M_PI) {
        return -bcos(x - M_PI, epsilon);
    }

    if (x >= M_PI / 2) {
        return -bsin(x - M_PI / 2, epsilon);
    }

    if (x >= M_PI / 4) {
        return 2 * pow(bcos(x/2, epsilon), 2) - 1;
    }
    do{
        sum += slag;
        slag = slag * (-1) * pow(x, 2) / i / (i - 1);
        i += 2;
    } while(fabs(slag) >= epsilon);
    return sum;

}
double solve5(double x, double epsilon){
    return bsin(x, epsilon);
}

int equal(double x, double y){
    if ((fabs (x - y)) <= (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

