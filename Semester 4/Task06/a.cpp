#include "enum.h"
#include "list2.h"
#include "command.h"
#include "time.h"
#include "parser.h"
#include "list.h"
#include "list2_search.h"
#include "hashtable.h"

int main(int argc, char* argv[]){
    char* name = 0;
    io_status ret;
    double t = 0;
    int res = 0;
    int k = 0;
    int m = 0;
    FILE* fp;
    list2 a;
    if (!(argc == 4 && sscanf(argv[2], "%d", &k) == 0 && sscanf(argv[3], "%d", &m))){
        printf("Usage: %s filename k m\n", argv[0]);
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
            default: break;
        }
        a.delete_list();
        return 3;
    }while(0);
    parser com_parse(stdin);
    command c;
    int fl1 = 0;
    hash_table data(k, m);
    for (list2_node* curr = a.get_head(); curr; curr= curr->get_next()){
        int res_ = data.insert(curr);
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
                a.delete_list();
                return 0;
            case command_type::del:
                if (c.get_c_name() == condition::eq){
                    data.get_i(data.hash_function(c.get_name()))->delete_list2_search(c, &a);
                }
                else{
                    
                }
                a.delete_command(c);
                break;
            case command_type::insert:
                int res_ = a.insert_command(c);
                if (res_ == 0)
                    data.insert(a.get_head());
                break;
            case command_type::select:
                fl1 = select_command(a.get_head(), &answer, c);
                if (fl1 == 1){
                    printf("Cannot allocate memory!\n"); 
                    a.delete_list();
                    answer.delete_list();
                    return 5;
                }
                res += answer.get_length();
                answer.print(c);
                answer.delete_list();
                break;
            default:
                break;
        }
        printf("\n");
        dop = com_parse.read();
    }
    a.delete_list();
    return 0;
}