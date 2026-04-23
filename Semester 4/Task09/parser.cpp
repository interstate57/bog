#include "parser.h"
#include "enum.h"

char* parser::read(FILE* fp){
    buf[0] = '\0';
    int i = 0;
    char line[LEN];
    while (fgets(line, LEN, fp)) {
        char* semi = strchr(line, ';');
        size_t take = semi ? (size_t)(semi - line) : strlen(line);
        for (size_t p = 0; p < take; ++p) {
            if (i >= LEN - 2) return nullptr;
            char s = line[p];
            buf[i++] = (s == '\n' || s == '\t' || s == '\r') ? ' ' : s;
        }
        if (semi) {
            buf[i] = ';';
            i++;
            buf[i] = '\0';
            return buf + skip_spaces(buf);
        }
    }
    return nullptr;
}
bool parser::is_spaces(const char s){
    return (s == ' ' || s == '\t' || s == '\n');
}
int parser::skip_spaces(const char* str){
    int i;
    for (i = 0; str[i]; i++){
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return i;
    }
    return i;
}
io_status parser::parse(command& cmd, char* string){
    int i = 0;
    int j = 0;
    for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
    int len_first_word = j - i;
    if (strncmp(string, "quit", len_first_word) == 0){
        cmd.com_type = command_type::quit;
        i = j;
    }
    else if (strncmp(string, "stop", len_first_word) == 0){
        cmd.com_type = command_type::stop;
        i = j;
    }
    else if (len_first_word == 6){
        if (strncmp(string, "insert", len_first_word) == 0)
            cmd.com_type = command_type::insert;
        else if (strncmp(string, "delete", len_first_word) == 0)
            cmd.com_type = command_type::del;
        else if (strncmp(string, "select", len_first_word) == 0)
            cmd.com_type = command_type::select;
        else
            return io_status::parsing_error;
        i = j;
    }
    else
        return io_status::parsing_error;
    switch (cmd.com_type){
        case command_type::insert:
            return parse_insert(cmd, string + i);
        case command_type::del:
            return parse_delete(cmd, string + i);
        case command_type::select:
            return parse_select(cmd, string + i);
        case command_type::quit:
            return parse_quit(string + i);
        default:
            return io_status::parsing_error;
    }
}
io_status parser::parse_quit(const char* string){
    //printf("%s\n", string);
    if (string[0] == ';')
        return io_status::success;
    return io_status::parsing_error;
}
io_status parser::parse_insert(command& cmd, char* string){
    int i = 0;
    int j = 0;
    char dop;
    i += skip_spaces(string);
    if (string[i] != '(')
        return io_status::parsing_error;
    i += 1;
    for (j = i; string[j] && string[j] != ','; j++);
    dop = ',';
    string[j] = '\0';
    cmd.set_name(string + i);
    string[j] = dop;
    i = j + 1;
    i += skip_spaces(string + i);
    for (j = i; string[j] && string[j] != ','; j++);
    dop = ',';
    string[j] = '\0';
    int phone = std::atoi(string + i);
    cmd.set_phone(phone);
    string[j] = dop;
    i = j + 1;
    i += skip_spaces(string + i);
    for (j = i; string[j] && string[j] != ')'; j++);
    dop = ')';
    string[j] = '\0';
    int group = std::atoi(string + i);
    cmd.set_group(group);
    string[j] = dop;
    i = j + 1;
    i += skip_spaces(string + i);
    if (string[i] != ';')
        return io_status::parsing_error;
    return io_status::success;
}
io_status parser::parse_delete(command& cmd, const char* string){
    //printf("%s\n", string);
    int i = 0;
    int j = 0;
    if (string[i] != ';'){
        i += skip_spaces(string + i);
        for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
        int len = j - i;
        if (strncmp(string + i, "where", len) == 0){
            i = j;
            i += skip_spaces(string + i);
            //printf("%s\n", string + i);
            bool second_res = parse_after_where(cmd, string + i);
            if (!second_res)
                return io_status::parsing_error;
        }
        else{
            return io_status::parsing_error;
        }
    }
    return io_status::success;
}
io_status parser::parse_select(command& cmd, const char* string){
    int i = 0;
    i += skip_spaces(string);
    bool ret = parse_ordering(cmd, string + i);
    if (!ret)
        return io_status::parsing_error;
    return io_status::success;
}
bool parser::parse_ordering (command& cmd, const char* string){
    //printf("%s\n", string);
    int i = 0;
    int j = 0;
    i += skip_spaces(string);
    if (string[i] == '*'){
        cmd.c_order[0] = ordering::name;
        cmd.c_order[1] = ordering::phone;
        cmd.c_order[2] = ordering::group;
        i += 1;
        i += skip_spaces(string + i);
        return parse_select_suffix(cmd, string + i);
    }
    else{
        for (j = i; string[j] && (string[j] != ',' && string[j] != ' ' && string[j] != ';'); j++);
        int len_first_word = j - i;
        //printf("%d\n", len_first_word);
        if (len_first_word == 5){
            if (strncmp(string + i, "phone", len_first_word) == 0)
                cmd.c_order[0] = ordering::phone;
            else if (strncmp(string + i, "group", len_first_word) == 0)
                cmd.c_order[0] = ordering::group;
            else
                return 0;
        }
        else if (len_first_word == 4 && strncmp(string + i, "name", len_first_word) == 0){
            cmd.c_order[0] = ordering::name;
        }
        else
            return 0;
        
        i = j;
        i += skip_spaces(string + i);
        if (string[i] == ';')
            return parse_select_suffix(cmd, string + i);
        if (string[i] == ','){
            i += 1;
            i += skip_spaces(string + i);
        }
        for (j = i; string[j] && (string[j] != ',' && string[j] != ' ' && string[j] != ';'); j++);
        int len_second_word = j - i;
        //printf("%d\n", len_second_word);
        if (len_second_word == 5){
            if (strncmp(string + i, "phone", len_second_word) == 0)
                cmd.c_order[1] = ordering::phone;
            else if (strncmp(string + i, "group", len_second_word) == 0){
                cmd.c_order[1] = ordering::group;
            }
            else if (strncmp(string + i, "where", len_second_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                bool second_res = parse_after_where(cmd, string + i);
                if (!second_res)
                    return 0;
                return 1;
            }
            else if (strncmp(string + i, "order", len_second_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                for (j = i; string[j] && string[j] != ' '; j++);
                if (!(j - i == 2 && strncmp(string + i, "by", 2) == 0))
                    return 0;
                i = j;
                i += skip_spaces(string + i);
                return parse_after_order_by(cmd, string + i);
            }
            else
                return 0;
        }
        else if (len_second_word == 4 && strncmp(string + i, "name", len_second_word) == 0)
            cmd.c_order[1] = ordering::name;
        else
            return 0;
        i = j;
        i += skip_spaces(string + i);
        if (string[i] == ';')
            return parse_select_suffix (cmd, string + i);
        if (string[i] == ','){
            i += 1;
            i += skip_spaces(string + i);
        }
        for (j = i; string[j] && string[j] != ' ' && string[j] != ';'; j++);
        int len_third_word = j - i;
        if (len_third_word == 5){
            if (strncmp(string + i, "phone", len_third_word) == 0)
                cmd.c_order[2] = ordering::phone;
            else if (strncmp(string + i, "group", len_third_word) == 0)
                cmd.c_order[2] = ordering::group;
            else if (strncmp(string + i, "where", len_third_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                bool second_res = parse_after_where(cmd, string + i);
                if (!second_res)
                    return 0;
                return 1;
            }
            else if (strncmp(string + i, "order", len_third_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                for (j = i; string[j] && string[j] != ' '; j++);
                if (!(j - i == 2 && strncmp(string + i, "by", 2) == 0))
                    return 0;
                i = j;
                i += skip_spaces(string + i);
                return parse_after_order_by(cmd, string + i);
            }
            else
                return 0;
        }
        else if (len_third_word == 4 && strncmp(string + i, "name", len_third_word) == 0)
            cmd.c_order[2] = ordering::name;
        else
            return 0;
        i = j;
        i += skip_spaces(string + i);
        return parse_select_suffix (cmd, string + i);
    }
}

bool parser::parse_select_suffix (command& cmd, const char* string){
    int i = skip_spaces(string);
    if (string[i] == ';')
        return true;
    int j;
    for (j = i; string[j] && string[j] != ' ' && string[j] != ';'; j++);
    int len = j - i;
    if (len == 5 && strncmp(string + i, "where", len) == 0){
        i = j;
        i += skip_spaces(string + i);
        return parse_after_where(cmd, string + i);
    }
    if (len == 5 && strncmp(string + i, "order", len) == 0){
        i = j;
        i += skip_spaces(string + i);
        for (j = i; string[j] && string[j] != ' '; j++);
        if (!(j - i == 2 && strncmp(string + i, "by", 2) == 0))
            return false;
        i = j;
        i += skip_spaces(string + i);
        return parse_after_order_by(cmd, string + i);
    }
    return false;
}
bool parser::parse_after_where (command& cmd, const char* string){
    //printf("%s\n", string);
    /*for (int k = 0; k < 3; k++){
        std::cout << c_order[k];
        printf("\n");
    }*/
    int i = 0;
    int j = 0;
    
    bool mini_res = parse_condition(cmd, string, &i);
    if (!mini_res)
        return 0;
    if (i == 0){
        return 1;
    }
    else{
        for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
        int len_first_word = j - i;
        if (len_first_word == 2 && strncmp(string + i, "or", len_first_word) == 0){
            if (cmd.op == operation::land)
                return 0;
            cmd.op = operation::lor;
        }
        else if (len_first_word == 3 && strncmp(string + i, "and", len_first_word) == 0){
            if (cmd.op == operation::lor)
                return 0;
            cmd.op = operation::land;
        }
        else if (len_first_word == 5 && strncmp(string + i, "order", len_first_word) == 0){
            i = j;
            i += skip_spaces(string + i);
            for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
            int len_second_word = j - i;
            if (len_second_word == 2 && strncmp(string + i, "by", len_second_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                return parse_after_order_by(cmd, string + i);
            }
        }
        else
            return 0;
        i = j;
        i += skip_spaces(string + i);
    }
    return parse_after_where(cmd, string + i); 
}
bool parser::parse_after_order_by(command& cmd, const char* string){
    int i = 0;
    int j = 0;
    for (j = i; string[j] && (string[j] != ',' && string[j] != ';'); j++);
    int len_first_word = j - i;
    //printf("%d\n", len_first_word);
    if (len_first_word == 5){
        if (strncmp(string, "phone", len_first_word) == 0)
            cmd.c_order_end[0] = ordering::phone;
        else if (strncmp(string, "group", len_first_word) == 0)
            cmd.c_order_end[0] = ordering::group;
        else
            return 0;
    }
    else if (len_first_word == 4 && strncmp(string, "name", len_first_word) == 0){
        cmd.c_order_end[0] = ordering::name;
    }
    else
        return 0;
    if (string[j] == ';')
        return 1;
    i = j + 1;
    i += skip_spaces(string + i);
    for (j = i; string[j] && (string[j] != ',' && string[j] != ';'); j++);
    int len_second_word = j - i;
    //printf("%d\n", len_second_word);
    if (len_second_word == 5){
        if (strncmp(string + i, "phone", len_second_word) == 0)
            cmd.c_order_end[1] = ordering::phone;
        else if (strncmp(string + i, "group", len_second_word) == 0){
            cmd.c_order_end[1] = ordering::group;
        }
        else
            return 0;
    }
    else if (len_second_word == 4 && strncmp(string + i, "name", len_second_word) == 0)
        cmd.c_order_end[1] = ordering::name;
    else
        return 0;
    if (string[j] == ';')
        return 1;
    i = j + 1;
    i += skip_spaces(string + i);
    for (j = i; string[j] && string[j] != ';'; j++);
    int len_third_word = j - i;
    if (len_third_word == 5){
        if (strncmp(string + i, "phone", len_third_word) == 0)
            cmd.c_order_end[2] = ordering::phone;
        else if (strncmp(string + i, "group", len_third_word) == 0)
            cmd.c_order_end[2] = ordering::group;
        else
            return 0;
    }
    else if (len_third_word == 4 && strncmp(string + i, "name", len_third_word) == 0)
        cmd.c_order_end[2] = ordering::name;
    else
        return 0;
    if (string[j] == ';')
        return 1;
    return 0;
}

bool parser::parse_condition (command& cmd, const char * string, int* kon){
            int i = 0;
            int j = 0;
            condition dop;
            enum class tgt_field { none, name, phone, group };
            tgt_field tgt = tgt_field::none;
            i += skip_spaces(string);
            const int field_start = i;
            for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
            int len_first_word = j - i;
            i = j;
            i += skip_spaces(string + i);
            for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
            int len_second_word = j - i;
            if (len_second_word == 2){
                if (strncmp(string + i, "<>", len_second_word) == 0){
                    dop = condition::ne;
                }
                else if (strncmp(string + i, "<=", len_second_word) == 0){
                    dop = condition::le;
                }
                else if (strncmp(string + i, ">=", len_second_word) == 0){
                    dop = condition::ge;
                }
                else{
                    return 0;
                }
            }
            else if (len_second_word == 1){
                if (strncmp(string + i, "=", len_second_word) == 0){
                    dop = condition::eq;
                }
                else if (strncmp(string + i, "<", len_second_word) == 0){
                    dop = condition::lt;
                }
                else if (strncmp(string + i, ">", len_second_word) == 0){
                    dop = condition::gt;
                }
                else{
                    return 0;
                }
            }
            else if (len_second_word == 4 && strncmp(string + i, "like", len_second_word) == 0){
                dop = condition::like;
            }
            else if (len_second_word == 3 && strncmp(string + i, "not", len_second_word) == 0){
                i = j;
                i += skip_spaces(string + i);
                for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
                int len_dop_word = j - i;
                if (len_dop_word == 4 && strncmp(string + i, "like", len_dop_word) == 0)
                    dop = condition::nlike;
                else
                    return 0;
            }
            else{
                return 0;
            }
            if (len_first_word == 5){
                if (strncmp(string + field_start, "phone", len_first_word) == 0){
                    cmd.c_phone = dop;
                    tgt = tgt_field::phone;
                }
                else if (strncmp(string + field_start, "group", len_first_word) == 0){
                    cmd.c_group = dop;
                    tgt = tgt_field::group;
                }
                else
                    return 0;
            }
            else if (len_first_word == 4 && strncmp(string + field_start, "name", len_first_word) == 0){
                cmd.c_name = dop;
                tgt = tgt_field::name;
            }
            else
                return 0;
            i = j;
            i += skip_spaces(string + i);
            for (j = i; string[j] && !is_spaces(string[j]) && string[j] != ';'; j++);
            int len_third_word = j - i;
            if (len_third_word >= LEN){
                return 0;
            }
            char str_dop[LEN] = {};
            if (len_third_word > 0){
                memcpy(str_dop, string + i, (size_t)len_third_word);
            }
            str_dop[len_third_word] = '\0';
            if (tgt == tgt_field::name){
                bool res = cmd.set_name(str_dop);
                if (!res)
                    return 0;
            }
            else if (tgt == tgt_field::phone || tgt == tgt_field::group){
                int number = std::atoi(str_dop);
                if (number == 0 && str_dop[0] != '0'){
                    return 0;
                }
                if (tgt == tgt_field::phone)
                    cmd.set_phone(number);
                else
                    cmd.set_group(number);
            }
            else{
                return 0;
            }
            if (string[j] != '\0' && is_spaces(string[j])){
                i = j;
                i += skip_spaces(string + i);
                *kon = i;
            }
            //print();
            return 1;
        }