#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "sravneniya.h"

int up_strcmp(const char* a, const char* b){
    return strcmp(a, b);
}
int down_strcmp(const char* a, const char* b){
    return -up_strcmp(a, b);
}
int up_len(const char* a, const char* b){
    ssize_t dif = (ssize_t)strlen(a) - (ssize_t)strlen(b);
    if (dif > 0){
        return 1;
    }
    else if (dif < 0){
        return -1;
    }
    return 0;
}
int down_len(const char* a, const char* b){
    return -up_len(a, b);
}

