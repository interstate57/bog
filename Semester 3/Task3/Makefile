FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a01.out a02.out a03.out a04.out a06.out a07.out a08.out a09.out
a0%.out : a0%.o solve.o
	g++ $(FLAGS) $^ -o $@
a0%.o : a0%.cpp student.h
	g++ -c -g $(FLAGS) $<
a1%.out : a1%.o solve.o
	g++ $(FLAGS) $^ -o $@
a1%.o : a1%.cpp student.h
	g++ -c -g $(FLAGS) $<
solve.o : solve.cpp solve.h student.h
	g++ -c -g $(FLAGS) $<
clean:
	rm -f *.o