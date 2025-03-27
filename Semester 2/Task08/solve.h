#pragma once

double solve1(double* a, double* x, double* xm, int n, int m);
void solve2(double* a, double* x, double* b, double* xm, int n, int m, double tau);
void solve3(double* a, double* x, double* b, double* xm, double* r, int n, int m);
void solve4(double* a, double* x, double* b, double* xm, double* r, int n, int m);
void solve7(double* a, double* x, double* b, double* xm, double* r, int n, int m, double tau);
void solve8(double* a, double* x, double* b, double* xm, double* r, double* w, int n, int m, double tau);
void solve9(double* a, double* x, double* b, double* xm, double* r, double* w, int n, int m, double tau);
void solve10(double* a, double* x, double* b, double* xm, double* r, double* w, int n, int m, double tau);


double r2_1(double* a, double* xm, int n, double r1);
double r1_(double* a, double* b, double* xm, int n);
double r2_(double* xm, int n);

int equal(double x, double y);

double skal_proisv(double* a, double* b, int n);
void xk(double* a, double* b, double* c, int n, double tau);
int gauss_nizhn(double* a, double* r, double* w, int n);
int gauss_verh(double* a, double* r, double* w, int n);
int gauss_verh_dop(double* a, double* r, double* w, int n);

void proisv_matr_na_vect(double* a, double* b, double* c, int n);
void vectcpy(double* a, double* b, int n);
int proizv_d_obr_na_vect(double* a, double* b, int n);
void umnozh_vect_na_ch(double* a, double* b, int n, double tau);
void sum_vect(double* a, double* b, double* c, int n);
void razn_vect(double* a, double* b, double* c, int n);