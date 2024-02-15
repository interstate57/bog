#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1234
int task1(const char* s, char* buf);
int task2(const char* s, char* buf);
enum error_codes{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_LAST_BACKSLASH
};