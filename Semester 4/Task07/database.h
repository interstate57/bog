#ifndef DATABASE_H
#define DATABASE_H

#include "list2.h"
#include "hashtable.h"
#include "list2_search.h"
#include "list.h"

class database{
    private:
        int m = 0;
        int k = 0;
        hash_table<const char*> fast_search_name;
        hash_table<int> fast_search_phone;
        list2 starting_list;
    public:
        database() = default;

        database(int x, int y): m(x), k(y), fast_search_name(m, k), fast_search_phone(m, k){
        }

        ~database() = default;

        list2& get_list(){ 
            return starting_list;
        }

        hash_table<const char*>& get_hash_table_name(){ 
            return fast_search_name;
        }

        hash_table<int>& get_hash_table_phone(){ 
            return fast_search_phone;
        }


        void delete_command(command& c){
            list answer;
            int res = select_command(c, answer);
            if (res != 0)
                return;
            list_node* curr = answer.get_head();
            list_node* next;
            for (;curr; curr = next){
                next = curr->get_next();
                fast_search_name.remove_element(curr->get_data());
                fast_search_phone.remove_element(curr->get_data());
                starting_list.delete_element(curr->get_data());
                curr->set_data(nullptr);
            }
        }
        
        void insert_command(command& c){
            int res_ = starting_list.insert_command(c);
            if (res_ == 0){
                fast_search_name.insert(starting_list.get_head());
                fast_search_phone.insert(starting_list.get_head());
            }
        }

        int select_command(command& c, int* res){
            list answer;
            int fl1;
            int fl2;
            operation op_ = c.get_op();
            condition c_phone_ = c.get_c_phone();
            condition c_name_ = c.get_c_name();
            if (op_ == operation::lor && c.get_c_group() != condition::none){
                fl1 = command_select(starting_list.get_head(), &answer, c);
            }
            else{
                if (c_name_ != condition::none && c_phone_ != condition::none){
                    if (op_ == operation::land){
                        if (c_name_ == condition::eq){
                            fl1 = fast_search_name.select(&answer, c);
                        }
                        else if (c_phone_ == condition::eq){
                            fl1 = fast_search_phone.select(&answer, c);
                        }
                        else{
                            fl1 = command_select(starting_list.get_head(), &answer, c);
                        }
                    }
                    else{
                        if (c_name_ == condition::eq){
                            fl1 = fast_search_name.select(&answer, c);
                        }
                        else{
                            fl1 = command_select(starting_list.get_head(), &answer, c);
                        }
                        if (fl1 == 1)
                            return 6;
                        if (c_phone_ == condition::eq){
                            fl2 = fast_search_phone.select(&answer, c);
                        }
                        else{
                            fl2 = command_select(starting_list.get_head(), &answer, c);
                        }
                        if (fl2 == 1)
                            return 6;
                    }
                }
                else if (c_phone_ != condition::none){
                    if (c_phone_ == condition::eq){
                        fl1 = fast_search_phone.select(&answer, c);
                    }
                    else{
                        fl1 = command_select(starting_list.get_head(), &answer, c);
                    }
                }
                else{
                    if (c_name_ == condition::eq){
                        fl1 = fast_search_name.select(&answer, c);
                    }
                    else{
                        fl1 = command_select(starting_list.get_head(), &answer, c);
                    }
                }
            }
            if (fl1 == 1){ 
                return 5;
            }
            if (res) 
                *res += answer.get_length();
            answer.print(c);
            answer.delete_list();
            return 0;
        }

        int select_command(command& c, list& answer){
            int fl1;
            int fl2;
            operation op_ = c.get_op();
            condition c_phone_ = c.get_c_phone();
            condition c_name_ = c.get_c_name();
            if (op_ == operation::lor && c.get_c_group() != condition::none){
                fl1 = command_select(starting_list.get_head(), &answer, c);
            }
            else{
                if (c_name_ != condition::none && c_phone_ != condition::none){
                    if (op_ == operation::land){
                        if (c_name_ == condition::eq){
                            fl1 = fast_search_name.select(&answer, c);
                        }
                        else if (c_phone_ == condition::eq){
                            fl1 = fast_search_phone.select(&answer, c);
                        }
                        else{
                            fl1 = command_select(starting_list.get_head(), &answer, c);
                        }
                    }
                    else{
                        if (c_name_ == condition::eq){
                            fl1 = fast_search_name.select(&answer, c);
                        }
                        else{
                            fl1 = command_select(starting_list.get_head(), &answer, c);
                        }
                        if (fl1 == 1)
                            return 6;
                        if (c_phone_ == condition::eq){
                            fl2 = fast_search_phone.select(&answer, c);
                        }
                        else{
                            fl2 = command_select(starting_list.get_head(), &answer, c);
                        }
                        if (fl2 == 1)
                            return 6;
                    }
                }
                else if (c_phone_ != condition::none){
                    if (c_phone_ == condition::eq){
                        fl1 = fast_search_phone.select(&answer, c);
                    }
                    else{
                        fl1 = command_select(starting_list.get_head(), &answer, c);
                    }
                }
                else{
                    if (c_name_ == condition::eq){
                        fl1 = fast_search_name.select(&answer, c);
                    }
                    else{
                        fl1 = command_select(starting_list.get_head(), &answer, c);
                    }
                }
            }
            if (fl1 == 1){ 
                return 5;
            }
            return 0;
        }
        

};

#endif