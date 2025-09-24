# ifndef data_H
# define data_H
# include <stdio.h>
#include <iostream>
#include <sstream>
#define LEN 1234
//#define ERROR_READ -1

enum io_status{
    SUCCESS = 0,
    ERROR_READ = -1,
    ERROR_OPEN = -2,
};

class data
{
private:
    int m = 0; // number of actual used elements in a[]
    double a[M] = {}; // array, length is defined in command line -DM=10
    static int p; // number of printed elements in a[]
public:
    data () = default;
    ~data () = default;
    int get_m () const { return m; }
    // Length of the used part of array a: min{m,M}
    int get_M () const { return (m < M ? m : M); }
    const double * get_a () { return a; }
    static int get_p () { return p; }
    static void set_p (int q)
    { p = q; }
    // Copy constructor
    data (const data &x) = default;
    // Assignement operator
    data& operator= (const data&) = default;
    // Comparison operators
    int operator< (const data& x) const
    { return m < x.m; }
    int operator> (const data& x) const
    { return m > x.m; }
    int operator>= (const data& x) const
    { return m >= x.m; }
    int operator<= (const data& x) const
    { return m <= x.m; }
    // Print data in a line (not more than p): m a[0] a[1] ... a[m-1]
    void print (FILE * fp = stdout) const
    {
        int len = get_M (), i;
        fprintf(fp, "%d", m);
        if (len > p) len = p;
        for (i = 0; i < len; i++)
        fprintf(fp, " %le", a[i]);
        fprintf(fp, "\n");
    }
    // Read data from the line: m a[0] a[1] ... a[m-1]
    io_status read (FILE *fp = stdin){
        int mi = 0;
        int i = 0;
        double ai = 0;
        char buf[LEN] = "57";
        if (!fgets(buf, LEN, fp)) return ERROR_READ;
        std::istringstream iss(buf);
        iss >> mi;
        if (iss.fail()) return ERROR_READ;
        mi = (mi > M ? M : mi);
        this->m = mi;
        for (i = 0; i < mi; i++){
            iss >> ai;
            if (iss.fail()) return ERROR_READ;
            a[i] = ai;
        }
        return SUCCESS;
    }
    // Init data by formulae with number s for a_i, i=1, ..., n
    void init (int s, int n, int i){
        switch(s){
            case 1: m = i; break;
            case 2: m = n - i; break;
            case 3: m = i / 2; break;
            case 4: m = n - i / 2; break;
        }
        for (int j = 0; j < m; j++){
            a[j] = 0;
        }
    }
};
# endif // data