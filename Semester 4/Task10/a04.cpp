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

using std::list;

typedef std::pair<std::string, std::pair<int, int>> data;

void solve4(char* name1, char* name2, int* res);

bool less_than(const data& a, const data& b){
    if ((a.first < b.first) || (a.first == b.first && a.second.first < b.second.first))
        return true;
    return false;
}

bool less_than_(const data& a, const data& b){
    if (a.second.first < b.second.first)
        return true;
    return false;
}
      
bool is_equal(const data& a, const data& b){
    if (a.first == b.first)
        return true;
    return false;
}

void set_dop(list<data>::iterator begin, list<data>::iterator end, int number){
    auto k = end;
    do{
        --k;
        (*k).second.second = number;
    }
    while(k != begin);
}


int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    double t = 0;
    int res = 0;
    int task = 4;
    if (argc != 3){
        printf("Usage: %s filename1 filename2\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    t = clock();
    solve4(name1, name2, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}


void solve4(char* name1, char* name2, int* res){
    std::ifstream ifs(name1);
    list <data> container;
    int cnt = 0;
    int dop = 0;
    std::string buf;
    while(!ifs.eof()) {
        ifs >> buf;
        cnt += 1;
        container.push_back(std::make_pair(buf, std::make_pair(cnt, dop)));
    }
    container.sort(less_than);
    int number = 1;
    auto p = container.begin();
    auto k = container.begin();
    do{
        ++k;
        if (k == container.end()){
            set_dop(p, k, number);
            *res += 1;
        }
        else if (is_equal(*p, *k)){
            number += 1;
        }
        else{
            set_dop(p, k, number);
            p = k;
            number = 1;
            *res += 1;
        }
    }
    while(k != container.end());
    container.sort(less_than_);
    std::ofstream ofs(name2);
    for (const auto& p : container){
        ofs << p.second.first << " " << p.second.second << " " << p.first << std::endl;
    }
}