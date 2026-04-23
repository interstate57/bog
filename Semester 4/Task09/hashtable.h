#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list2_search.h"
#include "list2.h"
#include "list.h"
#include "comparator.h"


template<typename T>
class hash_table{
    private:
        list2_search<T>* collection_of_data = nullptr;
        int k = 0;
        int m = 0;
    public:
        hash_table() = default;
        hash_table(int x, int y){
            k = x;
            m = y;
            init();
        }
        ~hash_table(){
            delete[] collection_of_data;
            collection_of_data = nullptr;
        }
        void set_k(int x){
            k = x;
        }
        int init(){
            collection_of_data = new list2_search<T>[k];
            if (!collection_of_data)
                return -1;
            for (int i = 0; i < k; i++){
                collection_of_data[i].init(m);
            }
            return 0;
        }
        int init(int a, int b){
            k = a;
            m = b;
            collection_of_data = new list2_search<T>[k];
            if (!collection_of_data)
                return -1;
            for (int i = 0; i < k; i++){
                collection_of_data[i].init(m);
            }
            return 0;
        }
        list2_search<T>* get_i(int i){
            return collection_of_data + i;
        }
        int insert(list2_node* curr){
            int index = hash_function(get_field<T>(curr));
            int res = collection_of_data[index].insert(curr);
            if (res != 0)
                return -1;
            return 0;
        }
        int select(list* answer, command& cmd){
            int index = hash_function(get_field<T>(cmd));
            int res = collection_of_data[index].select_command(answer, cmd);
            if (res != 0)
                return -1;
            return 0;
        }
        void remove_element(list2_node* curr) {
            int index = hash_function(get_field<T>(curr));
            collection_of_data[index].delete_element(curr);
        }

        void go_through_hashtable(list* answer, command& cmd){
            int i = 0;
            for (; i < k; i++){
                list2_node_search<T>* curr = collection_of_data[i].get_head();
                for (;curr; curr = curr->get_next()){
                    for (int j = 0; j < curr->get_curr_number(); j++){
                        if (cmd.apply(*curr->get_data_i(j)))
                            answer->insert(curr->get_data_i(j));
                    }
                }
            }
        }
        int hash_function(T x){
            throw 2;
        }
};

template<> int hash_table<int>::hash_function(int x){
    int dop = x;
    int cnt = 0;
    while (dop != 0){
        cnt += dop % 10;
        dop = dop / 10;
    }
    return cnt % k;
}
template<> int hash_table<const char*>::hash_function(const char* x){
    int cnt = 0;
    for (int i = 0; x[i]; i++){
        cnt += x[i];
    }
    return cnt % k;
}

#endif