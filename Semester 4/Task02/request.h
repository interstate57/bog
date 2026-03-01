#include <stdio.h>
#include "io_status.h"
#include "b_tree.h"
#include "rb_tree.h"

#define BACKSLASH '\\'


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
            char* s_word = strtok_r(s, t, &dop2);
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
                sr = strtok_r(nullptr, t, &dop1);
                s_word = strtok_r(nullptr, t, &dop2);
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
                            break;
                        case sravneniya::gr:
                            if (strcmp(str + j, s_words[k]) > 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                            break;
                        case sravneniya::le:
                            if (strcmp(str + j, s_words[k]) <= 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                            break;
                        case sravneniya::ge:
                            if (strcmp(str + j, s_words[k]) >= 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                            break;
                        case sravneniya::e:
                            if (strcmp(str + j, s_words[k]) == 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                            break;
                        case sravneniya::ne:
                            if (strcmp(str + j, s_words[k]) != 0){
                                str[j + i] = del_char;
                                return 1;
                            }
                            break;
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
            char* s_word = strtok_r(s, t, &dop2);
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
                sr = strtok_r(nullptr, t, &dop1);
                s_word = strtok_r(nullptr, t, &dop2);
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
                            break;
                        case sravneniya::gr:
                            if (strcmp(str + j, s_words[k]) <= 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                            break;
                        case sravneniya::le:
                            if (strcmp(str + j, s_words[k]) > 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                            break;
                        case sravneniya::ge:
                            if (strcmp(str + j, s_words[k]) < 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                            break;
                        case sravneniya::e:
                            if (strcmp(str + j, s_words[k]) != 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                            break;
                        case sravneniya::ne:
                            if (strcmp(str + j, s_words[k]) == 0){
                                str[j + i] = del_char;
                                return 0;
                            }
                            break;
                    }
                }
                str[j + i] = del_char;
                j += i;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }            
            return 1;
        }
};

class request_6{
    private:
        char spaces[256] = {};
        char dop[LEN] = {};
        int special_symbols[LEN] = {};
        int begining_of_words[LEN] = {};
        int cnt_words = 0;
    public:
        request_6() = default;
        ~request_6() = default;
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        int is_space(char symbol) {
            return spaces[(unsigned int)symbol] == 1;
        }
        io_status parse_s(char* s){
            int inside_word = 0;
            int prev_back = 0;
            int i = 0;

            for (int j = 0; s[j]; j++){
                //printf("");
                if (is_space(s[j])) {
                    if (prev_back) {
                        prev_back = 0;
                    }
                    if (inside_word) {
                        inside_word = 0;
                    }
                    continue;
                }
                
                if (s[j] == BACKSLASH && !prev_back) {
                    prev_back = 1;
                    continue;
                }

                if (!inside_word) {
                    begining_of_words[cnt_words] = i;
                    inside_word = 1;
                    cnt_words += 1;
                }
                printf("%d %d %c\n", i, j, s[j]);
                dop[i] = s[j];
                special_symbols[i] = (s[j] == '_' && !prev_back);
                i++;
                prev_back = 0;
            }
            begining_of_words[cnt_words] = i;
            if (prev_back)
                return io_status::parsing_error;
            return io_status::success;
        }

        
        int context_fit(char* str){
            int i, j;
            int l;
            int len;
            /*
            printf("begining: ");
            for (i = 0; i <= cnt_words; ++i){
                printf("%d ", begining_of_words[i]);
            }
            printf("\n");
            printf("dop: " );
            for (i = 0; dop[i];){
                printf("%c ", dop[i]);
                i++;
            }
            printf("\n");
            */
            for (j = 0; str[j] && is_space(str[j]); j++);
            for (; str[j];) {
                for (i = 0; str[j + i] && !is_space(str[j + i]); ++i);
                len = i;
                for (int k = 0; k < cnt_words; k++){
                    bool error = false;
                    if (begining_of_words[k + 1] - begining_of_words[k] != len)
                        continue;
                    int nach_slova = begining_of_words[k];
                    for (l = 0; l < len; l++){
                        if (special_symbols[nach_slova + l])
                            continue;
                        else{
                            if (dop[nach_slova + l] == str[j + l])
                                continue;
                            else{
                                error = true;
                                break;
                            }
                        }
                    }
                    if ((l == len) && !error)
                        return 1;
                }
                j += len;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
        }
};

class pair{
    private:
        char a = 0;
        char b = 0;
    public:
        pair() = default;
        pair(char x, char y){
            a = x;
            b = y;
        }
        ~pair() = default;

        bool letter_in_between(char x){
            if (x >= a && x <= b)
                return true;
            return false;
        }
        char get_a(){
            return a;
        }
        char get_b(){
            return b;
        }

};

class request_8{
    private:
        char spaces[256] = {};
        char dop[LEN] = {};
        int special_symbols[LEN] = {};
        int begining_of_words[LEN] = {};
        pair check[LEN] = {};
        int cnt_words = 0;
    public:
        request_8() = default;
        ~request_8() = default;
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        int is_space(char symbol) {
            return spaces[(unsigned int)symbol] == 1;
        }
        io_status parse_s(char* s){
            int inside_word = 0;
            int prev_back = 0;
            int i = 0;

            for (int j = 0; s[j]; j++){
                //printf("");
                if (is_space(s[j])) {
                    if (prev_back) {
                        prev_back = 0;
                    }
                    if (inside_word) {
                        inside_word = 0;
                    }
                    continue;
                }
                
                if (s[j] == BACKSLASH && !prev_back) {
                    prev_back = 1;
                    continue;
                }

                if (!inside_word) {
                    begining_of_words[cnt_words] = i;
                    inside_word = 1;
                    cnt_words += 1;
                }
                if (s[j] == '[' && !prev_back){
                    int k = 1;
                    char a = 0;
                    char b = 0;
                    int zakr = 0;
                    for (k; s[j + k]; k++){
                        if (k == 1){
                            a = s[j + k];
                            continue;
                        }
                        if (k == 2){
                            if (s[j + k] != '-')
                                return io_status::parsing_error;
                            continue;
                        }
                        if (k == 3){
                            b = s[j + k];
                            continue;
                        }
                        if (k == 4){
                            zakr = s[j + k] == ']' ? 1 : 0;
                            break;
                        }
                    }
                    if (!zakr && k != 4)
                        return io_status::parsing_error;
                    dop[i] = s[j];
                    special_symbols[i] = 1;
                    check[i] = pair(a, b);
                    j += k;
                    i++;
                    prev_back = 0;
                }
                dop[i] = s[j];
                i++;
                prev_back = 0;
            }
            begining_of_words[cnt_words] = i;
            if (prev_back)
                return io_status::parsing_error;
            return io_status::success;
        }

        
        int context_fit(char* str){
            int i, j;
            int l;
            int len;
            
            printf("begining: ");
            for (i = 0; i <= cnt_words; ++i){
                printf("%d ", begining_of_words[i]);
            }
            printf("\n");
            printf("dop: " );
            for (i = 0; dop[i];){
                printf("%c ", dop[i]);
                i++;
            }
            printf("\n");
            for (j = 0; str[j] && is_space(str[j]); j++);
            for (; str[j];) {
                for (i = 0; str[j + i] && !is_space(str[j + i]); ++i);
                len = i;
                for (int k = 0; k < cnt_words; k++){
                    bool error = false;
                    if (begining_of_words[k + 1] - begining_of_words[k] != len)
                        continue;
                    int nach_slova = begining_of_words[k];
                    for (l = 0; l < len; l++){
                        if (special_symbols[nach_slova + l])
                            if (!check[nach_slova + l].letter_in_between(str[j + l])){
                                error = true;
                                break;
                            }
                        else{
                            if (dop[nach_slova + l] == str[j + l])
                                continue;
                            else{
                                error = true;
                                break;
                            }
                        }
                    }
                    if ((l == len) && !error)
                        return 1;
                }
                j += len;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
        }


};