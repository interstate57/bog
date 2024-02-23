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
#define PATTERN_ERROR -4
int task1(char* s1, char* s2, char* buf);
int task3(char* s3, int* s4, char* s5, char* buf);
int task2(char * buf, char * s1, char * s2);
int task5(char* s1, char* s2, char* s3, char* s4, char* buf);
int pattern1(char* s, char* s1, char* s2);
int pattern2(char* s, char* s1, char* s2);
int pattern3(char* s, char*s3, int* s4, char* s5);
int pattern5(char* s, char* s1, char* s2, char*s3, char* s4);