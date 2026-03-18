#ifndef ENUM_H
#define ENUM_H

#define LEN 1234

#define BACKSLASH '\\'

#include <iostream>

enum class io_status
{
    success,
    eof,
    format,
    memory,
    wrong_file,
    parsing_error,
    quit,
};

enum class condition
{
    none, // not specified
    eq, // equal
    ne, // not equal
    lt, // less than
    gt, // less than
    le, // less equal
    ge, // great equal
    like, // strings only: match pattern
    nlike, // strings only: not match pattern
};

std::ostream& operator<<(std::ostream& os, const condition& c) {
    const char* str;
    switch (c) {
        case condition::none:
            str = "none"; break;
        case condition::eq:
            str = "eq"; break;
        case condition::ne:
            str = "ne"; break;
        case condition::lt:
            str = "lt"; break;
        case condition::gt:
            str = "gt"; break;
        case condition::le:
            str = "le"; break;
        case condition::ge:
            str = "ge"; break;
        case condition::like:
            str = "like"; break;
        case condition::nlike:
            str = "not like"; break;
        default:
            str = "another";
    }
    os << str;
    return os;
}


enum class like_type
{
    percent,
    underline,
    in_between,
    not_in_between,
    nothing,
};

enum percent_location
{
    start,
    end,
    middle,
    both,
};

std::ostream& operator<<(std::ostream& os, const percent_location& c) {
    const char* str;
    switch (c) {
        case percent_location::start:
            str = "start"; break;
        case percent_location::end:
            str = "end"; break;
        case percent_location::middle:
            str = "middle"; break;
        case percent_location::both:
            str = "both"; break;
        default:
            str = "another";
    }
    os << str;
    return os;
}

std::ostream& operator<<(std::ostream& os, const like_type& c) {
    const char* str;
    switch (c) {
        case like_type::percent:
            str = "%"; break;
        case like_type::underline:
            str = "_"; break;
        case like_type::in_between:
            str = "[]"; break;
        case like_type::not_in_between:
            str = "[^]"; break;
        case like_type::nothing:
            str = "nothing"; break;
        default:
            str = "another"; break;
    }
    os << str;
    return os;
}



enum class ordering
{
    none, // not specified
    name, // print name
    phone, // print phone
    group, // print group
};

std::ostream& operator<<(std::ostream& os, const ordering& c) {
    const char* str;
    switch (c) {
        case ordering::name:
            str = "name "; break;
        case ordering::phone:
            str = "phone "; break;
        case ordering::group:
            str = "group "; break;
        case ordering::none:
            str = "none "; break;
        default:
            str = "another"; break;
    }
    os << str;
    return os;
}

enum class operation
{
    none, // not specified
    land, // logical and
    lor, // logical or
};

enum class command_type
{
    none, // uninitialized
    quit, // end of input stream
    insert, // add record
    select, // find by conditions specified
    del, // delete record
};

#endif