FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out
a0%.out : a0%.o list.o solve.o
	gcc $(FLAGS) $^ -o $@ -lm
a0%.o : a0%.c list.h solve.h
	gcc -c $(FLAGS) $<
list.o : list.c list.h
	gcc -c $(FLAGS) $<
solve.o : solve.c solve.h list.h
	gcc -c $(FLAGS) $<
clean:
	rm -f *.o -l