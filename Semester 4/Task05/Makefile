FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a.out
a.out : a.o parser.o enum.o
	g++ $(FLAGS) $^ -o $@
a.o : a.cpp enum.h list2.h command.h parser.h list.h
	g++ -c -g $(FLAGS) $<
parser.o : parser.cpp enum.h parser.h
	g++ -c -g $(FLAGS) $<
enum.o : enum.cpp enum.h 
	g++ -c -g $(FLAGS) $<
clean:
	rm -f *.o