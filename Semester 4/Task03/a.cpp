#include "enum.h"
#include "list2.h"
#include "record.h"
#include "time.h"

int main(int argc, char* argv[]){
    char* name = 0;
    char str[LEN] = {};
    int r = 0;
    io_status ret;
    int task = 1, k = 0;
    double t = 0;
    unsigned int len1 = 0, len2 = 0;
    FILE* fp;
    list2 a;
    if (!(argc == 2)){
        printf("Usage: %s filename k\n", argv[0]);
        return 1;
    }
    name = argv[1];
    if (!(fp = fopen(name, "r"))) return -1;
    ret = a.read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Wrong format in the file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
        }
        a.delete_list();
        return 3;
    }while(0);
    while (fgets(str, LEN, stdin)){
        command c;
        list2_node* curr;
        bool ret_parse = c.parse(str);
        if (!ret_parse){
            break;
        }
        for (curr = a.get_head(); curr; curr = curr->get_next()){
            if (c.apply(*curr)){
                curr->print();
            }
        }
        printf("\n");
    }
    if (!feof(stdin)) {
        printf("Wrong format in the file!\n");
        return 4;
    }
    a.delete_list();
    return 0;
}