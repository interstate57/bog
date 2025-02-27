#pragma once

int sort1(char* x, char** a, int n, int (*cmp)(const char* , const char*));
int sort3(char* x, char** a, int n, int (*cmp)(const char* , const char*));

void sort4 (char** a, int n, int (*cmp)(const char* , const char*));
void sort5 (char** a, int n, int (*cmp)(const char* , const char*));
void sort6 (char** a, int n, int (*cmp)(const char* , const char*));
void sort7 (char** a, int n, int (*cmp)(const char* , const char*));
int binpoisk (char* x, char** a, int n, int (*cmp)(const char* , const char*));
void sort8 (char** a, char** b, int n, int (*cmp)(const char* , const char*));
void merge (char** a, char** b, int n, int m, char** c, int (*cmp)(const char* , const char*));
void sort9 (char** a, int n, int (*cmp)(const char* , const char*));
int polov_sort (char* x, char** a, int n, int (*cmp)(const char* , const char*));
