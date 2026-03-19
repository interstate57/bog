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
            like_type type1, type2;
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
                    type1 = find_type(*this);
                    //std::cout << "Found type : " << type1 << std::endl;
                    switch (type1){
                        case like_type::percent:
                            return solve_for_percent(y);
                        case like_type::underline:
                            return solve_for_underline(y);
                        case like_type::in_between:
                            return solve_for_brackets(y);
                        case like_type::not_in_between:
                            return solve_for_brackets_with_cap(y);
                        case like_type::nothing:
                            return strcmp(name.get(), y.name.get()) == 0;
                        default:
                            break;
                    }
                    return false;
                case condition::nlike:

                    type2 = find_type(*this);
                    switch (type2){
                        case like_type::percent:
                            return !solve_for_percent(y);
                        case like_type::underline:
                            return !solve_for_underline(y);
                        case like_type::in_between:
                            return !solve_for_brackets(y);
                        case like_type::not_in_between:
                            return !solve_for_brackets_with_cap(y);
                        case like_type::nothing:
                            return !(strcmp(name.get(), y.name.get()) == 0);
                        default:
                            break;
                    }
                    return false;
                default:
                    break;
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
                case condition::nlike:
                    return false;
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
                case condition::nlike:
                    return false;
            }
            return false;
        }
        void print (const ordering order[], FILE *fp){
            const int max_items = 3;
            //const ordering default_ordering[max_items] = {ordering::name, ordering::phone, ordering::group};
            const ordering * p = order;
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
            for (int i = 0; x.name[i]; i++){
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
        int solve_for_percent(const record& x) const{
            request_7 request;
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
        ordering c_order[3] = {ordering::none, ordering::none, ordering::none};
        ordering c_order_end[3] = {ordering::none, ordering::none, ordering::none};
        command_type com_type = command_type::none;
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
        const ordering* get_ordering() const{
            return (const ordering*) c_order;
        }
        const ordering* get_ordering_end() const{
            return (const ordering*) c_order_end;
        }
        void set_phone(int x){
            this->phone = x;
        }
        void set_group(int x){
            this->group = x;
        }
        bool set_name(const char *n){
            if (n){
                name = std::make_unique<char []> (strlen (n) + 1);
                if (!name) return false;
                strcpy (name.get(), n);
            }
            return true;
        }
        command_type get_command_type(){
            return com_type;
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
            int cnt, cnt1, cnt2;
            switch (op){
                case operation::none:
                    if (c_phone != condition::none){
                        return compare_phone(c_phone, x);
                    }
                    if (c_group != condition::none){
                        return compare_group(c_group, x);
                    }
                    if (c_name != condition::none){
                        return compare_name(c_name, x);
                    }
                    return 1;
                case operation::lor:
                    cnt = 0;
                    if (c_phone != condition::none){
                        cnt += to_int(compare_phone(c_phone, x));
                    }
                    if (c_group != condition::none){
                        cnt += to_int(compare_group(c_group, x));
                    }
                    if (c_name != condition::none){
                        cnt += to_int(compare_name(c_name, x));
                    }
                    if (cnt != 0)
                        return 1;
                    return 0;
                case operation::land:
                    cnt1 = 0;
                    cnt2 = 0;
                    if (c_phone != condition::none){
                        cnt1 += to_int(compare_phone(c_phone, x));
                        //printf("phone : %d\n", compare_phone(c_phone, x));
                        cnt2 += 1;
                    }
                    if (c_group != condition::none){
                        cnt1 += to_int(compare_group(c_group, x));
                        //printf("group : %d, this : %d, x.group = %d\n", compare_group(c_group, x), group, x.get_group());
                        cnt2 += 1;
                    }
                    if (c_name != condition::none){
                        cnt1 += to_int(compare_name(c_name, x));
                        //printf("name : %d\n", compare_name(c_name, x));
                        cnt2 += 1;
                    }
                    //printf("cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
                    if (cnt1 == cnt2)
                        return 1;
                    return 0;
                default:
                    break;
            }
            return 0;
        }

        int to_int(bool boo) const{
            return (boo ? 1 : 0);
        }
        int skip_spaces(const char* str){
            int i;
            for (i = 0; str[i]; i++){
                if (str[i] != ' ')
                    return i;
            }
            return i;
        }



        friend class parser;
};

#endif