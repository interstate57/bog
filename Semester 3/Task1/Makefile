FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out
a0%.out : a0%.o sortirovki.o
	g++ $(FLAGS) $^ -o $@
a0%.o : a0%.cpp data.h
	g++ -c -g -DM=10 $(FLAGS) $<
sortirovki.o : sortirovki.cpp sortirovki.h data.h
	g++ -c -g -DM=10 $(FLAGS) $<
clean:
	rm -f *.o