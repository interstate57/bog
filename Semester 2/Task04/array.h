#pragma once
#include "io_status.h"
io_status read_array(char** a, int n, const char* name);
void delete_array(char** a, int n);
void print_array(char ** a, int n, int m);
int difference (char** a, int n, int (*cmp)(const char*, const char*));