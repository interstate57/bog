#pragma once 
int solve(int n, double* a, double* b, double* x);
double norma_mtrx(double* a, int n);
int equal_zero(double a, double b);
int equal(double x, double y);
void vectcpy(double* a, double* b, int n);
void proisv_matr_na_vect(double* a, double* b, double* c, int n);
void razn_vect(double* a, double* b, double* c, int n);
double norma_vect(double* a, int n);
double calc_r1(double* a, double* b, double* x, int n, int* error);
double calc_r2(double* x, int n);
