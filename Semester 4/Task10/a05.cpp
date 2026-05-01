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
#include <sstream>

#include "io_status.h"

#define LEN 1234


using std::vector;

bool less_than(const std::string& a, const std::string& b){
    if (a < b)
        return true;
    return false;
}

      
bool is_equal(const std::string& a, const std::string& b){
    if (a == b)
        return true;
    return false;
}

void solve5(char* name1, char* name2, char* name3, char* spaces, int* res);

int main(int argc, char* argv[]){
    char* name1 = 0;
    char* name2 = 0;
    char* name3 = 0;
    char* spaces = 0;
    double t = 0;
    int res = 0;
    int task = 5;
    if (argc != 5){
        printf("Usage: %s filename1 filename2 filename3 spaces\n", argv[0]);
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    name3 = argv[3];
    spaces = argv[4];
    t = clock();
    solve5(name1, name2, name3, spaces, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}

void solve5(char* name1, char* name2, char* name3, char* spaces, int* res){
    std::ifstream ifs1(name1);
    std::vector <std::string> container;
    std::string buf;
    while(!ifs1.eof()) {
        ifs1 >> buf;
        container.push_back(buf);
    }
    std::sort(container.begin(), container.end(), less_than);
    const auto pd = std::unique(container.begin(), container.end(), is_equal);
    container.erase(pd, container.end());
    std::ifstream ifs2(name2);
    std::ofstream ofs(name3);
    char line_[LEN];
    while(!ifs2.eof()) {
        ifs2.getline(line_, LEN);
        std::string line(line_);
        std::string word;
        size_t index = 0;
        int cnt = 0;
        while ((index = line.find(spaces)) != std::string::npos){
            word = line.substr(0, index);
            if (std::binary_search(container.begin(), container.end(), word)){
                cnt += 1;
            }
            line = line.substr(index + 1);
        }
        if (std::binary_search(container.begin(), container.end(), line)){
            cnt += 1;
        }
        *res += cnt;
        ofs << cnt << " " << line_ << std::endl;
    }
}