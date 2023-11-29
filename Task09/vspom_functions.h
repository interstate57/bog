#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
double test_1(size_t n, size_t (*p)(const char *), const char *s, size_t *res);
double test_2_5 (size_t n, char* (*p) (char*, const char *), char *s1, const char *s2, char **result);
double test_3_4 (size_t n, char* (*p) (const char *, int), const char *s, int ch, char **res);
size_t strlen_(const char *);
char *strcpy_(char *s1, const char *s2);
char *strchr_ (const char *s, int ch);
char *strrchr_ (const char *s, int ch);
char *strcat_ (char *string1, const char *string2);