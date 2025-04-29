#include "solve.h"

int count = 0;

int solve1(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double c;
    double f_a = f(a), f_b = f(b);
    count += 2;
    if (f_a * f_b > 0) return -1;
    for (it = 0; it < m; it++){
        double f_c;
        c = (a + b) * 0.5;
        f_c = f(c);
        count += 1;
        if (f_c * f_a < 0){
            b = c;
            f_b = f_c;
        }
        else if (f_b * f_c < 0){
            a = c;
            f_a = f_c;
        }
        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (fabs(b - a) < epsilon)
            break;
    }
    return -1;
}

int solve2(double (*f) (double), double (*d) (double), double x0, double epsilon, int m, double* x){
    int it;
    double f_x0 = f(x0);
    double d_x0 = d(x0);
    count += 1;
    for (it = 0; it < m; it++){
        if (equal(d_x0, 0)) return -1;
        x0 = x0 - f_x0 / d_x0;
        f_x0 = f(x0);
        count += 1;
        d_x0 = d(x0);
        if (fabs(f_x0) < epsilon){
            *x = x0;
            return it;
        }
    }
    return -1;
}

int solve3(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double c;
    double f_a = f(a), f_b = f(b);
    int sgn = (f_a * f_b > 0 ? 1 : -1);
    count += 2;
    if (sgn > 0) return -1;
    for (it = 0; it < m; it++){
        double f_c;
        if (equal(f_b - f_a, 0)) return -1;
        c = a - f_a * (b - a) / (f_b - f_a);
        f_c = f(c);
        //printf("a = %le, b = %le, f_a = %le, f_b = %le, c = %le, f_c = %le\n", a, b, f_a, f_b, c, f_c);
        count += 1;
        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (f_c * f_a > 0){
            a = c;
            f_a = f_c;
        }
        else if (f_c * f_b > 0){
            b = c;
            f_b = f_c;
        }
        if (fabs(b - a) < epsilon)
            break;
    }
    return -1;
}

/*int solve3(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double c;
    double f_a = f(a), f_b = f(b);
    count += 2;
    if (f_a * f_b > 0) return -1;
    for (it = 0; it < m; it++){
        if (equal(f_b - f_a, 0)) return -1;
        c = a - f_a * (b - a) / (f_b - f_a);
        double f_c = f(c);
        count += 1;
        double min1 = min(min(a, b), c);
        double min2 = a + b + c - min1 - max(max(a, b), c);
        if (equal(f_a, f_b) || !equal(min1, f_c) && !(min2, f_c)) return -1;
        if (equal(f_c, min1)){
            if (equal(f_a, min2)){
                b = a;
                f_b = f_a;
            }
            a = c;
            f_a = f_c;
        }
        else if (equal(f_c, min2)){
            if (equal(f_b, min1)){
                a = b;
                f_a = f_b;
            }
            b = c;
            f_b = f_c;
        }
        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (fabs(b - a) < epsilon)
            break;
    }
    return -1;
}

*/
int solve4(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double c;
    double f_a, f_b;
    double temp;
    count += 2;
    
    if (b > a) {
        temp = a;
        a = b;
        b = temp;
    }
    f_a = f(a);
    f_b = f(b);
    for (it = 0; it < m; it++){
        double f_c;
        if (equal(f_a - f_b, 0)) return -1;
        c = b - f_b * (a - b) / (f_a - f_b);
        f_c = f(c);
        count += 1;

        if (f_c >= f(a)) {
            return -1;
        }

        if (f_c >= f(b)) {
            a = c;
            f_a = f_c;
        }
        else {
            a = b;
            f_a = f_b;
            b = c;
            f_b = f_c;
        }

        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (fabs(b - a) < epsilon)
            break;
    }
    return -1;
}

int equal(double x, double y){
    if ((fabs (x - y)) <= (EPS  * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}

double min(double a, double b){
    return (a < b ? a : b);
}

double max(double a, double b){
    return (a < b ? b : a);
}