#include "parser.h"
#include "enum.h"

io_status parser::read(command& cmd){
    int i = 0;
    int fl = 0;
    char s = fgetc(stdin);
    if (!s){
        return io_status::success;
    }
    while (s != ';'){
        if (s == '\t' || s == '\n'){
            buf[i] = ' ';
        }
        buf[i] = s;
        s = fgetc(stdin);
        if (!s){
            fl = 1;
            break;
        }
        i += 1;
    }
    if (fl){
        return io_status::eof;
    }
    buf[i] = '\0';
    return parse(cmd, buf + skip_spaces(buf));
}
bool parser::is_spaces(const char s){
    return s == ' ' && s == '\t' && s == '\n';
}
int parser::skip_spaces(const char* str){
    int i;
    for (i = 0; str[i]; i++){
        if (str[i] != ' ')
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
    if (len_first_word == 6){
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
    if (string[0] == ';')
        return io_status::quit;
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
    int i = 0;
    int j = 0;
    if (string[i] != ';'){
        i += skip_spaces(string + i);
        for (j = i; string[j] && !is_spaces(string[j]); j++);
        int len = j - i;
        if (strncmp(string + i, "where", len) == 0){
            i = j;
            i += skip_spaces(string + i);
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
    int i = 0;
    int j = 0;
    i += skip_spaces(string);
    if (string[i] == '*'){
        cmd.c_order[0] = ordering::name;
        cmd.c_order[1] = ordering::phone;
        cmd.c_order[2] = ordering::group;
        i += 1;
        i += skip_spaces(string + i);
        for (j = i; string[j] && string[j] != ' '; j++);
        int len = j - i;
        if (strncmp(string + i, "where", len) == 0){
            i = j;
            i += skip_spaces(string + i);
            bool second_res = parse_after_where(cmd, string + i);
            if (!second_res)
                return 0;
        }
        else{
            return 0;
        }
    }
    else{
        for (j = i; string[j] && (string[j] != ',' && string[j] != ' '); j++);
        int len_first_word = j - i;
        //printf("%d\n", len_first_word);
        if (len_first_word == 5){
            if (strncmp(string, "phone", len_first_word) == 0)
                cmd.c_order[0] = ordering::phone;
            else if (strncmp(string, "group", len_first_word) == 0)
                cmd.c_order[0] = ordering::group;
            else
                return 0;
        }
        else if (len_first_word == 4 && strncmp(string, "name", len_first_word) == 0){
            cmd.c_order[0] = ordering::name;
        }
        else
            return 0;
        
        i = j + 1;
        i += skip_spaces(string + i);
        for (j = i; string[j] && (string[j] != ',' && string[j] != ' '); j++);
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
            else
                return 0;
        }
        else if (len_second_word == 4 && strncmp(string + i, "name", len_second_word) == 0)
            cmd.c_order[1] = ordering::name;
        else
            return 0;
        i = j + 1;
        i += skip_spaces(string + i);
        for (j = i; string[j] && string[j] != ' '; j++);
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
            else
                return 0;
        }
        else if (len_third_word == 4 && strncmp(string + i, "name", len_third_word) == 0)
            cmd.c_order[2] = ordering::name;
        else
            return 0;
        i = j;
        i += skip_spaces(string + i);
        for (j = i; string[j] && string[j] != ' '; j++);
        int len_forth_word = j - i;
        if (strncmp(string + i, "where", len_forth_word) == 0){
            i = j;
            i += skip_spaces(string + i);
            bool second_res = parse_after_where(cmd, string + i);
            if (!second_res)
                return 0;
            return 1;
        }
        else
            return 0;
    }
    return 1;
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
        for (j = i; string[j] && string[j] != ' '; j++);
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
            for (j = i; string[j] && string[j] != ' '; j++);
            int len_second_word = j - i;
            if (strncmp(string + i, "by", len_second_word) == 0){
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
    i += skip_spaces(string);
    for (j = i; string[j] && string[j] != ' '; j++);
    int len_first_word = j - i;
    i = j;
    i += skip_spaces(string + i);
    for (j = i; string[j] && string[j] != ' '; j++);
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
        for (j = i; string[j] && string[j] != ' ' && string[j] != '\n'; j++);
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
        if (strncmp(string, "phone", len_first_word) == 0){
            cmd.c_phone = dop;
        }
        else if (strncmp(string, "group", len_first_word) == 0)
            cmd.c_group = dop;
        else
            return 0;
    }
    else if (len_first_word == 4 && strncmp(string, "name", len_first_word) == 0)
        cmd.c_name = dop;
    else
        return 0;
    i = j;
    i += skip_spaces(string + i);
    for (j = i; string[j] && string[j] != ' ' && string[j] != '\n'; j++);
    int len_third_word = j - i;
    char str_dop[LEN] = {};
    strncpy(str_dop, string + i, len_third_word);
    if (cmd.c_name != condition::none && dop == cmd.c_name){
        bool res = cmd.set_name(str_dop);
        if (!res)
            return 0;
        
    }
    else if ((cmd.c_phone != condition::none && dop == cmd.c_phone) || (cmd.c_group != condition::none && dop == cmd.c_group)){
        //std::cout << "number: " << "\"" << str_dop << "\"" << std::endl;
        int number = std::atoi(str_dop);
        //std::cout << "After atoi: " << str_dop << "->" << number << std::endl;
        if (number == 0 && str_dop[0] != '0'){
            return 0;
        }
        if (cmd.c_phone != condition::none && dop == cmd.c_phone){
            cmd.set_phone(number);
        }
        else{
            cmd.set_group(number);
        }
    }
    else{
        return 0;
    }
    if (string[j] == ' '){
        i = j;
        i += skip_spaces(string + i);
        *kon = i;
    }
    //print();
    return 1;
}