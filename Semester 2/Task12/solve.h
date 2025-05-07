#pragma once

#include <stdio.h>
#include <math.h>

#define EPS 1e-16

double solve1(double (*f) (double), double x, double h);

double solve2(double (*f) (double), double x, double h);

double solve3(double (*f) (double), double x, double h);

double solve4(double (*f) (double), double a, double b, int n);

double solve5(double (*f) (double), double a, double b, int n);

double solve6(double (*f) (double), double a, double b, int n);

double solve7(double (*f) (double), double a, double b, int n);

int solve8(double (*f) (double), double a, double b, double epsilon, double* r);

int solve9(double (*f) (double), double a, double b, double epsilon, double* r);

double solve10(double (*f) (double), double a, double epsilon, double* r);

double solve11(double (*f) (double), double a, double epsilon, double* r);

int equal(double x, double y);

int sgn(double x);