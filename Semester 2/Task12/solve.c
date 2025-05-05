#include "solve.h"

int count = 0;

double solve1(double (*f) (double), double x, double h){
    if (equal(h, 0)) return 1e308;
    return (f(x + h) - f(x)) / h;
}

double solve2(double (*f) (double), double x, double h){
    if (equal(h, 0)) return 1e308;
    return (f(x + h) - f(x - h)) / (2 * h);
}

double solve3(double (*f) (double), double x, double h){
    if (equal(h, 0)) return 1e308;
    return (f(x + h) - 2 * f(x) + f(x - h)) / pow(h, 2);
}

double solve4(double (*f) (double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = h * 0.5 * (f(a) + f(b));
    int i;
    for (i = 1; i < n; i++){
        sum += h * f(a + i * h);
    }
    return sum;
}

double solve5(double (*f) (double), double a, double b, int n){
    double h = (b - a) / (2 * n);
    double sum = h * (f(a) + f(b)) / 3;
    double sub_sum = 0;
    int i;
    for (i = 1; i < n; i++){
        sub_sum += f(a + 2 * i * h);
    }
    sum += 2 / 3 * h * sub_sum;
    sub_sum = 0;
    for (i = 0; i < n; i++){
        sub_sum += f(a + (2 * i + 1) * h);
    }
    sum += 4 / 3 * h * sub_sum;
    return sum;
}

double solve6(double (*f) (double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = 2 * f(b) * (2/3 * pow(fabs(a + h * (n - 1)), 3/2) + pow(fabs(b), 3/2) / 3 -\
        (a + h * (n - 1)) * sgn(b) * sqrt(fabs(b)));
    double sub_sum = 0;
    double xi = a;
    int i;
    sum += 2 * f(a) * (2/3 * pow(fabs(a + h), 3/2) + pow(fabs(a), 3/2) / 3 -\
        (a + h) * sgn(a) * sqrt(fabs(a)));
    for (i = 1; i < n; i++){
        xi += h;
        sub_sum += f(xi) * (2/3 * (pow(fabs(xi - h), 3/2) + pow(fabs(xi), 3/2) + pow(fabs(xi + h), 3/2)) - sgn(xi) * sqrt(fabs(xi)) * 2 * xi);
    }
    sum += 2 * sub_sum;
    return sum;
}

double solve7(double (*f) (double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = 0;
    double suma = 0, suma1 = 0, sumb1 = 0, sumb = 0;
    double xi = a + h;
    int i;
    suma = f(a) * ((pow(fabs(a + 2*h), 5/2) * sgn(a + 2*h) - pow(fabs(a), 5/2) * sgn(a)) / (5 * pow(h, 2)) +\
        (sqrt(fabs(a + 2*h)) * sgn(a + 2*h) - sqrt(fabs(a)) * sgn(a)) * (2 + 3 * a / h) -\
        (pow(fabs(a + 2*h), 3/2) - pow(fabs(a), 3/2)) * (1/h + 2 / (3 * pow(h, 2))));
    suma1 = f(a + h) * (-2 / (5 * pow(h, 2)) * (pow(fabs(a + 2*h), 5/2) * sgn(a + 2*h) - pow(fabs(a), 5/2) * sgn(a)) +\
        (1 / (5 * pow(h, 2))) * (pow(fabs(a + 3*h), 5/2) * sgn(a + 3*h) - pow(fabs(a + h), 5/2) * sgn(a + h))-\
        (4 * a / h) * (sqrt(fabs(a + 2*h)) * sgn(a + 2*h) - sqrt(fabs(a)) * sgn(a)) +\
        (sqrt(fabs(a + 3*h)) * sgn(a + 3*h) - sqrt(fabs(a + h)) * sgn(a + h)) * (2 + 3 * (a + h) / h) +\
        (pow(fabs(a + 2*h), 3/2) - pow(fabs(a), 3/2)) * (4 / (3 * h) + 4 * a / (3 * pow(h, 2))) -\
        (pow(fabs(a + 3*h), 3/2) - pow(fabs(a + h), 3/2)) * (1 / h - 2 / (3 * pow(h, 2))));
    sumb1 = f(b - h) * ((1 / (5 * pow(h, 2))) * (pow(fabs(b - h), 5/2) * sgn(b - h) - pow(fabs(b - 3*h), 5/2) * sgn(b - 3*h)) -\
        2 / (5 * pow(h, 2)) * (pow(fabs(b), 5/2) * sgn(b) - pow(fabs(b - 2*h), 5/2) * sgn(b - 2*h)) +\
        (b - 3*h) / h * (sqrt(fabs(b - h)) * sgn(b - h) - sqrt(fabs(b - 3*h)) * sgn(b - 3*h)) -\
        4 * (b - 2*h) / h * (sqrt(fabs(b)) * sgn(b) - sqrt(fabs(b - 2*h)) * sgn(b - 2*h)) -\
        (pow(fabs(b - h), 3/2) - pow(fabs(b - 3*h), 3/2)) * (1 / (3 * h) - 2 * (b - 3*h) / (3 * pow(h, 2))) +\
        (pow(fabs(b), 3/2) - pow(fabs(b - 2*h), 3/2)) * (4 / (3 * h) + 4 * (b - 2*h) / (3 * pow(h, 2))));
    sumb = f(b) * ((1 / (5 * pow(h, 2))) * (pow(fabs(b), 5/2) * sgn(b) - pow(fabs(b - 2*h), 5/2) * sgn(b - 2*h)) +\
        ((b - 2*h) / h) * (sqrt(fabs(b)) * sgn(b) - sqrt(fabs(b - 2*h)) * sgn(b - 2*h)) -\
        (pow(fabs(b), 3/2) - pow(fabs(b - 2*h), 3/2)) * (1 / (3 * h) + 2 * (b - 2*h) / (3 * pow(h, 2))));
    for (i = 2; i < n - 1; i++){
        xi += h;
        sum += f(xi) * ((1 / (5 * pow(h, 2))) * (pow(fabs(xi), 5/2) * sgn(xi) - pow(fabs(xi - 2*h), 5/2) * sgn(xi - 2*h)) -\
        2 / (5 * pow(h, 2)) * (pow(fabs(xi + h), 5/2) * sgn(xi + h) - pow(fabs(xi - h), 5/2) * sgn(xi - h)) +\
        1 / (5 * pow(h, 2)) * (pow(fabs(xi + 2*h), 5/2) * sgn(xi + 2*h) - pow(fabs(xi), 5/2) * sgn(xi)) +\
        (xi - 2*h) / h * (sqrt(fabs(xi)) * sgn(xi) - sqrt(fabs(xi - 2*h)) * sgn(xi - 2*h)) -\
        4 * (xi - h) / h) * (sqrt(fabs(xi + h)) * sgn(xi + h) - sqrt(fabs(xi - h)) * sgn(xi - h) +\
        (sqrt(fabs(xi + 2*h)) * sgn(xi + 2*h) - sqrt(fabs(xi)) * sgn(xi)) * (2 + 3 * xi / h) -\
        (pow(fabs(xi), 3/2) - pow(fabs(xi - 2*h), 3/2)) * (1 / (3 * h) - 2 * (xi - 2*h) / 3 * pow(h, 2)) +\
        (pow(fabs(xi + h), 3/2) - pow(fabs(xi - h), 3/2)) * (4 / (3 * h) + 4 * (xi - h) / (3 * pow(h, 2))) -\
        (pow(fabs(xi + 2*h), 3/2) - pow(fabs(xi), 3/2)) * (1 / h - 2 / (3 * pow(h, 2))));
    }
    sum += suma + suma1 + sumb1 + sumb;
    return sum;
}

int solve8(double (*f) (double), double a, double b, double epsilon, double* r){
    double h = b - a;
    double sst = 0.5 * h * (f(a) + f(b)); 
    double snov = 0, sum = 0;
    int i;
    //int j;
    int it = 0;
    count += 2;
    for(i = 1; a + i*h < b; i++){
        sst += h * f(a + i*h);
        count += 1;
    }
    while(1){
        h *= 0.5;
        if (equal(h, 0)){
            break;
        }
        it += 1;
        //n = (b - a) / h;
        for (i = 0; a + (2*i) * h < b; i++){
            sum += h * f(a + (2*i + 1) * h);
            //printf("1\n");
            count += 1;
        }
        snov = sst * 0.5 + sum;
        //printf("snov = %le, sst = %le, sum = %le\n", snov, sst, sum);
        if (fabs(snov - sst) < epsilon){
            *r = snov;
            return it;
        }
        sum = 0;
        sst = snov;
    }
    return -1;
}

double solve10(double (*f) (double), double a, double epsilon, double* r){
    double s = 0, h = 1;
    double b;
    while (1){
        double I;
        int k;
        b = a + h;
        k = solve8(f, a, b, epsilon, &I);
        if (k < 0) break;
        s += I;
        if (fabs(I) < epsilon){
            *r = s;
            return b;
        }
        a = b;
        h *= 2;
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

int sgn(double x){
    return x < 0 ? -1 : 1;
}