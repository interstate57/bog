#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: k " << endl;
        return 0;
    }

    int n = 0;
    sscanf(argv[1], "%d", &n);

    int c = clock();
    srand(c);

    int N_MAX = n * 100;
    for (int i = 0; i < n; ++i) {
        cout << "s " << rand() % N_MAX << endl;
    }

    return 0;
}
