#ifndef IO_STATUS_H
#define IO_STATUS_H

#define LEN 1234

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

#endif