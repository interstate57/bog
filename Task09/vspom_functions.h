#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
double test_1(size_t n, size_t (*p)(const char *), const char *s, size_t *res);
double test_2_5 (size_t n, char* (*p) (char*, const char *), char *s1, const char *s2, char **result);
size_t strlen_(const char *);
char *strcpy_(char *s1, const char *s2);