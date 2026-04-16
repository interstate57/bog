#ifndef KIRPICHEK_H
#define KIRPICHEK_H

#include "hashtable.h"
#include "list2.h"

class kirpichek{
    private:
        int m = 0;
        int k = 0;
        hash_table<const char*> fast_search_name;
        hash_table<int> fast_search_phone;
    public:
        kirpichek() = default;

        kirpichek(int x, int y): m(x), k(y), fast_search_name(m, k), fast_search_phone(m, k){
        }

        ~kirpichek() = default;

        hash_table<const char*>& get_fast_search_name(){ 
            return fast_search_name;
        }

        hash_table<int>& get_fast_search_phone(){ 
            return fast_search_phone;
        }

        void init(int x, int y){
            m = x;
            k = y;
            fast_search_name.init(m, k);
            fast_search_phone.init(m, k);
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
};


#endif