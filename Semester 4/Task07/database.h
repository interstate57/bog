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
        hash_table<name_key_traits> fast_search_name;
        hash_table<phone_key_traits> fast_search_phone;
        list2 starting_list;

        void rebuild_indexes(){
            fast_search_name.reinit(m, k);
            fast_search_phone.reinit(m, k);
            for (list2_node* curr = starting_list.get_head(); curr; curr = curr->get_next()){
                fast_search_name.insert(curr);
                fast_search_phone.insert(curr);
            }
        }
    public:
        database() = default;
        database(int x, int y)
            : m(x)
            , k(y)
            , fast_search_name(m, k)
            , fast_search_phone(m, k)
        {
            fast_search_name.init();
            fast_search_phone.init();
        }
        ~database() = default;
        list2& get_list(){ return starting_list; }
        const list2& get_list() const { return starting_list; }
        hash_table<name_key_traits>& get_hash_table_name(){ return fast_search_name; }
        const hash_table<name_key_traits>& get_hash_table_name() const { return fast_search_name; }
        hash_table<phone_key_traits>& get_hash_table_phone(){ return fast_search_phone; }
        const hash_table<phone_key_traits>& get_hash_table_phone() const { return fast_search_phone; }

        void delete_command(command& c){
            const bool can_use_index = (c.get_operation() != operation::lor);

            if (can_use_index && c.get_c_name() == condition::eq){
                fast_search_name.get_i(fast_search_name.hash_command(c))->delete_list2_search(c, &starting_list);
                rebuild_indexes();
                return;
            }
            if (can_use_index && c.get_c_phone() == condition::eq){
                fast_search_phone.get_i(fast_search_phone.hash_command(c))->delete_list2_search(c, &starting_list);
                rebuild_indexes();
                return;
            }
            else{
                starting_list.delete_command(c);
                rebuild_indexes();
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
            const bool can_use_index = (c.get_operation() != operation::lor);

            if (can_use_index && c.get_c_name() == condition::eq){
                fl1 = fast_search_name.select(&answer, c);
            }
            else if (can_use_index && c.get_c_phone() == condition::eq){
                fl1 = fast_search_phone.select(&answer, c);
            }
            else{
                fl1 = command_select(starting_list.get_head(), &answer, c);
            }
            if (fl1 == 1){ 
                return 5;
            }
            if (res) *res += static_cast<int>(answer.get_length());
            answer.print(c);
            answer.delete_list();
            return 0;
        }

};

#endif