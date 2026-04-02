#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list2_search.h"
#include "list2.h"
#include "list.h"
#include "comparator.h"


class hash_table{
    private:
        list2_search* collection_of_data = nullptr;
        int k = 0;
        int m = 0;
    public:
        hash_table() = default;
        hash_table(int x, int y){
            m = x;
            k = y;
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
            collection_of_data = new list2_search[k];
            if (!collection_of_data)
                return -1;
            for (int i = 0; i < k; i++){
                collection_of_data[i].init(m);
            }
            return 0;
        }
        list2_search* get_i(int i){
            return collection_of_data + i;
        }
        int hash_function(const char* name){
            int cnt = 0;
            for (int i = 0; name[i]; i++){
                cnt += name[i];
            }
            return cnt % k;
        }
        int insert(list2_node* curr){
            int index = hash_function(curr->get_name());
            int res = collection_of_data[index].insert(curr);
            if (!res)
                return -1;
            return 0;
        }
        int select(list* answer, command& cmd){
            int index = hash_function(cmd.get_name());
            int res = collection_of_data[index].select_command(answer, cmd);
            if (!res)
                return -1;
            return 0;
        }
};

#endif