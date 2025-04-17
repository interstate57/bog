FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

all: a05.out a06.out a07.out a08.out
a0%.out : a0%.o array_io.o solve.o
	gcc $(FLAGS) $^ -o $@ -lm
a0%.o : a0%.c array_io.h solve.h
	gcc -c $(FLAGS) $<
array_io.o : array_io.c array_io.h
	gcc -c $(FLAGS) $<
solve.o : solve.c solve.h
	gcc -c $(FLAGS) $<
clean:
	rm -f *.o