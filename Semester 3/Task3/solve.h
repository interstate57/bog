#ifndef solve_H
#define solve_H
#include "student.h"

int solve1(student* a, int n);

int solve2(student* a, int n);

int solve3(student* a, int n);

int solve4(student* a, int n);

int solve5(student* a, int n);

int solve6(student *a, int n, student &x);

int solve7(student *a, int n, student &x);

int solve8(student *a, int n, student &x);

int solve9(student *a, int n, student &x);

int solve10(student *a, int n, student &x);

io_status read_array(student* a, int n, const char* name);

void print_array(student* a, int n, int p);

void init_array(student* a, int n, int s);

int f(int s, int n, int i);

#endif