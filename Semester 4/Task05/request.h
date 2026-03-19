#ifndef REQUEST_H
#define REQUEST_H

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

class request_7{
    private:
        char spaces[256] = {};
        char dop[LEN] = {};
        int special_symbols[LEN] = {};
        percent_location location;
        int first = -1;
        int second = -1;
        int len_dop = 0;

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
        io_status parse_s(const char* s){
            int i = 0;
            int prev_back = 0;
            int how_many = 0;
            for (int j = 0; s[j]; j++){
                if (is_space(s[j])) {
                    if (prev_back) {
                        prev_back = 0;
                    }
                    continue;
                }

                if (s[j] == BACKSLASH && !prev_back) {
                    prev_back = 1;
                    continue;
                }

                if (s[j] == '%' && !prev_back) {
                    if (how_many == 0 && i == 0) {
                        location = percent_location::start;
                        first = i;
                    }
                    else if (how_many == 0 && i > 0) {
                        first = i;
                    }
                    else if (how_many == 1) {
                        location = percent_location::both;
                        second = i;
                    }
                    how_many += 1;
                }

                dop[i] = s[j];
                special_symbols[i] = (s[j] == '%' && !prev_back);
                if (s[j] == '%' && !prev_back && s[j+1] && s[j+1] == '_') {
                    j += 1;
                    dop[i] = '_';
                }
                i++;
                prev_back = 0;
            }
            len_dop = i;
            dop[i] = '\0';
            if (prev_back)
                return io_status::parsing_error;

            if (how_many == 1) {
                if (first + 1 == i) {
                    location = percent_location::end;
                } else if (first > 0) {
                    location = percent_location::middle;
                }
            }
            return io_status::success;
        }

        int context_fit(const char* s) {
            int len_s = strlen(s);
            int len_a = 0, len_b = 0;
            int offset = 0;
            const char * occ;
            char temp;
            switch (location) {
                case percent_location::start:
                    len_a = len_dop - 1;
                    offset = len_s - len_a;
                    if (strncmp(dop + 1, s + offset, len_a) != 0)
                        return 0;
                    if (dop[first] == '_' && len_s <= len_a)
                        return 0;
                    return 1;
                case percent_location::end:
                    len_a = len_dop - 1;
                    if (strncmp(dop, s, len_a) != 0)
                        return 0;
                    if (dop[first] == '_' && len_s <= len_a)
                        return 0;
                    return 1;
                case percent_location::middle:
                    len_a = first;
                    len_b = len_dop - first - 1;
                    offset = len_s - len_b;
                    if (strncmp(dop, s, len_a) != 0)
                        return 0;
                    if (strncmp(dop + first + 1, s + offset, len_b) != 0)
                        return 0;
                    if (dop[first] == '_' && len_s <= len_a + len_b)
                        return 0;
                    return 1;
                case percent_location::both:
                    len_a = len_dop - 2;

                    temp = dop[second];
                    dop[second] = '\0';
                    occ = strstr(s, dop + 1);
                    dop[second] = temp;

                    if (!occ)
                        return 0;
                    if (dop[first] == '_' && occ == s)
                        return 0;
                    if (dop[second] == '_' && (int) strlen(occ) <= len_a)
                        return 0;
                    return 1;
                default:
                    return 0;
            }
            return 1;
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

#endif