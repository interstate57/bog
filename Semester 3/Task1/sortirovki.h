# ifndef sortirovki_H
# define sortirovki_H

int sort1(const data& x, data* a, int n);


int sort3 (data* a, int n, int m);

void sort4 (data* a, int n);

void sort5 (data* a, int n);

void sort6 (data* a, int n);

void sort7 (data* a, int n);

int binpoisk (data x, data* a, int n);

void sort8 (data* a, data* b, int n);

void merge (data* a, data* b, int n, int m, data* c);

void sort9 (data* a, int n);

int polov_sort (data x, data* a, int n);

io_status read_array(data* a, int n, const char* name);

int difference(data* a, int n);


# endif