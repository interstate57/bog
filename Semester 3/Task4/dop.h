#ifndef dop_H
#define dop_H
#include "student.h"

void print_list(const list_node* head, int p);

io_status read_list(list_node** p_head, FILE* fp = stdout);

void delete_list(list_node* head);

#endif