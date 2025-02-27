FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

all: a01.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out
a0%.out : a0%.o array.o sortirovki.o sravneniya.o
	gcc $(FLAGS) $^ -o $@
a0%.o : a0%.c array.h io_status.h
	gcc -c $(FLAGS) $<
array.o : array.c array.h io_status.h
	gcc -c $(FLAGS) $<
sortirovki.o : sortirovki.c sortirovki.h io_status.h
	gcc -c $(FLAGS) $<
sravneniya.o : sravneniya.c sravneniya.h io_status.h
	gcc -c $(FLAGS) $<
clean:
	rm -f *.o
