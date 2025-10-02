# ifndef sortirovki_H
# define sortirovki_H

int sort1(const student& x, student* a, int n);


int sort3 (student* a, int n, int m);

void sort4 (student* a, int n);

void sort5 (student* a, int n);

void sort6 (student* a, int n);

void sort7 (student* a, int n);

int binpoisk (student x, student* a, int n);

void sort8 (student* a, student* b, int n);

void merge (student* a, student* b, int n, int m, student* c);

void sort9 (student* a, int n);

int polov_sort (student x, student* a, int n);

io_status read_array(student* a, int n, const char* name);

int difference(student* a, int n);

void print_array(student* a, int n, int p);

void init_array(student* a, int n, int s);

int f(int s, int n, int i);

# endif