OPTS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out
a01.out: task01.o array_io.o
	gcc $(OPTS) task01.o array_io.o -o a01.out
task01.o: task01.c array_io.h
	gcc -c $(OPTS) task01.c
array_io.o: array_io.c array_io.h
	gcc -c $(OPTS) array_io.c
a02.out: task02.o array_io.o
	gcc $(OPTS) task02.o array_io.o -o a02.out
task02.o: task02.c array_io.h
	gcc -c $(OPTS) task02.c
a03.out: task03.o array_io.o
	gcc $(OPTS) task03.o array_io.o -o a03.out
task03.o: task03.c array_io.h
	gcc -c $(OPTS) task03.c
a04.out: task04.o array_io.o
	gcc $(OPTS) task04.o array_io.o -o a04.out
task04.o: task04.c array_io.h
	gcc -c $(OPTS) task04.c
a05.out: task05.o array_io.o
	gcc $(OPTS) task05.o array_io.o -o a05.out
task05.o: task05.c array_io.h
	gcc -c $(OPTS) task05.c
a06.out: task06.o array_io.o
	gcc $(OPTS) task06.o array_io.o -o a06.out
task06.o: task06.c array_io.h
	gcc -c $(OPTS) task06.c
a07.out: task07.o array_io.o
	gcc $(OPTS) task07.o array_io.o -o a07.out
task07.o: task07.c array_io.h
	gcc -c $(OPTS) task07.c
a08.out: task08.o array_io.o
	gcc $(OPTS) task08.o array_io.o -o a08.out
task08.o: task08.c array_io.h
	gcc -c $(OPTS) task08.c
