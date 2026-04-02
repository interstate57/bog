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
        hash_table fast_search;
        list2 starting_list;
    public:
        database() = default;

        database(int x, int y): m(x), k(y), fast_search(m, k){
        }

        ~database() = default;

        list2& get_list(){ 
            return starting_list;
        }

        hash_table& get_hash_table(){ 
            return fast_search;
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
            if (res_ == 0)
                fast_search.insert(starting_list.get_head());
        }

        int select_command(command& c, int* res){
            list answer;
            int fl1;
            operation op_ = c.get_op();
            if (op_ == operation::lor){
                fl1 = command_select(starting_list.get_head(), &answer, c);
            }
            else{
                if (c.get_c_name() == condition::eq){
                    fl1 = fast_search.select(&answer, c);
                }
                else{
                    fl1 = command_select(starting_list.get_head(), &answer, c);
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