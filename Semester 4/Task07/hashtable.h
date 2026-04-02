#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list2_search.h"
#include "list2.h"
#include "list.h"
#include "comparator.h"
#include "key_traits.h"

template <class Traits>
class hash_table{
    private:
        list2_search<Traits>* collection_of_data = nullptr;
        int k = 0;
        int m = 0;
    public:
        hash_table() = default;
        hash_table(int x, int y){
            m = x;
            k = y;
        }
        hash_table(const hash_table&) = delete;
        hash_table& operator=(const hash_table&) = delete;
        hash_table(hash_table&& other) noexcept {
            collection_of_data = other.collection_of_data;
            other.collection_of_data = nullptr;
            k = other.k; other.k = 0;
            m = other.m; other.m = 0;
        }
        hash_table& operator=(hash_table&& other) noexcept {
            if (this == &other) return *this;
            delete[] collection_of_data;
            collection_of_data = other.collection_of_data;
            other.collection_of_data = nullptr;
            k = other.k; other.k = 0;
            m = other.m; other.m = 0;
            return *this;
        }
        ~hash_table(){
            delete[] collection_of_data;
            collection_of_data = nullptr;
        }
        void set_k(int x){
            k = x;
        }
        int init(){
            delete[] collection_of_data;
            collection_of_data = new list2_search<Traits>[k];
            if (!collection_of_data)
                return -1;
            for (int i = 0; i < k; i++){
                collection_of_data[i].init(m);
            }
            return 0;
        }
        int reinit(int new_m, int new_k){
            m = new_m;
            k = new_k;
            return init();
        }
        list2_search<Traits>* get_i(int i){
            return collection_of_data + i;
        }
        int hash_node(const list2_node* n) const { return Traits::hash_key(Traits::get_key(n), k); }
        int hash_command(const command& c) const { return Traits::hash_key(Traits::get_cmd_key(c), k); }

        int insert(list2_node* curr){
            int index = hash_node(curr);
            int res = collection_of_data[index].insert(curr);
            return (res == 0) ? 0 : -1;
        }
        int select(list* answer, command& cmd){
            int index = hash_command(cmd);
            int res = collection_of_data[index].select_command(answer, cmd);
            return (res == 0) ? 0 : -1;
        }
};

#endif