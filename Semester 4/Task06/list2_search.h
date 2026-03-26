#include "list2.h"
#include "vector_m.h"
#include "enum.h"
#include "comparator.h"
#include "list.h"

class list2_node_search : public vector_m{
    private:
        list2_node_search* next = nullptr;
        list2_node_search* prev = nullptr;
    public:
        list2_node_search() = default;
        ~list2_node_search() = default;
        void set_next(list2_node_search* x){
            next = x;
        }
        void set_prev(list2_node_search* x){
            prev = x;
        }
        list2_node_search* get_next(){
            return next;
        }
        list2_node_search* get_prev(){
            return prev;
        }
};

class list2_search{
    private:
        list2_node_search* head = nullptr;
        list2_node_search* tail = nullptr;
        int m = 0;
    public:
        list2_search() = default;
        list2_search(int x){
            m = x;
        }
        ~list2_search(){
            list2_node_search* curr = head;
            list2_node_search* next;
            for (;curr;curr = next){
                next = curr->get_next();
                delete curr;
            }
            head = nullptr;
            tail = nullptr;
        }
        list2_node_search* get_head(){
            return head;
        }
        int add_record(list2_node* x){
            list2_node_search* curr = head;
            list2_node_search* new_node;
            if (curr == nullptr){
                new_node = new list2_node_search(); /// 
                if (!new_node){
                    return -1;
                }
                new_node->init(m);
                head = new_node;
                curr = head;
            }
            int fl = 2;
            while (fl < 2){
                list2_node* res = curr-> insert(x); ///
                if (res == nullptr){
                    return 0;
                }
                else{
                    curr = curr->get_next();
                    if (curr == nullptr){
                        new_node = new list2_node_search(); /// 
                        if (!new_node){
                            return -1;
                        }
                        new_node->init(m);
                        tail->set_next(new_node);
                        new_node->set_prev(tail);
                        tail = new_node;
                        curr = new_node;
                    }
                    fl += 1;
                }
            }
            return -2;
        }

        int select_command(list* answer, command& cmd){
            comparator cmp(cmd.get_ordering_end()[0], cmd.get_ordering_end()[1], cmd.get_ordering_end()[2]);
            list2_node_search* curr = head;
            for (;curr;curr = curr->get_next()){
                if (cmd.apply(*curr)){
                    io_status ret = answer->insert(curr);
                    if (ret != io_status::success){
                        return 1;
                    }
                }
            }
            answer->sort(cmp);
            return 0;
        }
};