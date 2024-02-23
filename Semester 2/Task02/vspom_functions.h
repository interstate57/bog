#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1234
#define SUCCESS 0
#define ERROR_OPEN -1
#define ERROR_READ -2
#define ERROR_LAST_BACKSLASH -3
int task1(char* s1, char* s2, char* buf);
int task2(const char* s, char* buf);
int task3(char* s3, int* s4, char* s5, char* buf);
int task4(const char* s, char* buf);
int pattern1(char* s, char* s1, char* s2);
int pattern3(char* s, char*s3, int* s4, char* s5);