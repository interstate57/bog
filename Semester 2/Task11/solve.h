#pragma once

#include <stdio.h>
#include <math.h>

#define EPS 1e-16

int solve1(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve2(double (*f) (double), double (*d) (double), double x0, double epsilon, int m, double* x);

int solve3(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve4(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve5(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve7(double (*f) (double), double x0, double epsilon, int m, double* x);

int solve8(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve9(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve10(double (*f) (double), double a, double b, double epsilon, int m, double* x);

double golden_section(void);

int equal(double x, double y, double epsilon);

double min(double a, double b);

double max(double a, double b);

int time_to_stop(double start, double end, double curr);

int zn_equal(double a, double b);