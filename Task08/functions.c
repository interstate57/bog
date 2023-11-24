#include "functions.h"
#include "array_io.h"
#include <math.h>
int equal(double x, double y){
    if ((fabs (x - y)) < (EPS * (fabs (x) + fabs (y)))){
        return 1;
    }
    else{
        return 0;
    }
}
int ubuvanie(double x, double y){
    if (x > y)
        return 1;
    else if (x < y)
        return -1;
    return 0;
}
int vosrastanie(double x, double y){
    if (x < y)
        return 1;
    else if (x > y)
        return -1;
    return 0;
}