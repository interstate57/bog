#pragma once

#include <stdio.h>
#include <math.h>

#define EPS 1e-16

int solve1(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve2(double (*f) (double), double (*d) (double), double x0, double epsilon, int m, double* x);

int solve3(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve4(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int solve8(double (*f) (double), double a, double b, double epsilon, int m, double* x);

int equal(double x, double y);

double min(double a, double b);

double max(double a, double b);