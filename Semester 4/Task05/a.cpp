#include "enum.h"
#include "list2.h"
#include "command.h"
#include "time.h"

int main(int argc, char* argv[]){
    char* name = 0;
    char str[LEN] = {};
    io_status ret;
    double t = 0;
    int res = 0;
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
            case io_status::parsing_error: printf("Parsing error!\n"); break;
        }
        a.delete_list();
        return 3;
    }while(0);
    parser com_parse(stdin);
    command c;
    while (com_parse.read(c) == io_status::success){
        list2_node* curr;
        for (curr = a.get_head(); curr; curr = curr->get_next()){
            if (c.apply(*curr)){
                curr->print(c.get_ordering(), stdout);
                res += 1;
            }
        }
        printf("\n");
    }
    if (!feof(stdin)) {
        printf("Wrong format in the file!\n");
        a.delete_list();
        return 4;
    }
    printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
    a.delete_list();
    return 0;
}