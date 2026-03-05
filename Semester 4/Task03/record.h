#ifndef RECORD_H
#define RECORD_H
# include <memory>
# include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "enum.h"

class record
{
    private:
        std::unique_ptr<char []> name = nullptr;
        int phone = 0;
        int group = 0;
    public:
        record () = default;
        ~record () = default;
        const char * get_name () const { return name.get (); }
        int get_phone () const { return phone; }
        int get_group () const { return group; }
        int init (const char *n, int p, int g){
            phone = p;
            group = g;
            if (n){
                name = std::make_unique<char []> (strlen (n) + 1);
                if (!name) return -1;
                strcpy (name.get(), n);
            }
            else
                name = nullptr;
            return 0;
        }
        // Allow as return value for functions
        record (record &&x) = default; // move constructor
        // Assignement move operator
        record& operator= (record&& x) = default;
        // Prohoibit pass by value
        // (it is default when move constructor is declared)
        record (const record &x) = delete;
        // Prohoibit assignement operator
        // (it is default when move constructor is declared)
        record& operator= (const record&) = delete;
        // Check condition ’x’ for field ’name’ for ’this’ and ’y’
        bool compare_name (condition x, const record& y) const{
            switch (x)
            {
                case condition::none: // not specified
                    return true; // unspecified opeation is true
                case condition::eq: // equal
                    return strcmp(name.get(), y.name.get()) == 0;
                case condition::ne: // not equal
                    return strcmp(name.get(), y.name.get()) != 0;
                case condition::lt: // less than
                    return strcmp(name.get(), y.name.get()) < 0;
                case condition::gt: // less than
                    return strcmp(name.get(), y.name.get()) > 0;
                case condition::le: // less equal
                    return strcmp(name.get(), y.name.get()) <= 0;
                case condition::ge: // great equal
                    return strcmp(name.get(), y.name.get()) >= 0;
                case condition::like: // strings only: match pattern
                    like_type type = find_type(y);
                    switch (type){
                        case like_type::percent:
                            return false;
                        case like_type::underline:
                            return false;
                        case like_type::in_between:
                            return false;
                        case like_type::not_in_between:
                            return false;
                    }
                    return false;
            }
            return false;
        }
        // Check condition ’x’ for field ’phone’ for ’this’ and ’y’
        bool compare_phone (condition x, const record& y) const{
            switch (x)
            {
                case condition::none: // not specified
                    return true; // unspecified opeation is true
                case condition::eq: // equal
                    return phone == y.phone;
                case condition::ne: // not equal
                    return phone != y.phone;
                case condition::lt: // less than
                    return phone < y.phone;
                case condition::gt: // less than
                    return phone > y.phone;
                case condition::le: // less equal
                    return phone <= y.phone;
                case condition::ge: // great equal
                    return phone >= y.phone;
                case condition::like: // strings only: match pattern
                    return false; // cannot be used for phone
            }
            return false;
        }
        // Check condition ’x’ for field ’group’ for ’this’ and ’y’
        bool compare_group (condition x, const record& y) const{
            switch (x)
            {
                case condition::none: // not specified
                    return true; // unspecified opeation is true
                case condition::eq: // equal
                    return group == y.group;
                case condition::ne: // not equal
                    return group != y.group;
                case condition::lt: // less than
                    return group < y.group;
                case condition::gt: // less than
                    return group > y.group;
                case condition::le: // less equal
                    return group <= y.group;
                case condition::ge: // great equal
                    return group >= y.group;
                case condition::like: // strings only: match pattern
                    return false; // cannot be used for group
            }
            return false;
        }
        void print (FILE * fp = stdout){
            fprintf(fp, "%s %d %d\n", name, phone, group);
        }
        io_status read (FILE *fp = stdin){
            char buf[LEN];
            name = nullptr;
            if (fscanf (fp, "%s%d%d", buf, &phone, &group) != 3){
                if (feof(fp)) 
                    return io_status::eof;
                return io_status::format;
            }
            if (init (buf, phone, group))
                return io_status::memory;
            return io_status::success;
        }
        like_type find_type(const record& x){
            int prev_back = 0;
            for (int i = 0; x.name[i]; i++){  //////////////
                if (x.name[i] == BACKSLASH && !prev_back){
                    prev_back = 1;
                    continue;
                }
                if (x.name[i] == '_' && !prev_back){
                    return like_type::underline;
                }
                if (x.name[i] == '%' && !prev_back){
                    return like_type::percent;
                }
                if (x.name[i] == '[' && !prev_back){
                    if (x.name[i + 1] && x.name[i + 1] == '^')
                        return like_type::not_in_between;
                    return like_type::in_between;
                }
                prev_back = 0;
            }
            return like_type::nothing;
        }
};

class command : public record
{
    private:
        condition c_name = condition::none;
        condition c_phone = condition::none;
        condition c_group = condition::none;
    public:
        command () = default;
        ~command () = default;
        // Convert string command to data structure
        // Example 1: "phone = 1234567" parsed to
        // (command::phone = 1234567, command::c_phone = condition::eq)
        // other fields are unspecified
        // Example 2: "name like St%" parsed to
        // (command::name = "St%", command::c_name = condition::like)
        // other fields are unspecified
        bool parse (const char * string){
            int i = 0;
            int j = 0;
            condition dop;
            i += skip_spaces(string);
            for (j = i; string[j] && string[j] != ' '; j++);
            int len_first_word = j - i;
            i = j;
            i += skip_spaces(string + i);
            for (j = i; string[j] && string[j] != ' '; j++);
            int len_second_word = j - i;
            if (len_second_word == 2){
                if (strncmp(string + i, "<>", len_second_word) == 0){
                    dop = condition::ne;
                }
                else if (strncmp(string + i, "<=", len_second_word) == 0){
                    dop = condition::le;
                }
                else if (strncmp(string + i, ">=", len_second_word) == 0){
                    dop = condition::ge;
                }
                else{
                    return 0;
                }
            }
            else if (len_second_word == 1){
                if (strncmp(string + i, "=", len_second_word) == 0){
                    dop = condition::eq;
                }
                else if (strncmp(string + i, "<", len_second_word) == 0){
                    dop = condition::lt;
                }
                else if (strncmp(string + i, ">", len_second_word) == 0){
                    dop = condition::gt;
                }
                else{
                    return 0;
                }
            }
            else if (len_second_word == 4 && strncmp(string + i, "like", len_second_word) == 0){
                dop = condition::like;
            }
            else{
                return 0;
            }
            if (len_first_word == 5){
                if (strncmp(string, "phone", len_first_word) == 0)
                    c_phone = dop;
                else if (strncmp(string, "group", len_first_word) == 0)
                    c_group = dop;
                else
                    return 0;
            }
            else if (len_first_word == 4 && strncmp(string, "name", len_first_word) == 0)
                c_name = dop;
            else
                return 0;
            i = j;
            i += skip_spaces(string + i);
            for (j = i; string[j] && string[j] != ' '; j++);
            int len_third_word = j - i;
            if (c_name != condition::none){
                
            }
        }
        // Print parsed structure
        void print (FILE *fp = stdout) const;
        // Apply command, return comparision result for record ’x’
        bool apply (const record& x) const;
        int skip_spaces(const char* str){
            int i;
            for (i = 0; str[i]; i++){
                if (str[i] != ' ')
                    return i;
            }
            return i;
        }
};

#endif