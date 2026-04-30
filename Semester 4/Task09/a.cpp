#include "enum.h"
#include "list2.h"
#include "command.h"
#include "time.h"
#include "parser.h"
#include "list.h"
#include "list2_search.h"
#include "hashtable.h"
#include "database.h"
#include <libgen.h>
#include <memory>
#include <string.h>

static bool read_config(const char* filename, int& k1, int& m1, int& k2, int& m2) {
    const char* config_name = "config.txt";
    std::unique_ptr<char []> exe_path = std::make_unique<char []>(strlen(filename) + 1);
    if (!exe_path)
        return false;
    strcpy(exe_path.get(), filename);
    char* dir = dirname(exe_path.get());
    if (!dir)
        return false;
    printf ("Executable dir = %s\n", dir);
    size_t path_len = strlen(dir) + 1 + strlen(config_name) + 1;
    std::unique_ptr<char []> config_path = std::make_unique<char []>(path_len);
    if (!config_path)
        return false;
    snprintf(config_path.get(), path_len, "%s/%s", dir, config_name);
    printf ("Config path = %s\n", config_path.get ());
    FILE* fp = fopen(config_path.get(), "r");
    if (!fp)
        return false;

    int found = 0;
    char str[LEN];
    while (fgets(str, sizeof(str), fp)) {
        const char* p = str;
        while (p[0] == ' ' || p[0] == '\t')
            p++;
        if (p[0] == '\0' || p[0] == '\n' || p[0] == '#')
            continue;
        while (p[0]) {
            while (p[0] == ' ' || p[0] == '\t')
                p++;
            if (p[0] == '\0' || p[0] == '\n' || p[0] == '#')
                break;
            char* end = nullptr;
            long v = strtol(p, &end, 10);
            if (end == p) {
                fclose(fp);
                return false;
            }
            if (found == 0)
                k1 = (int)v;
            else if (found == 1)
                m1 = (int)v;
            else if (found == 2)
                k2 = (int)v;
            else if (found == 3)
                m2 = (int)v;
            found++;
            p = end;
            if (found >= 4)
                break;
        }
        if (found >= 4)
            break;
    }
    fclose(fp);
    return found >= 4 && k1 > 0 && m1 > 0 && k2 > 0 && m2 > 0;
}

int main(int argc, char* argv[]){
    char* name = 0;
    io_status ret;
    double t = 0;
    int res = 0;
    int k1 = 0;
    int m1 = 0;
    int k2 = 0;
    int m2 = 0;
    FILE* fp;
    if (argc != 2 || !read_config(argv[0], k1, m1, k2, m2)){
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    name = argv[1];
    if (!(fp = fopen(name, "r"))) return -1;
    database data(k1, m1, k2, m2);
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
        fclose(fp);
        return 3;
    }while(0);
    parser com_parse(stdin);
    command c;
    for (list2_node* curr = data.get_list().get_head(); curr; curr = curr->get_next()){
        int res_ = data.get_solo().insert(curr);
        if (res_ == -1){
            printf("ERROR\n");
            fclose(fp);
            return 4;
        }
        res_ = data.get_kirpichek_i(curr->get_group() - 1).insert(curr);
        if (res_ == -1){
            printf("ERROR\n");
            fclose(fp);
            return 4;
        }
    }
    t = clock();
    char* dop = com_parse.read();
    while (dop){
        //printf("Command : %s\n", dop);
        command c;
        list answer;
        ret = com_parse.parse(c, dop);
        if (ret != io_status::success){
            printf("Parsing error!\n");
            fclose(fp);
            return 3;
        }
        switch (c.get_command_type()){
            case command_type::quit:
                printf("\n");
                t = (clock() - t) / CLOCKS_PER_SEC;
                printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
                answer.delete_list();
                fclose(fp);
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
        dop = com_parse.read();
        printf("\n");
    }
    fclose(fp);
    return 0;
}