FLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out
a01.out: a01.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a01.o vspom_functions.o solves.o array.o -o a01.out
a01.o: a01.c array.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a01.c array.c
vspom_functions.o: vspom_functions.c vspom_functions.h
	gcc -c $(FLAGS) vspom_functions.c
solves.o: solves.c vspom_functions.h solves.h
	gcc -c $(FLAGS) solves.c
array.o: solves.c vspom_functions.h
	gcc -c $(FLAGS) array.c
a02.out: a02.o vspom_functions.o solves.o array.o
	gcc $(FLAGS) a02.o vspom_functions.o solves.o array.o -o a02.out
a02.o: a02.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a02.c
a03.out: a03.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a03.o vspom_functions.o solves.o array.o -o a03.out
a03.o: a03.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a03.c
a04.out: a04.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a04.o vspom_functions.o solves.o array.o -o a04.out
a04.o: a04.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a04.c 
a05.out: a05.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a05.o vspom_functions.o solves.o array.o -o a05.out
a05.o: a05.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a05.c
a06.out: a06.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a06.o vspom_functions.o solves.o array.o -o a06.out
a06.o: a06.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a06.c
a07.out: a07.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a07.o vspom_functions.o solves.o array.o -o a07.out
a07.o: a07.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a07.c
a08.out: a08.o vspom_functions.o solves.o array.o 
	gcc $(FLAGS) a08.o vspom_functions.o solves.o array.o -o a08.out
a08.o: a08.c vspom_functions.h solves.h
	gcc -c $(FLAGS) a08.c