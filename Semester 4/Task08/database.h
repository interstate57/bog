#ifndef DATABASE_H
#define DATABASE_H

#include "list2.h"
#include "hashtable.h"
#include "list2_search.h"
#include "list.h"
#include "kirpichek.h"

class database{
    private:
        int m = 0;
        int k = 0;
        kirpichek solo;
        kirpichek* mnogo_kirpichekov = new kirpichek[LEN_GROUP]; 
        list2 starting_list;
    public:
        database() = default;

        database(int x, int y): m(x), k(y), solo(m, k){
            for (int i = 0; i < LEN_GROUP; i++){
                mnogo_kirpichekov[i].init(m, k);
            }
        }

        ~database(){
            delete[] mnogo_kirpichekov;
        };

        list2& get_list(){ 
            return starting_list;
        }

        kirpichek& get_solo(){
            return solo;
        }

        kirpichek& get_kirpichek_i(int i){
            return mnogo_kirpichekov[i];
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
                solo.remove_element(curr->get_data());
                mnogo_kirpichekov[curr->get_data()->get_group() - 1].remove_element(curr->get_data());
                starting_list.delete_element(curr->get_data());
                curr->set_data(nullptr);
            }
        }
        
        void insert_command(command& c){
            int res_ = starting_list.insert_command(c);
            if (res_ == 0){
                solo.insert(starting_list.get_head());
                mnogo_kirpichekov[c.get_group() - 1].insert(starting_list.get_head());
            }
        }

        int select_command(command& c, int* res){
            list answer;
            int fl1;
            condition c_group_ = c.get_c_group();
            if (c_group_ == condition::eq){
                fl1 = poisk_name_phone(answer, c, mnogo_kirpichekov[c.get_group() - 1]);
            }
            else{
                fl1 = poisk_name_phone(answer, c, solo);
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
            condition c_group_ = c.get_c_group();
            if (c_group_ == condition::eq){
                fl1 = poisk_name_phone(answer, c, mnogo_kirpichekov[c.get_group() - 1]);
            }
            else{
                fl1 = poisk_name_phone(answer, c, solo);
            }
            if (fl1 == 1){ 
                return 5;
            }
            return 0;
        }

        int poisk_name_phone(list& answer, command& c, kirpichek& x){
            operation op_ = c.get_op();
            condition c_phone_ = c.get_c_phone();
            condition c_name_ = c.get_c_name();
            if (op_ == operation::lor && c.get_c_group() != condition::none){
                return command_select(starting_list.get_head(), &answer, c);
            }
            if (c_name_ != condition::none && c_phone_ != condition::none){
                if (op_ == operation::land){
                    if (c_name_ == condition::eq){
                        return x.get_fast_search_name().select(&answer, c);
                    }
                    else if (c_phone_ == condition::eq){
                        return x.get_fast_search_phone().select(&answer, c);
                    }
                    else{
                        return command_select(starting_list.get_head(), &answer, c);
                    }
                }
                else{
                    int fl1 = 0;
                    if (c_name_ == condition::eq){
                        fl1 = x.get_fast_search_name().select(&answer, c);
                    }
                    else{
                        fl1 = command_select(starting_list.get_head(), &answer, c);
                    }
                    if (fl1 == 1)
                        return 6;
                    if (c_phone_ == condition::eq){
                        return x.get_fast_search_phone().select(&answer, c);
                    }
                    else{
                        return command_select(starting_list.get_head(), &answer, c);
                    }
                }
            }
            else if (c_phone_ != condition::none){
                if (c_phone_ == condition::eq){
                    return x.get_fast_search_phone().select(&answer, c);
                }
                else{
                    return command_select(starting_list.get_head(), &answer, c);
                }
            }
            else{
                if (c_name_ == condition::eq){
                    return x.get_fast_search_name().select(&answer, c);
                }
                else{
                    return command_select(starting_list.get_head(), &answer, c);
                }
            }
        }
        

};



#endif