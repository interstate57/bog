#include "time.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>

#include "io_status.h"

#define LEN 1234


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

io_status solve5(char* name1, char* name2, char* name3, char* spaces, int* res);

static void insert_words(std::string line, const char* spaces, std::set<std::string>& container){
    size_t index = 0;
    std::string word;
    while ((index = line.find_first_of(spaces)) != std::string::npos){
        word = line.substr(0, index);
        container.insert(word);
        line = line.substr(index + 1);
    }
    container.insert(line);
}

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
    io_status st = solve5(name1, name2, name3, spaces, &res);
    if (st != io_status::success) {
        printf("Wrong file!\n");
        return -1;
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    return 0;
}

io_status solve5(char* name1, char* name2, char* name3, char* spaces, int* res){
    std::ifstream ifs1(name1);
    if (!ifs1.is_open())
        return io_status::wrong_file;
    std::set <std::string> container;
    std::string buf;
    while(std::getline(ifs1, buf)) {
        insert_words(buf, spaces, container);
    }
    std::ifstream ifs2(name2);
    if (!ifs2.is_open())
        return io_status::wrong_file;
    std::ofstream ofs(name3);
    if (!ofs.is_open())
        return io_status::wrong_file;
    std::string line;
    while(std::getline(ifs2, line)) {
        std::string line_(line);
        std::string word;
        size_t index = 0;
        int cnt = 0;
        while ((index = line.find_first_of(spaces)) != std::string::npos){
            word = line.substr(0, index);
            if (container.find(word) != container.end()){
                cnt += 1;
            }
            line = line.substr(index + 1);
        }
        if (container.find(line) != container.end()){
            cnt += 1;
        }
        *res += cnt;
        ofs << cnt << " " << line_ << std::endl;
    }
    return io_status::success;
}