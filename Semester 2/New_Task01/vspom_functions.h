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

io_status task1(const char* s, char* buf, int* r);
io_status pattern2 (const char* s, char* s1, int* s2);
io_status task2(const char* s, char* buf, char* s1, int s2, int* r);
io_status task3(const char* s, const char* t, char* buf, int* r);
io_status task4(const char* s, const char* t, char* buf, int* r);
io_status pattern6(const char* s, char* s1, char* s2);
io_status task6(char* s1, char* s2, char* buf, int* r);
io_status pattern8(const char* s, char*s3, int* s4, char* s5);
io_status task8(char* s3, int* s4, char* s5, char* buf, int* r);

