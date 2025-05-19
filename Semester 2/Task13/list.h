#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LEN 1234

typedef struct _node
{
    char* string;
    struct _node* next;
} node;

typedef enum io_status_{
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_MEMORY,
} io_status;

int get_len(node* head);

void delete_list(node* head);

io_status read_list(node** res, const char* name);

void print_list(node* head, int p);
