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

static bool read_config(const char* argv0, int& k, int& m) {
    const char* config_name = "config.txt";
    std::unique_ptr<char []> exe_path = std::make_unique<char []>(strlen(argv0) + 1);
    if (!exe_path) return false;
    strcpy(exe_path.get(), argv0);
    char* dir = dirname(exe_path.get());
    if (!dir) return false;

    size_t path_len = strlen(dir) + 1 + strlen(config_name) + 1;
    std::unique_ptr<char []> config_path = std::make_unique<char []>(path_len);
    if (!config_path) return false;
    snprintf(config_path.get(), path_len, "%s/%s", dir, config_name);

    FILE* fp = fopen(config_path.get(), "r");
    if (!fp) return false;

    int found = 0;
    char line[LEN];
    while (fgets(line, sizeof(line), fp)) {
        const char* p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0' || *p == '\n' || *p == '#') continue;
        while (*p) {
            while (*p == ' ' || *p == '\t') p++;
            if (*p == '\0' || *p == '\n' || *p == '#') break;
            char* end = nullptr;
            long v = strtol(p, &end, 10);
            if (end == p) { fclose(fp); return false; }
            if (found == 0) k = (int)v;
            else if (found == 1) m = (int)v;
            found++;
            p = end;
            if (found >= 2) break;
        }
        if (found >= 2) break;
    }
    fclose(fp);
    return found >= 2 && k > 0 && m > 0;
}

int main(int argc, char* argv[]){
    char* name = 0;
    io_status ret;
    double t = 0;
    int res = 0;
    int k = 0;
    int m = 0;
    FILE* fp;
    if (argc != 2 || !read_config(argv[0], k, m)){
        printf("Usage: %s filename\n", argv[0]);
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
        ret = com_parse.parse(c, dop);
        if (ret != io_status::success){
            printf("Parsing error!\n");
            return 3;
        }
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
        dop = com_parse.read();
        printf("\n");
    }
    return 0;
}