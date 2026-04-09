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
        hash_table<std::unique_ptr<char []>> fast_search_name;
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

        hash_table<std::unique_ptr<char []>>& get_hash_table_name(){ 
            return fast_search_name;
        }

        hash_table<int>& get_hash_table_phone(){ 
            return fast_search_phone;
        }

        void delete_command(command& c){
            operation op_ = c.get_op();
            list2_node* next;
            if (op_ == operation::lor){
                list2_node* curr = starting_list.get_head();
                for (;curr;){
                    next = curr->get_next();
                    if (c.apply(*curr)){
                        fast_search.get_i(fast_search.hash_function(curr->get_name()))->delete_list2_search(curr->get_name(), \
                        curr->get_phone(), curr->get_group(), &starting_list);
                    }
                    curr = next;
                }
            }
            else{
                if (c.get_c_name() == condition::eq){
                    fast_search.get_i(fast_search.hash_function(c.get_name()))->delete_list2_search(c, &starting_list);
                }
                else{
                    list2_node* curr = starting_list.get_head();
                    for (;curr;){
                        next = curr->get_next();
                        if (c.apply(*curr)){
                            fast_search.get_i(fast_search.hash_function(curr->get_name()))->delete_list2_search(curr->get_name(), \
                            curr->get_phone(), curr->get_group(), &starting_list);
                        }
                        curr = next;
                    }
                }
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
                        list answer_;
                        command c_(c.get_c_name(), c.get_c_phone(), c.get_c_group(), operation::land);
                        c_.set_name(c.get_name());
                        c_.set_phone(c.get_phone());
                        c_.set_group(c.get_group());
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
                        list_node* curr = answer_.get_head();
                        for (;curr;){
                            if (!c_.apply(*curr->get_data())){
                                answer.insert(curr->get_data());
                            }
                        }
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

        

};

#endif