#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1234
size_t strlen_(const char *);
char *strcpy_(char *s1, const char *s2);
char *strchr_ (const char *s, int ch);
char *strrchr_ (const char *s, int ch);
char *strcat_ (char *string1, const char *string2);
int strcmp_ (const char *string1, const char *string2);
size_t strcspn_ (const char *string1, const char *string2);
size_t strspn_ (const char *s1, const char *s2);
char *strstr_ (const char *string1, const char *string2);
char *strtok_r_ (char *str, const char *delim, char **saveptr);
void print_array(char** a, int n, int max_print);
void free_array(char** a, int n);
int read_array(char** a, int n, const char* name);
enum error_codes{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_MEM,
};