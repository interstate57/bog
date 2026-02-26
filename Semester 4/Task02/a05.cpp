#include "solve.h"
#include <time.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    int task = 5;
	char *a;
    char* b;
    char* spaces;
	char *s;
    char* x;
	double t; 
	io_status res;
    int cnt;
	if(!(argc == 6)){
		printf("Usage %s: name_in name_out s t x\n", argv[0]);
		return 1;
	}
	a = argv[1];
	b = argv[2];
	s = argv[3];
	spaces = argv[4];
    x = argv[5];
	t = clock();
	res = solve5(a, b, s, spaces, x, &cnt);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if (res != io_status::success) {
		switch (res) {
			case io_status::format:
				printf("Wrong format in %s\n", a);
				break;
			case io_status::open_error_a:
				printf("Cannot open %s\n", a);
				break;
			case io_status::open_error_b:
				printf("Cannot open %s\n", b);
				break;
			case io_status::eof:
				printf("Not enough elements in %s\n", a);
				break;
			case io_status::memory:
				printf("Cannot allocate memory in %s\n", a);
				break;
			case io_status::parsing_error:
				printf("Wrong format of query string \"%s\"\n", s);
				break;
			default:
				printf("Unknown error\n");
		}
		return 3;
	}
    printf("%s: Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, cnt, t); 
	return 0;
}
