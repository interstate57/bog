#ifndef LIST_H
#define LIST_H
#include "enum.h"
#include "list2.h"
#include "comparator.h"
#include "command.h"

class list2_node;

class list_node
{
    private:
        list_node* next = nullptr;
        list2_node* data = nullptr;
    public:
        list_node() = default;
        list_node(const list_node&) = delete;
        list_node(list_node&& r){
            next = r.next; r.next = nullptr;
            data = r.data; r.data = nullptr;
        }
        ~list_node(){
            next = nullptr;
            data = nullptr;
        }
        list_node& operator= (const list_node&) = delete;
        list_node& operator=(list_node&& r){
            next = r.next; r.next = nullptr;
            data = r.data; r.data = nullptr;
            return *this;
        }
        list_node* get_next() const{
            return next;
        }
        list2_node* get_data() const{
            return data;
        }
        void set_next(list_node* r){
            next = r;
        }
        void set_data(list2_node* r){
            data = r;
        }
        int len(){
            return (next != nullptr) ? (1 + next->len()) : 1;
        }
        friend class list;
};

class list
{
    private:
        list_node * head = nullptr;
    public:
        list() = default;
        ~list(){
            delete_list();
        }
        void delete_list(){
            list_node *curr, *next;
            for(curr = head; curr; curr = next){
                next = curr->get_next();
                delete curr;
            }
            head = 0;
        }
        list_node* get_head(){
            return head;
        }
        void print (command& cmd, FILE *fp = stdout) const{
            list_node* curr;
            unsigned int cnt = 0;
            for(curr = head; curr != nullptr; curr = curr->get_next()){
                curr->data->print(cmd.get_ordering(), fp);
                cnt++;
            }
        }
       io_status insert(list2_node* dop){
            list_node* new_head = new list_node;
            if (!new_head)
                return io_status::memory;
            list_node* old_head = head;
            new_head->set_data(dop);
            head = new_head;
            new_head->set_next(old_head);
            return io_status::success;

        }
       int length_(list_node* head){
            int cnt = 0;
            list_node* curr;
            for (curr = head; curr; curr = curr->get_next()){
                cnt += 1;
            }
            return cnt;
        }

        int get_length(){
            return length_(head);
        }
       list_node* merge(list_node* a, list_node* b, list_node** res_tail, comparator cmp){
            list_node* new_head = nullptr;
            list_node* new_tail = nullptr;
            list_node* curra = a;
            list_node* currb = b;
            while (curra && currb){
                if (cmp(curra->data->get_name(), currb->data->get_name(), curra->data->get_phone(), currb->data->get_phone(),
                curra->data->get_group(), currb->data->get_group())){
                    if (new_head == nullptr){
                        new_head = curra;
                    }
                    else{
                        new_tail->set_next(curra);
                    }
                    new_tail = curra;
                    curra = curra->get_next();
                }
                else{
                    if (new_head == nullptr){
                        new_head = currb;
                    }
                    else{
                        new_tail->set_next(currb);
                    }
                    new_tail = currb;
                    currb = currb->get_next();
                }
            }
            if (curra == nullptr){
                while (currb){
                    if (new_head == nullptr){
                        new_head = currb;
                    }
                    else{
                        new_tail->set_next(currb);
                    }
                    new_tail = currb;
                    currb = currb->get_next();
                }
            }
            else{
                while (curra){
                    if (new_head == nullptr){
                        new_head = curra;
                    }
                    else{
                        new_tail->set_next(curra);
                    }
                    new_tail = curra;
                    curra = curra->get_next();
                }
            }
            *res_tail = new_tail;
            return new_head;
        }

        list_node* circumcise(list_node** current_head, int len){
            list_node* head = *current_head;
            list_node* tmp = head;
            list_node* tail = nullptr;
            for (int k = 0; k < len; ++k) {
                if (k + 1 == len) {
                    tail = tmp;
                }
                tmp = tmp->get_next();
            }
            tail->set_next(nullptr);
            *current_head = tmp;
            return head;
        }

        void sort(comparator cmp){
            int n = get_length();
            int j = 1;
            while (j < n) {
                list_node* tail = nullptr;
                list_node* curr = head;
                for (int i = 0; i < n; i += 2 * j) {
                    list_node* first = nullptr;
                    list_node* second = nullptr;
                    list_node* res = nullptr;
                    list_node *res_tail = nullptr;
                    if (i + 2*j >= n) { 
                        if (i+j >= n) { 
                            first = circumcise(&curr, n-i);
                            res = merge(first, second, &res_tail, cmp);
                        }
                        else{ 
                            first = circumcise(&curr, j);
                            second = circumcise(&curr, n-i-j);
                            res = merge(first, second, &res_tail, cmp);
                        }
                    }
                    else {
                        first = circumcise(&curr, j);
                        second = circumcise(&curr, j);
                        res = merge(first, second, &res_tail, cmp);
                    }
                    if (tail) {
                        tail->set_next(res);
                    }
                    else {
                        head = res;
                    }
                    tail = res_tail;    
                }
                j *= 2;
            }
        }
};

int select_command(list2_node* head_2, list* answer, command& cmd){
    comparator cmp(cmd.get_ordering_end()[0], cmd.get_ordering_end()[1], cmd.get_ordering_end()[2]);
    list2_node* curr = head_2;
    for (;curr;curr = curr->get_next()){
        if (cmd.apply(*curr)){
            io_status ret = answer->insert(curr);
            if (ret != io_status::success){
                return 1;
            }
        }
    }
    const ordering* ob = cmd.get_ordering_end();
    bool need_sort = (ob[0] != ordering::none || ob[1] != ordering::none
        || ob[2] != ordering::none);
    if (need_sort)
        answer->sort(cmp);
    return 0;
}

#endif 