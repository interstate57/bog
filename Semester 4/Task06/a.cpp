#include "enum.h"
#include "list2.h"
#include "command.h"
#include "time.h"
#include "parser.h"
#include "list.h"
#include "list2_search.h"
#include "hashtable.h"
#include "database.h"

int main(int argc, char* argv[]){
    char* name = 0;
    io_status ret;
    double t = 0;
    int res = 0;
    int k = 0;
    int m = 0;
    FILE* fp;
    if (!(argc == 4 && sscanf(argv[2], "%d", &k) == 0 && sscanf(argv[3], "%d", &m))){
        printf("Usage: %s filename k m\n", argv[0]);
        return 1;
    }
    name = argv[1];
    if (!(fp = fopen(name, "r"))) return -1;
    database data(m, k);
    ret = data.get_list().read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Wrong format in the file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
            case io_status::parsing_error: printf("Parsing error!\n"); break;
            default: break;
        }
        return 3;
    }while(0);
    parser com_parse(stdin);
    command c;
    int fl1 = 0;
    for (list2_node* curr = data.get_list().get_head(); curr; curr = curr->get_next()){
        int res_ = data.get_hash_table().insert(curr);
        if (res_ == -1){
            printf("ERROR\n");
            return 4;
        }
    }
    t = clock();
    char* dop = com_parse.read();
    while (dop){
        command c;
        list answer;
        com_parse.parse(c, dop);
        switch (c.get_command_type()){
            case command_type::quit:
                printf("\n");
                t = (clock() - t) / CLOCKS_PER_SEC;
                printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
                answer.delete_list();
                return 0;
            case command_type::del:
                data.delete_command(c);
                break;
            case command_type::insert:
                data.insert_command(c);
                break;
            case command_type::select:
                data.select_command(c, &res);
                break;
            default:
                break;
        }
        printf("\n");
        dop = com_parse.read();
    }
    return 0;
}