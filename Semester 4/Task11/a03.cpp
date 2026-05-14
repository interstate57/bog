#include "time.h"
#include <libgen.h>
#include <memory>
//#include <string.h>
#include <string>
//#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include "io_status.h"


io_status solve3(char* name1, char* name2, int* res);



int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    double t = 0;
    int res = 0;
    int task = 3;
    if (argc != 3){
        printf("Usage: %s filename1 filename2\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    t = clock();
    io_status st = solve3(name1, name2, &res);
    if (st != io_status::success) {
        printf("Wrong file!\n");
        return -1;
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}

io_status solve3(char* name1, char* name2, int* res){
    std::ifstream ifs(name1);
    if (!ifs.is_open())
        return io_status::wrong_file;
    std::multiset <std::string> container;
    int cnt = 0;
    std::string buf;
    std::ofstream ofs(name2);
    if (!ofs.is_open())
        return io_status::wrong_file;
    int cnt_str = 0;
    while(std::getline(ifs, buf)) {
        cnt += 1;
        cnt_str = 0;
        container.insert(buf);
        auto p = container.equal_range(buf);
        for (auto i = p.first; i != p.second; ++i){
            cnt_str += 1;
        }
        if (cnt_str == 1)
            *res += 1;
        ofs << cnt << " " << cnt_str << " " << buf << std::endl;
    }
    return io_status::success;
}