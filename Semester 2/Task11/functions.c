#include "functions.h"

double f0(double x){
    return 1 + 0 * x;;
}

double f1(double x){
    return x - pow(10, 100);
}

double f2(double x){
    return 4 - pow(x, 2);
}

double f3(double x){
    return pow(x, 3) + 3 * pow(x, 2) + 16;
}

double f4(double x){
    return 3 - 2 * pow(x, 2) - pow(x, 4);
}

double f5(double x){
    return sqrtf(fabs(x) + 1) - 2;
}

double f6(double x){
    return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
}

double d0(double x){
    return 0 * x;
}

double d1(double x){
    return 1 + 0 * x;
}

double d2(double x){
    return -2 * x;
}

double d3(double x){
    return 3 * pow(x, 2) + 6 * x;
}

double d4(double x){
    return -4 * x - 4 * pow(x, 3);
}

double d5(double x){
    int sgn = (x < 0) ? -1 : 1;
    return sgn / (2 * sqrt(fabs(x) + 1));
}
double d6(double x){
    int sgn = (x < 0) ? -1 : 1;
    return sgn / (4 * sqrt(sqrt(fabs(x) + 1) + 1) * sqrt(fabs(x) + 1));
}