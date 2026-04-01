#include "list2.h"
#include "hashtable.h"

class database{
    private:
        list2 starting_list;
        hash_table fast_search;
        int m = 0;
        int k = 0;
    public:
        database() = default;
        database(int x, int y){
            m = x;
            k = y;
            hash_table fast_search = new hash_table(m ,k);
        }
    
};