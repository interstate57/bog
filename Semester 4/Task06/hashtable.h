#include "list2_search.h"
#include "list2.h"


class hash_table{
    private:
        list2_search* collection_of_data = nullptr;
        int k = 0;
    public:
        hash_table() = default;
        hash_table(int x){k = x;};
        ~hash_table(){
            //////
        }
        int hash_function(list2_node* curr){
            int cnt = 0;
            const char* name = curr->get_name();
            for (int i = 0; name[i]; i++){
                cnt += name[i];
            }
            return cnt % k;
        }
        
};