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
int task1(const char* s, char* buf);
int task2(const char* s, char* buf);
int task3(const char* s, /*char* buf,*/ const char* out);
int task4(const char* s, char* buf);