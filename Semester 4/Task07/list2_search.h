#ifndef LIST2_SEARCH_H
#define LIST2_SEARCH_H

#include "list2.h"
#include "vector_m.h"
#include "enum.h"
#include "comparator.h"
#include "list.h"

template<typename T>
class list2_node_search : public vector_m{
    private:
        list2_node_search<T>* next = nullptr;
        list2_node_search<T>* prev = nullptr;
    public:
        list2_node_search() = default;
        ~list2_node_search() = default;
        void set_next(list2_node_search<T>* x){
            next = x;
        }
        void set_prev(list2_node_search<T>* x){
            prev = x;
        }
        list2_node_search<T>* get_next(){
            return next;
        }
        list2_node_search<T>* get_prev(){
            return prev;
        }
};
template<typename T>
class list2_search{
    private:
        list2_node_search<T>* head = nullptr;
        list2_node_search<T>* tail = nullptr;
        int m = 0;
    public:
        list2_search() = default;
        list2_search(int x){
            m = x;
        }
        ~list2_search(){
            list2_node_search<T>* curr = head;
            list2_node_search<T>* next;
            for (;curr;curr = next){
                next = curr->get_next();
                delete curr;
            }
            head = nullptr;
            tail = nullptr;
        }
        list2_node_search<T>* get_head(){
            return head;
        }
        void init(int x){
            m = x;
        }

        void delete_element(list2_node* a){
            list2_node_search* curr = head;
            for (;curr;){
                int len = curr->get_curr_number();
                for (int i = 0; i < len; i++){
                    if (curr->get_data_i(i) == a)
                        curr->move_left(i);
                        return;
                }
            }
        }

        int insert(list2_node* x) {
            list2_node* dop = x;
            list2_node* res;
            if (head == nullptr){
                list2_node_search<T>* new_curr = new list2_node_search();
                if (!new_curr) return -1;
                new_curr->init(m);
                new_curr->insert(x);
                head = new_curr;
                tail = new_curr;
                return 0;
            }

            list2_node_search<T>* curr = head;
            
            while (curr->get_next() && compare_field<T>(get_field<T>(curr->get_next()->get_data_i(0)), get_field<T>(x)) < 0){
                curr = curr->get_next();
            }

            do{
                res = curr-> insert(dop);
                curr = curr->get_next();
                dop = res;            
            } while (res && curr);

            if (res) {
                list2_node_search<T>* new_curr = new list2_node_search(); /// 
                if (!new_curr){
                    return -1;
                }
                new_curr->init(m);
                res = new_curr-> insert(dop);
                if (res != nullptr)
                    return -1;
                tail->set_next(new_curr);
                new_curr->set_prev(tail);
                tail = new_curr;
            }
            return 0;
        }

        void delete_list2_search(command& cmd, list2* a){
            list2_node_search<T>* curr = head;
            list2_node_search<T>* next;
            list2_node* dop;
            int j;
            for (;curr;curr = next){
                int fl = 0;
                int end = curr->get_curr_number();
                for (j = 0; j < end; j++){
                    dop = curr->get_data_i(j);
                    if (cmd.apply(*curr->get_data_i(j))){
                        curr->delete_vector_element(j);
                        end -= 1;
                        j -= 1;
                        if (curr->get_curr_number() == 0){
                            fl = 1;
                            if (curr == head && curr == tail){
                                head = nullptr;
                                next = nullptr;
                                tail = nullptr;
                            }
                            else if (curr == head){
                                curr->get_next()->set_prev(nullptr);
                                head = curr->get_next();
                                next = head;
                            }
                            else if (curr == tail){
                                curr->get_prev()->set_next(nullptr);
                                tail = curr->get_prev();
                                next = nullptr;
                            }
                            else{
                                curr->get_next()->set_prev(curr->get_prev());
                                curr->get_prev()->set_next(curr->get_next());
                                next = curr->get_next();
                            }
                            delete curr;
                            curr = 0;
                        }
                        a->delete_element(dop);
                    }
                }
                if (fl == 0){
                    next = curr->get_next();
                }
            }
        }
        void delete_list2_search(const char* name, int phone, int group, list2* a){
            list2_node_search<T>* curr = head;
            list2_node_search<T>* next = nullptr;
            list2_node* dop;
            int j;
            for (;curr;curr = next){
                int fl = 0;
                int end = curr->get_curr_number();
                for (j = 0; j < end; j++){
                    dop = curr->get_data_i(j);
                    if ((strcmp(name, curr->get_data_i(j)->get_name()) == 0) && (phone == curr->get_data_i(j)->get_phone()) &&
                        (group == curr->get_data_i(j)->get_group())){
                        curr->delete_vector_element(j);
                        end -= 1;
                        j -= 1;
                        if (curr->get_curr_number() == 0){
                            fl = 1;
                            if (curr == head && curr == tail){
                                head = nullptr;
                                next = nullptr;
                                tail = nullptr;
                            }
                            else if (curr == head){
                                curr->get_next()->set_prev(nullptr);
                                head = curr->get_next();
                                next = head;
                            }
                            else if (curr == tail){
                                curr->get_prev()->set_next(nullptr);
                                tail = curr->get_prev();
                                next = nullptr;
                            }
                            else{
                                curr->get_next()->set_prev(curr->get_prev());
                                curr->get_prev()->set_next(curr->get_next());
                                next = curr->get_next();
                            }
                            delete curr;
                            curr = 0;
                        }
                        a->delete_element(dop);
                    }
                }
                if (fl == 0){
                    next = curr->get_next();
                }
            }
        }
        int select_command(list* answer, command& cmd){
            comparator cmp(cmd.get_ordering_end()[0], cmd.get_ordering_end()[1], cmd.get_ordering_end()[2]);
            list2_node_search<T>* curr = head;
            int fl = 0;
            for (;curr;curr = curr->get_next()){
                int j;
                for (j = 0; j < m; j++){
                    list2_node* data_j = curr->get_data_i(j);
                    if (data_j == nullptr){
                        fl = 0;
                        break;
                    }
                    else if (compare_by_field(cmd, condition::eq, *data_j)){
                        if (cmd.apply(*data_j)){
                            if (fl == 0)
                                fl = 1;
                            io_status ret = answer->insert(data_j);
                            if (ret != io_status::success){
                                return 1;
                            }
                        }
                    }
                    else{
                        if (fl == 1){
                            fl = 0;
                            break;
                        }
                    }    
                }
            }
            answer->sort(cmp);
            return 0;
        }
};

template<class T>
bool compare_by_field(command& cmd, condition a, const record& b) {
    throw 5;
}

template<> bool compare_by_field<int>(command& cmd, condition a, const record& b){
    return cmd.compare_phone(a, b);
}

template<> bool compare_by_field<const char*>(command& cmd, condition a, const record& b){
    return cmd.compare_name(a, b);
}


#endif