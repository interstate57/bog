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
        ~request_b_tree() {
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

class request_rb_tree {
    private:
        rb_tree<std::unique_ptr<char *>> *tree = nullptr;
	    char spaces[256] = {};
    public:
        request_rb_tree() {	
            tree = new rb_tree<std::unique_ptr<char *>>();
        }
        ~request_rb_tree() {
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
                res = tree->add_word(dop);
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
                if (tree->find_word(dop) == 0) {
                    str[j + i] = del_char;
                    return 0;
                }
                str[j + i] = del_char;
                j += i;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 1;
	    }
};

enum class sravneniya{
    ls,
    gr,
    le,
    ge,
    e,
    ne,
};
        
class request_4{
    private:
        char spaces[256] = {};
        sravneniya x_symbols[LEN] = {};
        char* s_words[LEN] = {};
        int cnt_words = 0;
    public:
        request_4() = default;
        ~request_4() = default;
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        io_status parse_s_and_x(char* s, char* x, char* t){
            char* dop1;
            char* dop2;
            char* sr = strtok_r(x, t, &dop1);
            char* s_word = strtok_r(x, t, &dop2);
            int i = 0;
            while (sr){
                if (!s_word)
                    return io_status::parsing_error;
                s_words[i] = s_word;
                if (strcmp(sr, "<") == 0){
                    x_symbols[i] = sravneniya::ls;
                }
                else if (strcmp(sr, ">") == 0){
                    x_symbols[i] = sravneniya::gr;
                }
                else if (strcmp(sr, "<=") == 0){
                    x_symbols[i] = sravneniya::le;
                }
                else if (strcmp(sr, ">=") == 0){
                    x_symbols[i] = sravneniya::ge;
                }
                else if (strcmp(sr, "=") == 0){
                    x_symbols[i] = sravneniya::e;
                }
                else if (strcmp(sr, "<>") == 0){
                    x_symbols[i] = sravneniya::ne;
                }
                else{
                    return io_status::parsing_error;
                }
                i += 1;
                sr = strtok_r(x, t, &dop1);
                s_word = strtok_r(x, t, &dop2);
            }
            if (s_word){
                return io_status::parsing_error;
            }
            cnt_words = i;
            return io_status::success;
        }
        int context_fit(char* str){
            int i, j, k;
            char del_char = 0;
            for (j = 0; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            for (; str[j];) {
                for (i = 0; str[j + i] && spaces[(unsigned int)str[j + i]] != 1; ++i);
                del_char = str[j + i];
                str[j + i] = '\0';
                for (k = 0; k < cnt_words; k++){
                    switch(x_symbols[k]){
                        case sravneniya::ls:
                            if (strcmp(str + j, s_words[k]) < 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                        case sravneniya::gr:
                            if (strcmp(str + j, s_words[k]) > 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                        case sravneniya::le:
                            if (strcmp(str + j, s_words[k]) <= 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                        case sravneniya::ge:
                            if (strcmp(str + j, s_words[k]) >= 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                        case sravneniya::e:
                            if (strcmp(str + j, s_words[k]) == 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                        case sravneniya::ne:
                            if (strcmp(str + j, s_words[k]) != 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                    }
                }
                str[j + i] = del_char;
                j += i;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
        }
};

class request_5{
    private:
        char spaces[256] = {};
        sravneniya x_symbols[LEN] = {};
        char* s_words[LEN] = {};
        int cnt_words = 0;
    public:
        request_5() = default;
        ~request_5() = default;
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        io_status parse_s_and_x(char* s, char* x, char* t){
            char* dop1;
            char* dop2;
            char* sr = strtok_r(x, t, &dop1);
            char* s_word = strtok_r(x, t, &dop2);
            int i = 0;
            while (sr){
                if (!s_word)
                    return io_status::parsing_error;
                s_words[i] = s_word;
                if (strcmp(sr, "<") == 0){
                    x_symbols[i] = sravneniya::ls;
                }
                else if (strcmp(sr, ">") == 0){
                    x_symbols[i] = sravneniya::gr;
                }
                else if (strcmp(sr, "<=") == 0){
                    x_symbols[i] = sravneniya::le;
                }
                else if (strcmp(sr, ">=") == 0){
                    x_symbols[i] = sravneniya::ge;
                }
                else if (strcmp(sr, "=") == 0){
                    x_symbols[i] = sravneniya::e;
                }
                else if (strcmp(sr, "<>") == 0){
                    x_symbols[i] = sravneniya::ne;
                }
                else{
                    return io_status::parsing_error;
                }
                i += 1;
                sr = strtok_r(x, t, &dop1);
                s_word = strtok_r(x, t, &dop2);
            }
            if (s_word){
                return io_status::parsing_error;
            }
            cnt_words = i;
            return io_status::success;
        }
        int context_fit(char* str){
            int i, j, k;
            char del_char = 0;
            for (j = 0; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            for (; str[j];) {
                for (i = 0; str[j + i] && spaces[(unsigned int)str[j + i]] != 1; ++i);
                del_char = str[j + i];
                str[j + i] = '\0';
                for (k = 0; k < cnt_words; k++){
                    switch(x_symbols[k]){
                        case sravneniya::ls:
                            if (strcmp(str + j, s_words[k]) >= 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                        case sravneniya::gr:
                            if (strcmp(str + j, s_words[k]) <= 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                        case sravneniya::le:
                            if (strcmp(str + j, s_words[k]) > 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                        case sravneniya::ge:
                            if (strcmp(str + j, s_words[k]) < 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                        case sravneniya::e:
                            if (strcmp(str + j, s_words[k]) != 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                        case sravneniya::ne:
                            if (strcmp(str + j, s_words[k]) == 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                    }
                }
                str[j + i] = del_char;
                j += i;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 1;
        }
};