FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a01.out a02.out a04.out a05.out a06.out

a%.out: a%.o
	g++ $(OPTS) $^ -o $@
a%.o: a%.cpp solve.h request.h io_status.h b_tree.h rb_tree.h
	g++ -c $(OPTS) $< -o $@
clean: 
	rm -f *.o all
