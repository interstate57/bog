#include "list2_search.h"
#include "list2.h"
#include "list.h"
#include "comparator.h"


class hash_table{
    private:
        list2_search* collection_of_data = nullptr;
        int k = 0;
    public:
        hash_table() = default;
        hash_table(int x){k = x;};
        ~hash_table(){
            delete[] collection_of_data;
            collection_of_data = nullptr;
        }
        int init(){
            collection_of_data = new list2_search[k];
            if (!collection_of_data)
                return -1;
            return 0;
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
            int res = collection_of_data[index].add_record(curr);
            if (!res)
                return -1;
            return 0;
        }

        int select(list2_node* x, list* answer, command& cmd){
            int index = hash_function(x->get_name());
            int res = collection_of_data[index].select_command(x, answer, cmd);
            if (!res)
                return -1;
            return 0;
        }
};