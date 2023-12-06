FLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
all: a01.out a02.out a03.out
#a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out
a01.out: a01.o vspom_functions.o
a02.out: a02.o vspom_functions.o
a03.out: a03.o vspom_functions.o

%.out: %.o
		gcc $^ -o $@

%.o: %.c
		gcc $(FLAGS) -c $<
