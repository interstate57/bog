#include <stdio.h>
#include "enum.h"


#include <memory>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>




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

        
        int context_fit(const char* str){
            int i, j;
            int l;
            int len;
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
        bool letter_not_in_between(char x){
            if (x < a || x > b)
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

class request_7 {
    private:
        char dop[LEN] = {};
        char special_symbols[LEN] = {};
        char spaces[256] = {};
        int words_index[LEN/2 + 1] = {};
        int cnt_words = 0;
    public:
        request_7() = default;
        ~request_7() = default;
        void parse_t(const char* t){
            int i;
            for (i = 0; t[i]; ++i) { 
                spaces[(unsigned int)t[i]] = 1;
            }
        }
        int is_space(char symbol) {
            return spaces[(unsigned int)symbol] == 1;
        }
	    io_status parse_s(const char *s) {
            int i = 0, j = 0, k = 0;
            for(i = 0; s[i] && is_space(s[i]); ++i);
            words_index[j++] = k;
            for (; s[i]; ++i) {
                if (is_space(s[i])) {
                    for(; s[i] && is_space(s[i]); ++i);
                    words_index[j++] = k;
                    --i;
                    continue;
                }
                if (s[i] == '\\') {
                    i++;
                    if (!s[i] ||is_space(s[i])) {
                        return io_status::parsing_error;
                    }
                    else {
                        dop[k] = s[i];
                    }
                    
                }
                else if (s[i] == '%') {
                    special_symbols[k] = 1;
                    dop[k] = '%';
                }
                else {
                    dop[k] = s[i];
                }
                k++;
            }
            words_index[j++] = k;
            cnt_words = j-1;
            return io_status::success;
        }
        int context_fit(char *str) {
            int a_ind, i, k, len, s_begin, j, s_len;
            char symb = '\0';
            for (a_ind = 0; str[a_ind] && is_space(str[a_ind]); ++a_ind);
            for (; str[a_ind];) {
                for (i = 0; str[a_ind + i] && !is_space(str[a_ind + i]); ++i);
                len = i;
                for (k = 0; k < cnt_words; ++k) {
                    s_begin = words_index[k];
                    s_len = words_index[k + 1] - words_index[k];
                    if (special_symbols[s_begin] == 1 && s_len > 1 && special_symbols[s_begin + s_len - 1] == 1) {
                        dop[s_begin + s_len - 1] = '\0';
                        symb = str[a_ind + i];
                        if (str[a_ind + i]) {
                            str[a_ind + i] = '\0';
                        }
                        if (strstr(str + a_ind, dop + s_begin + 1) != nullptr) {
                            str[a_ind + i] = symb;
                            symb = '\0';
                            dop[s_begin + s_len - 1] = '%';
                            return 1;
                        }
                        str[a_ind + i] = symb;
                        symb = '\0';
                        dop[s_begin + s_len - 1] = '%';
                    }
                    else { 
                        int flag = 0;
                        for (i = 0; i < s_len; ++i) {
                            if (flag == 1) {
                                break;
                            }
                            if (special_symbols[s_begin + i] == 1) {
                                for (j = 1; j < s_len - i; ++j) {
                                    if (i + j > len || dop[s_begin + s_len - j] != str[a_ind + len - j]) {
                                        break;
                                    }
                                }
                                if (j == s_len - i) {
                                    return 1;
                                }
                                else {
                                    flag = 1;
                                }
                            }
                            else {
                                if (!str[a_ind + i] || dop[s_begin + i] != str[a_ind + i]) {
                                    break;
                                }
                            }
                        }
                        if (i == s_len && len == s_len) {
                            return 1;
                        }
                    }
                }
                a_ind += len;
                for (; str[a_ind] && is_space(str[a_ind]); ++a_ind);
            }
            return 0;
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
                    for (; s[j + k]; k++){
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
                    if (!zakr || k != 4)
                        return io_status::parsing_error;
                    dop[i] = s[j];
                    special_symbols[i] = 1;
                    check[i] = pair(a, b);
                    j += k;
                    i++;
                    prev_back = 0;
                }
                else{
                    dop[i] = s[j];
                    i++;
                    prev_back = 0;
                }
            }
            begining_of_words[cnt_words] = i;
            if (prev_back)
                return io_status::parsing_error;
            return io_status::success;
        }

        
        int context_fit(const char* str){
            int i, j;
            int l;
            int len;
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
                        if (special_symbols[nach_slova + l]){
                            if (!(check[nach_slova + l].letter_in_between(str[j + l]))){
                                error = true;
                                break;
                            }
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
                    if ((l == len) && !error){
                        return 1;
                    }
                    
                }
                j += len;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
        }


};

class request_9{
    private:
        char spaces[256] = {};
        char dop[LEN] = {};
        int special_symbols[LEN] = {};
        int begining_of_words[LEN] = {};
        pair check[LEN] = {};
        int cnt_words = 0;
    public:
        request_9() = default;
        ~request_9() = default;
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
                    for (; s[j + k]; k++){
                        if (k == 1){
                            if (s[j + k] != '^')
                                return io_status::parsing_error;
                            continue;
                        }
                        if (k == 2){
                            a = s[j + k];
                            continue;
                        }
                        if (k == 3){
                            if (s[j + k] != '-')
                                return io_status::parsing_error;
                            continue;
                        }
                        if (k == 4){
                            b = s[j + k];
                            continue;
                        }
                        if (k == 5){
                            zakr = s[j + k] == ']' ? 1 : 0;
                            break;
                        }
                    }
                    if (!zakr || k != 5)
                        return io_status::parsing_error;
                    dop[i] = s[j];
                    special_symbols[i] = 1;
                    check[i] = pair(a, b);
                    j += k;
                    i++;
                    prev_back = 0;
                }
                else{
                    dop[i] = s[j];
                    i++;
                    prev_back = 0;
                }
            }
            begining_of_words[cnt_words] = i;
            if (prev_back)
                return io_status::parsing_error;
            return io_status::success;
        }

        
        int context_fit(const char* str){
            int i, j;
            int l;
            int len;
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
                        if (special_symbols[nach_slova + l]){
                            if (!(check[nach_slova + l].letter_not_in_between(str[j + l]))){
                                error = true;
                                break;
                            }
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
                    if ((l == len) && !error){
                        return 1;
                    }
                    
                }
                j += len;
                for (; str[j] && spaces[(unsigned int)str[j]] == 1; j++);
            }
            return 0;
        }


};