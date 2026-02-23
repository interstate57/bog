#include <stdio.h>
#include "io_status.h"
#include "b_tree.h"
#include "rb_tree.h"


class request_b_tree {
    private:
        b_tree<std::unique_ptr<char *>> *tree = nullptr;
	    char spaces[256] = {};
    public:
        request_b_tree(int i = 0) {	
            tree = new b_tree<std::unique_ptr<char *>>(i);
        }
        request_b_tree() {
            delete tree;
            tree = nullptr;
        }
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        io_status parse_s(char* s, const char* t){
            char *word = strtok(s, t);
            io_status res;
            for (; word;) {
                std::unique_ptr<char *> dop = std::make_unique<char *>(word);
                res = tree->add_value(dop);
                if (res != io_status::success) {
                    return res;
                }
                word = strtok(nullptr, t);
            }
            return io_status::success;
        }
        // годится ли строка str под условие задачи
        int context_fit(char *str) {
            //printf("%s\n", str);
            int i, j;
            char del_char = 0;
            for (j = 0; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            for (; str[j];) {
                for (i = 0; str[j + i] && spaces[(unsigned int)str[j + i]] != 1; ++i);
                del_char = str[j + i];
                str[j + i] = '\0';
                std::unique_ptr<char *> dop = std::make_unique<char *>(str + j);
                if (tree->find_word(dop) == 1) {
                    str[j + i] = del_char;
                    return 1;
                }
                str[j + i] = del_char;
                j += i;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
	    }
};

        