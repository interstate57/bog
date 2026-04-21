#ifndef LIST2_SEARCH_H
#define LIST2_SEARCH_H

#include "list2.h"
#include "vector_m.h"
#include "enum.h"
#include "comparator.h"
#include "list.h"

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

template<class T>
T get_field(command&) {
    throw 3;
}

template<> int get_field<int>(command& cmd){
    return cmd.get_phone();
}

template<> const char* get_field<const char*>(command& cmd){
    return cmd.get_name();
}       

template<class T>
T get_field(record&) {
    throw 3;
}

template<> int get_field<int>(record& cmd){
    return cmd.get_phone();
}

template<> const char* get_field<const char*>(record& cmd){
    return cmd.get_name();
}   

template<class T>
int compare_field(T a, T b) {
    throw 3;
}

template<> int compare_field<int>(int a, int b){
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

template<> int compare_field<const char*>(const char* a, const char* b){
    return strcmp(a, b);
}

template<typename T>
class list2_node_search : public vector_m<T>{
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
            list2_node_search<T>* curr = head;
            list2_node_search<T>* next;
            for (;curr;curr = next){
                next = curr->get_next();
                int len = curr->get_curr_number();
                for (int i = 0; i < len; i++){
                    if (*(curr->get_data_i(i)) == *a){
                        curr->move_left(i);
                        if (curr->get_curr_number() == 0){
                            if (curr->get_prev()){
                                curr->get_prev()->set_next(next);
                            }
                            else{
                                head = curr->get_next();
                            }
                            if (next){
                                next->set_prev(curr->get_prev());
                            }
                            else{
                                tail = curr->get_prev();
                            }
                            delete curr;
                            curr = 0;
                            return;
                        }
                        return;
                    }
                }
            }
        }

        int insert(list2_node* x) {
            list2_node* dop = x;
            list2_node* res;
            if (head == nullptr){
                list2_node_search<T>* new_curr = new list2_node_search<T>();
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
                list2_node_search<T>* new_curr = new list2_node_search<T>(); /// 
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
            while(curr && curr->get_next()){
                if (compare_by_field<T>(cmd, condition::lt, *curr->get_data_i(curr->get_curr_number() - 1))){
                    curr = curr->get_next();
                }
                else{
                    break;
                }
            }
            int res = dop_poisk(answer, cmd, curr);
            if (res != 0)
                return -1;
            const ordering* ob = cmd.get_ordering_end();
            bool need_sort = (ob[0] != ordering::none || ob[1] != ordering::none
                || ob[2] != ordering::none);
            if (need_sort)
                answer->sort(cmp);
            return 0;
        }
        int dop_poisk(list* answer, command& cmd, list2_node_search<T>* x){
            int nach = x->bin_find(get_field<T>(cmd));
            if (nach < 0)
                return -1;
            if (cmd.apply(*x->get_data_i(nach)))
                answer->insert(x->get_data_i(nach));
            for (int i = nach - 1; i > -1; i--){
                list2_node* data_j = x->get_data_i(i);
                if (cmd.apply(*data_j)){
                    io_status ret = answer->insert(data_j);
                    if (ret != io_status::success){
                        return -1;
                    }
                }
                else{
                    break;
                }
            }
            list2_node_search<T>* curr = x;
            int fl1 = 0;
            int fl2 = 0;
            for (; curr; curr = curr->get_next()){
                if (fl1 == 1)
                    break;
                int i = (fl2 == 0) ? nach + 1 : 0;
                int len = curr->get_curr_number();
                for (;i < len; i++){
                    list2_node* data_j = curr->get_data_i(i);
                    if (cmd.apply(*data_j)){
                        io_status ret = answer->insert(data_j);
                        if (ret != io_status::success){
                            return -1;
                        }
                    }
                    else{
                        fl1 = 1;
                        break;
                    }
                }
                fl2 = 1;
            }
            return 0;
        }

};





#endif