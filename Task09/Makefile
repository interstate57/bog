FLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out
a01.out: task01.o vspom_functions.o
	gcc $(FLAGS) task01.o vspom_functions.o -o a01.out
task01.o: task01.c vspom_functions.h
	gcc -c $(FLAGS) task01.c 
vspom_functions.o: vspom_functions.c vspom_functions.h
	gcc -c $(FLAGS) vspom_functions.c
a02.out: task02.o vspom_functions.o
	gcc $(FLAGS) task02.o vspom_functions.o -o a02.out
task02.o: task02.c vspom_functions.h
	gcc -c $(FLAGS) task02.c 
a03.out: task03.o vspom_functions.o
	gcc $(FLAGS) task03.o vspom_functions.o -o a03.out
task03.o: task03.c vspom_functions.h
	gcc -c $(FLAGS) task03.c 
a04.out: task04.o vspom_functions.o
	gcc $(FLAGS) task04.o vspom_functions.o -o a04.out
task04.o: task04.c vspom_functions.h
	gcc -c $(FLAGS) task04.c
a05.out: task05.o vspom_functions.o
	gcc $(FLAGS) task05.o vspom_functions.o -o a05.out
task05.o: task05.c vspom_functions.h
	gcc -c $(FLAGS) task05.c
a06.out: task06.o vspom_functions.o
	gcc $(FLAGS) task06.o vspom_functions.o -o a06.out
task06.o: task06.c vspom_functions.h
	gcc -c $(FLAGS) task06.c
a07.out: task07.o vspom_functions.o
	gcc $(FLAGS) task07.o vspom_functions.o -o a07.out
task07.o: task07.c vspom_functions.h
	gcc -c $(FLAGS) task07.c
a08.out: task08.o vspom_functions.o
	gcc $(FLAGS) task08.o vspom_functions.o -o a08.out
task08.o: task08.c vspom_functions.h
	gcc -c $(FLAGS) task08.c
a09.out: task09.o vspom_functions.o
	gcc $(FLAGS) task09.o vspom_functions.o -o a09.out
task09.o: task09.c vspom_functions.h
	gcc -c $(FLAGS) task09.c
a10.out: task10.o vspom_functions.o
	gcc $(FLAGS) task10.o vspom_functions.o -o a10.out
task10.o: task10.c vspom_functions.h
	gcc -c $(FLAGS) task10.c