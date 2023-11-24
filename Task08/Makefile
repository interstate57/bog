OPTS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out rand_sort
a01.out: task01.o array_io.o functions.o
	gcc $(OPTS) task01.o array_io.o functions.o -o a01.out
task01.o: task01.c array_io.h functions.h
	gcc -c $(OPTS) task01.c
array_io.o: array_io.c array_io.h
	gcc -c $(OPTS) array_io.c
functions.o: functions.c functions.h
	gcc -c $(OPTS) functions.c
a02.out: task02.o array_io.o functions.o
	gcc $(OPTS) task02.o array_io.o functions.o -o a02.out
task02.o: task02.c array_io.h functions.h
	gcc -c $(OPTS) task02.c
a03.out: task03.o array_io.o functions.o
	gcc $(OPTS) task03.o array_io.o functions.o -o a03.out
task03.o: task03.c array_io.h functions.h
	gcc -c $(OPTS) task03.c
a04.out: task04.o array_io.o functions.o
	gcc $(OPTS) task04.o array_io.o functions.o -o a04.out
task04.o: task04.c array_io.h functions.h
	gcc -c $(OPTS) task04.c
a05.out: task05.o array_io.o functions.o
	gcc $(OPTS) task05.o array_io.o functions.o -o a05.out
task05.o: task05.c array_io.h functions.h
	gcc -c $(OPTS) task05.c
a06.out: task06.o array_io.o functions.o
	gcc $(OPTS) task06.o array_io.o functions.o -o a06.out
task06.o: task06.c array_io.h functions.h
	gcc -c $(OPTS) task06.c
a07.out: task07.o array_io.o functions.o
	gcc $(OPTS) task07.o array_io.o functions.o -o a07.out
task07.o: task07.c array_io.h functions.h
	gcc -c $(OPTS) task07.c
a08.out: task08.o array_io.o functions.o
	gcc $(OPTS) task08.o array_io.o functions.o -o a08.out
task08.o: task08.c array_io.h functions.h
	gcc -c $(OPTS) task08.c
a09.out: task09.o array_io.o functions.o
	gcc $(OPTS) task09.o array_io.o functions.o -o a09.out
task09.o: task09.c array_io.h functions.h
	gcc -c $(OPTS) task09.c
a10.out: task10.o array_io.o functions.o
	gcc $(OPTS) task10.o array_io.o functions.o -o a10.out
task10.o: task10.c array_io.h functions.h
	gcc -c $(OPTS) task10.c

rand_sort: rand_sort.o array_io.o functions.o
	gcc $(OPTS) rand_sort.o functions.o array_io.o -o rand_sort
rand_sort.o: rand_sort.c
	gcc -c $(OPTS) rand_sort.c
