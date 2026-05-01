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
#include <list>

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

void solve1(char* name1, char* name2, int* res);

int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    double t = 0;
    int res = 0;
    int task = 1;
    if (argc != 3){
        printf("Usage: %s filename1 filename2\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    t = clock();
    solve1(name1, name2, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}



void solve1(char* name1, char* name2, int* res){
    std::ifstream ifs(name1);
    std::vector<std::pair<std::string, int>> container;
    int cnt = 0;
    std::string buf;
    while(!ifs.eof()) {
        ifs >> buf;
        cnt += 1;
        container.push_back(std::make_pair(buf, cnt));
    }
    std::sort(container.begin(), container.end(), less_than);
    const auto pd = std::unique(container.begin(), container.end(), is_equal);
    container.erase(pd, container.end());
    std::sort(container.begin(), container.end(), less_than_);
    std::ofstream ofs(name2);
    for (const auto& p : container){
        *res += 1;
        ofs << p.first << std::endl;
    }
}