FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: server client
server: ser_tcp.o parser.o enum.o
	g++ $(FLAGS) $^ -o $@
client: cli_tcp.o enum.o
	g++ $(FLAGS) $^ -o $@
enum.o : enum.cpp enum.h 
	g++ -c -g $(FLAGS) $<
parser.o : parser.cpp enum.h parser.h
	g++ -c -g $(FLAGS) $<
ser_tcp.o : ser_tcp.cpp enum.h list2.h command.h parser.h list.h comparator.h database.h hashtable.h list2_search.h vector_m.h kirpichek.h
	g++ -c -g $(FLAGS) $<
cli_tcp.o : cli_tcp.cpp
	g++ -c -g $(FLAGS) $<
clean:
	rm -f *.o