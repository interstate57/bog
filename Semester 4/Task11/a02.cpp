#include "time.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

#include "io_status.h"

bool less_than(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    if ((a.first < b.first) || (a.first == b.first && a.second < b.second))
        return true;
    return false;
}

bool is_equal(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    if (a.first == b.first)
        return true;
    return false;
}

bool less_than_(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    if (a.second < b.second)
        return true;
    return false;
}
io_status solve2(char* name1, char* name2, int* res);

int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    double t = 0;
    int res = 0;
    int task = 2;
    if (argc != 3){
        printf("Usage: %s filename1 filename2\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    t = clock();
    io_status st = solve2(name1, name2, &res);
    if (st != io_status::success) {
        printf("Wrong file!\n");
        return -1;
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}


io_status solve2(char* name1, char* name2, int* res){
    std::ifstream ifs(name1);
    if (!ifs.is_open())
        return io_status::wrong_file;
    std::map<std::string, int> container;
    std::ofstream ofs(name2);
    if (!ofs.is_open())
        return io_status::wrong_file;
    std::string buf;
    while (std::getline(ifs, buf)) {
        if (container.find(buf) == container.end()){
            container[buf] = 0;
            *res += 1;
            ofs << buf << std::endl;
        }
    }
    return io_status::success;
}