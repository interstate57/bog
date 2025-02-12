#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1234
typedef enum io_status_ {
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_PATTERN,
} io_status;
//#define SUCCESS 0
//#define ERROR_OPEN -1
//#define ERROR_READ -2
//#define ERROR_LAST_BACKSLASH -3
io_status task1(const char* s, char* buf, int* r);
io_status pattern2 (const char* s, char* s1, int* s2);
io_status task2(const char* s, char* buf, char* s1, int s2, int* r);
io_status task3(const char* s, const char* t, char* buf, int* r);
io_status task4(const char* s, const char* t, char* buf, int* r);

