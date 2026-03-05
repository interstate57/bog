#ifndef ENUM_H
#define ENUM_H

#define LEN 1234

#define BACKSLASH '\\'

enum class io_status
{
    success,
    eof,
    format,
    memory,
    wrong_file
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
};

enum class like_type
{
    percent,
    underline,
    in_between,
    not_in_between,
    nothing,
};

#endif