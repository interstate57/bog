#ifndef IO_STATUS_H
#define IO_STATUS_H

#define LEN 1234

enum class io_status {
	success,
	eof,
	format,
	memory,
	open_error_a,
	open_error_b,
	parsing_error,
    create,
};


#endif
