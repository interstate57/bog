#include "functions.h"

double f0(double x){
    return 1 + 0 * x;
}

double f1(double x){
    return 1 + x;
}

double f2(double x){
    return 1 + x + pow(x, 2);
}

double f3(double x){
    return 1 + x + pow(x, 2) + pow(x, 3);
}

double f4(double x){
    return 1 + x + pow(x, 2) + pow(x, 3) + pow(x, 4);
}

double f5(double x){
    return pow(M_E, -x);
}

double f6(double x){
    return 1 / (25 * pow(x, 2) + 1);
}
