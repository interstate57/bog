#ifndef PARSER_H
#define PARSER_H
# include <memory>
# include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>


#include "enum.h"
#include "command.h"

class parser {
    private:
        FILE *fp;
        char buf[LEN] = {};
        int curr;

    public:
        parser(FILE* f): fp(f) {}

        char* read(FILE* fp = stdin);

        bool is_spaces(const char s);
        
        int skip_spaces(const char* str);
        
        io_status parse(command& cmd, char* string);
        
        io_status parse_quit(const char* string);
        
        io_status parse_insert(command& cmd, char* string);
        
        io_status parse_delete(command& cmd, const char* string);
        
        io_status parse_select(command& cmd, const char* string);
        
        bool parse_ordering (command& cmd, const char* string);
        
        bool parse_after_where (command& cmd, const char* string);
        
        bool parse_after_order_by(command& cmd, const char* string);
        
        bool parse_condition (command& cmd, const char * string, int* kon);
};

#endif