#pragma once

double solve1(double* a, double* x, double* xm, int n, int m);
void solve2(double* a, double* x, double* b, double* xm, int n, int m, double tau);
int solve3(double* a, int m, int n);
int solve4(double* a, int m, int n);
int solve5(double* a, int m, int n);
int solve6(double* a, int m, int n);
int solve7(double* a, int m, int n);
int solve8(double* a, int m, int n);
int solve9(double* a, int m, int n);
int solve10(double* a, int m, int n);

double r2_1(double* a, double* xm, int n, double r1);
void proisv_matr_na_vect(double* a, double* b, double* c, int n);
double skal_proisv(double* a, double* b, int n);
double r1(double* a, double* b, double* xm, int n);
double r2(double* xm, int n);
void razn_vect(double* a, double* b, double* c, int n);
void umnozh_vect_na_ch(double* a, double* b, int n, double tau);