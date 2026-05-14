#ifndef KIRPICHEK_H
#define KIRPICHEK_H

#include "hashtable.h"
#include "list2.h"

class kirpichek{
    private:
        int k1 = 0;
        int m1 = 0;
        int k2 = 0;
        int m2 = 0;
        hash_table<const char*> fast_search_name;
        hash_table<int> fast_search_phone;
    public:
        kirpichek() = default;

        kirpichek(int x, int y, int a, int b): k1(x), m1(y), k2(a), m2(b), 
        fast_search_name(k1, m1), fast_search_phone(k2, m2){
        }

        ~kirpichek() = default;

        hash_table<const char*>& get_fast_search_name(){ 
            return fast_search_name;
        }

        hash_table<int>& get_fast_search_phone(){ 
            return fast_search_phone;
        }

        void init(int x, int y, int a, int b){
            k1 = x;
            m1 = y;
            k2 = a;
            m2 = b;
            fast_search_name.init(k1, m1);
            fast_search_phone.init(k2, m2);
        }

        int insert(list2_node* curr){
            int res_ = get_fast_search_name().insert(curr);
            if (res_ == -1){
                return -1;
            }
            res_ = get_fast_search_phone().insert(curr);
            if (res_ == -1){
                return -1;
            }
            return 0;
        }

        void remove_element(list2_node* curr){
            fast_search_name.remove_element(curr);
            fast_search_phone.remove_element(curr);
        }

        void go_through_kirpichek(list* answer, command& cmd){
            fast_search_name.go_through_hashtable(answer, cmd);
        }
};


#endif