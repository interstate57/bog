#include "enum.h"
#include "list2.h"
#include "command.h"
#include "time.h"
#include "parser.h"
#include "list.h"

int main(int argc, char* argv[]){
    char* name = 0;
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
            default: break;
        }
        a.delete_list();
        return 3;
    }while(0);
    parser com_parse(stdin);
    command c;
    int fl1 = 0;
    list answer;
    t = clock();
    while (com_parse.read(c) == io_status::success){
        switch (c.get_command_type()){
            case command_type::quit:
                printf("\n");
                t = (clock() - t) / CLOCKS_PER_SEC;
                printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
                a.delete_list();
                answer.delete_list();
                return 0;
            case command_type::del:
                a.delete_command(c);
                
                break;
            case command_type::insert:
                a.insert_command(c);
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
                break;
            default:
                break;
        }
        printf("\n");
        c.clear();
    }
    a.delete_list();
    answer.delete_list();
    return 0;
}