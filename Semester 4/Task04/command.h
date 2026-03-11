 #ifndef RECORD_H
#define RECORD_H
# include <memory>
# include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "enum.h"
#include "request.h"

class record
{
    protected:
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
                    return strcmp(name.get(), y.name.get()) > 0;
                case condition::gt: // less than
                    return strcmp(name.get(), y.name.get()) < 0;
                case condition::le: // less equal
                    return strcmp(name.get(), y.name.get()) >= 0;
                case condition::ge: // great equal
                    return strcmp(name.get(), y.name.get()) <= 0;
                case condition::like: // strings only: match pattern
                    like_type type = find_type(*this);
                    //std::cout << "type : " << type << std::endl;
                    switch (type){
                        case like_type::percent:
                            return false;
                        case like_type::underline:
                            return solve_for_underline(y);
                        case like_type::in_between:
                            return solve_for_brackets(y);
                        case like_type::not_in_between:
                            return solve_for_brackets_with_cap(y);
                        default:
                            break;
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
                    return phone > y.phone;
                case condition::gt: // less than
                    return phone < y.phone;
                case condition::le: // less equal
                    return phone >= y.phone;
                case condition::ge: // great equal
                    return phone <= y.phone;
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
                    return group > y.group;
                case condition::gt: // less than
                    return group < y.group;
                case condition::le: // less equal
                    return group >= y.group;
                case condition::ge: // great equal
                    return group <= y.group;
                case condition::like: // strings only: match pattern
                    return false; // cannot be used for group
            }
            return false;
        }
        void print (const ordering order[], FILE *fp){
            const int max_items = 3;
            const ordering default_ordering[max_items] = {ordering::name, ordering::phone, ordering::group};
            const ordering * p = (order ? order : default_ordering);
            for (int i = 0; i < max_items; i++)
                switch (p[i]){
                    case ordering::name:
                        printf (" %s", name.get()); break;
                    case ordering::phone:
                        printf (" %d", phone); break;
                    case ordering::group:
                        printf (" %d", group); break;
                    case ordering::none:
                        continue;
                }
            fprintf (fp, "\n");
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
        like_type find_type(const record& x) const{
            int prev_back = 0;
            for (int i = 0; x.name[i]; i++){  //////////////
                if (x.name.get()[i] == BACKSLASH && !prev_back){
                    prev_back = 1;
                    continue;
                }
                if (x.name.get()[i] == '_' && !prev_back){
                    return like_type::underline;
                }
                if (x.name.get()[i] == '%' && !prev_back){
                    return like_type::percent;
                }
                if (x.name.get()[i] == '[' && !prev_back){
                    if (x.name[i + 1] && x.name[i + 1] == '^')
                        return like_type::not_in_between;
                    return like_type::in_between;
                }
                prev_back = 0;
            }
            return like_type::nothing;
        }
        int solve_for_underline(const record& x) const{
            request_6 request;
            request.parse_t(" ");
            request.parse_s(name.get());
            if (request.context_fit(x.get_name())){
                return 1;
            }
            return 0;
        }
        int solve_for_brackets(const record& x) const{
            request_8 request;
            request.parse_t(" ");
            request.parse_s(name.get());
            if (request.context_fit(x.get_name())){
                return 1;
            }
            return 0;
        }
        int solve_for_brackets_with_cap(const record& x) const{
            request_9 request;
            request.parse_t(" ");
            request.parse_s(name.get());
            if (request.context_fit(x.get_name())){
                return 1;
            }
            return 0;
        }
};

class command : public record
{
    private:
        condition c_name = condition::none;
        condition c_phone = condition::none;
        condition c_group = condition::none;
        operation op = operation::none;
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
        bool mini_parse (const char * string){
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
            for (j = i; string[j] && string[j] != ' ' && string[j] != '\n'; j++);
            int len_third_word = j - i;
            char str_dop[LEN] = {};
            strncpy(str_dop, string + i, len_third_word);
            if (c_name != condition::none){
                int res = init(str_dop, 0, 0);
                if (res == -1)
                    return 0;
                
            }
            else if (c_phone != condition::none || c_group != condition::none){
                int number = std::atoi(str_dop);
                if (number == 0 && str_dop[0] != '0'){
                    return 0;
                }
                if (c_phone != condition::none){
                    int res = init("", number, 0);
                    if (res == -1)
                        return 0;
                }
                else{
                    int res = init("", 0, number);
                    if (res == -1)
                        return 0;
                }
            }
            else{
                return 0;
            }
            return 1;
        }
        // Print parsed structure
        void print () const{
            if (c_phone != condition::none){
                std::cout << "phone : condition - " << c_phone << ", number - " << phone << std::endl;
            }
            else if (c_group != condition::none){
                std::cout << "group : condition - " << c_group << ", number - " << group << std::endl;
            }
            else if (c_name != condition::none){
                std::cout << "name : condition - " << c_name << ", str - " << name.get() << std::endl;
            }
        }
        // Apply command, return comparision result for record ’x’
        bool apply (const record& x) const{
            if (c_phone != condition::none){
                return compare_phone(c_phone, x);
            }
            else if (c_group != condition::none){
                return compare_group(c_group, x);
            }
            else if (c_name != condition::none){
                return compare_name(c_name, x);
            }
            return 0;
        }
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