#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1234
int task1(const char* s, char* buf);
int task2(const char* s, char* buf);
int task3(const char* s, const char* t, char* buf);
int task4(const char* s, const char* t, char* buf);
enum error_codes{
    SUCCESS,
    ERROR_OPEN = (-1),
    ERROR_READ = (-2),
    ERROR_LAST_BACKSLASH = (-3)
};