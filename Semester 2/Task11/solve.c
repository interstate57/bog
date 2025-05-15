#include "solve.h"

int count = 0;

int solve1(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it = 0;
    double c;
    double f_a = f(a), f_b = f(b);
    count += 2;
    if (fabs(f_a) < epsilon){
        *x = a;
        return it;
    }
    if (fabs(f_b) < epsilon){
        *x = b;
        return it;
    }
    if (zn_equal(f_a, f_b)){
        return -1;
    }
    for (it = 0; it < m; it++){
        double f_c;
        c = (a + b) * 0.5;
        f_c = f(c);
        count += 1;
        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (!zn_equal(f_a, f_c)){
            b = c;
            f_b = f_c;
        }
        else if (!zn_equal(f_b, f_c)){
            a = c;
            f_a = f_c;
        }
        if (fabs(b - a) < epsilon){
            *x = c;
            return it;
        }
    }
    return -1;
}

int solve2(double (*f) (double), double (*d) (double), double x0, double epsilon, int m, double* x){
    int it;
    double f_x0 = f(x0);
    double d_x0 = d(x0);
    count += 1;
    for (it = 0; it < m; it++){
        if (equal(d_x0, 0, epsilon)) return -1;
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
    count += 2;
    if (fabs(f_a) < epsilon){
        *x = a;
        return 0;
    }
    if (fabs(f_b) < epsilon){
        *x = b;
        return 0;
    }
    if (zn_equal(f_a, f_b)){
        return -1;
    }
    for (it = 0; it < m; it++){
        double f_c;
        if (equal(f_b - f_a, 0, epsilon)) return -1;
        c = a - f_a * (b - a) / (f_b - f_a);
        f_c = f(c);
        //printf("a = %le, b = %le, f_a = %le, f_b = %le, c = %le, f_c = %le\n", a, b, f_a, f_b, c, f_c);
        count += 1;
        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (zn_equal(f_a, f_c)){
            if (equal(a, c, epsilon)){
                *x = c;
                return it;
            }
            a = c;
            f_a = f_c;
        }
        else{
            if (equal(b, c, epsilon)){
                *x = c;
                return it;
            }
            b = c;
            f_b = f_c;
        }
        if (fabs(b - a) < epsilon){
            *x = a;
            return it;
        }
    }
    return -1;
}
/*
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
}*/


int solve4(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double c;
    double f_a, f_b;
    f_a = f(a);
    f_b = f(b);
    count += 2;
    if (!zn_equal(f_a, f_b)) return solve3(f, a, b, epsilon, m, x);
    for (it = 0; it < m; it++){
        double f_c;
        if (equal(f_b - f_a, 0, epsilon)) return -1;
        c = a - f_a * (b - a) / (f_b - f_a);
        f_c = f(c);
        count += 1;

        if (f_c >= f(b)) {
            a = b;
            f_a = f_b;
            b = c;
            f_b = f_c;
        }

        if (f_c >= f(a)) {
            a = c;
            f_a = f_c;
        }
        else {
            return -1;
        }

        if (fabs(f_c) < epsilon){
            *x = c;
            return it;
        }
        if (fabs(b - a) < epsilon){
            *x = b;
            return it;
        }    
    }
    return -1;
}

int solve5(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double x1 = a, x2 = (a + b) / 2, x3 = b;
    double y1 = f(x1), y2 = f(x2), y3 = f(x3);
    double x4, y4;
    count += 3;
    printf("x1 = %le, x2 = %le, x3 = %le\n", x1, x2, x3);
    printf("y1 = %le, y2 = %le, y3 = %le\n", y1, y2, y3);
    for (it = 0; it < m; it++){
        double Max = max(max(y1, y2), y3);
        if (equal(y1, y2, epsilon) || equal(y1, y3, epsilon) || equal(y2, y3, epsilon)){
            return -1;
        }
        x4 = x1 + (x1 - x2) * (-y1) / (y1 - y2) + ((x2 - x3) / (y2 - y3) - (x1 - x2) / (y1 - y2)) * y1 * y2 / (y3 - y1);
        y4 = f(x4);
        //printf("x1 = %le, y1 = %le, x2 = %le, y2 = %le, x3 = %le, y3 = %le, x4 = %le, y4 = %le\n", x1, y1, x2, y2, x3, y3, x4, y4);
        count += 1;
        if (fabs(y4) > Max){
            printf("1\n");
            return -1;
        }
        if (fabs(y4) < epsilon){
            *x = x4;
            return it;
        }
        if (equal(y1, Max, epsilon)){
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
            x3 = x4;
            y3 = y4;
        }
        else if (equal(y2, Max, epsilon)){
            x2 = x3;
            y2 = y3;
            x3 = x4;
            y3 = y4;
        }
        else if (equal(y3, Max, epsilon)){
            x3 = x4;
            y3 = y4;
        }
        printf("x1 = %le, x2 = %le, x3 = %le, x4 = %le\n", x1, x2, x3, x4);
        printf("y1 = %le, y2 = %le, y3 = %le, y4 = %le\n", y1, y2, y3, y4);
    }
    return -1; 
}

int solve7(double (*f) (double), double x0, double epsilon, int m, double* x){
    double f_x0 = f(x0);
    int it;
    count += 1;
    for (it = 0; it < m; it++){
        x0 = f_x0;
        f_x0 = f(x0);
        count += 1;
        if (fabs(f_x0 - x0) < epsilon){
            *x = f_x0;
            return it;
        }
    }
    return -1;
}

int solve8(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    double h = (b - a) * 0.1;
    double x_curr = a;
    double f_x_curr;
    int it, i;
    double nach = a;
    double kon = b;
    for (it = 0; it < m; it++){
        f_x_curr = f(nach);
        count += 1;
        //for (x_curr = nach + h; !time_to_stop(nach, kon, x_curr); x_curr += h){
        for (x_curr = nach + h, i = 0; i < 10; x_curr += h, i++) {
            double new_f_x_curr = f(x_curr);
            count += 1;
            //printf("f_x_curr = %le, x_curr = %le, new_f_x_curr = %le, difference: %le\n", f_x_curr, x_curr, new_f_x_curr, new_f_x_curr - f_x_curr);
            if (new_f_x_curr < f_x_curr){
                break;
            }
            f_x_curr = new_f_x_curr;
        }
        if (fabs(kon - nach) < epsilon){
            *x = nach;
            return it;
        }
        if (i == 10){
            nach = x_curr - h;
            kon = x_curr - 2 * h;
        }
        else{
            if (equal(nach, x_curr - h, epsilon)){
                nach = x_curr;
                kon = x_curr - h;
            }
            else{
                nach = x_curr;
                kon = x_curr - 2 * h;
            }      
        }
        //if (fabs(h) < epsilon) return -1;
        h = (kon - nach) / 10;
        
    }
    return -1;
}

int solve9(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double x1, x2, f_x1, f_x2;
    double alpha = golden_section();
    x1 = alpha * a + (1 - alpha) * b;
    x2 = alpha * b + (1 - alpha) * a;
    f_x1 = f(x1);
    f_x2 = f(x2);
    count += 2;
    for (it = 0; it < m; it++){
        if (f_x1 <= f_x2){
            a = x1;
            x1 = x2;
            f_x1 = f_x2;
            x2 = alpha * b + (1 - alpha) * a;
            f_x2 = f(x2);
        }
        else{
            b = x2;
            x2 = x1;
            f_x2 = f_x1;
            x1 = alpha * a + (1 - alpha) * b;
            f_x1 = f(x1);
        }
        count += 1;
        if (fabs(b - a) < epsilon){
            *x = x1;
            return it;
        }
    }
    return -1;
}

int solve10(double (*f) (double), double a, double b, double epsilon, int m, double* x){
    int it;
    double x1 = a, x2 = (a + b) / 2, x3 = b;
    double y1 = f(x1), y2 = f(x2), y3 = f(x3);
    double x4, y4;
    count += 3;
    for (it = 0; it < m; it++){
        double Min = min(y1, y3);
        double B; 
        double A; 
        if (fabs(x1 - x2) < epsilon || fabs(x2 - x3) < epsilon){
            *x = x2;
            return it;
        }
        if (fabs(x1 - x3) < epsilon){
            *x = x1;
            return it;
        }
        B = (y1 - y2) / (x1 - x2) - ((y2 - y3) / (x2 - x3) - (y1 - y2) / (x1 - x2)) * (x1 + x2) / (x3 - x1);
        A = ((y2 - y3) / (x2 - x3) - (y1 - y2) / (x1 - x2)) / (x3 - x1);
        if (equal(A, 0, epsilon)){
            return -1;
        }
        x4 = -1 * B / (2 * A);
        y4 = f(x4);
        //printf("x1 = %le, y1 = %le, x2 = %le, y2 = %le, x3 = %le, y3 = %le, x4 = %le, y4 = %le\n", x1, y1, x2, y2, x3, y3, x4, y4);
        count += 1;
        if (y4 < Min){
            return -1;
        }
        if (equal(Min, y1, epsilon)){
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
            x3 = x4;
            y3 = y4;
        }
        else{
            x3 = x4;
            y3 = y4;
        }
        
    }
    return -1; 
}

double golden_section(void){
    return (sqrt(5) - 1) * 0.5;
}

int equal(double x, double y, double epsilon){
    if ((fabs (x - y)) <= (epsilon  * (fabs (x) + fabs (y)))){
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

int zn_equal(double a, double b){
    return ((a > 0 && b < 0) || (a < 0 && b > 0)) ? 0 : 1;
}