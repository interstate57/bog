#ifndef LIST2_H
#define LIST2_H
#include "enum.h"
//#include "list.h"
#include "command.h"
#include <memory>

//class list_node;

class list2_node : public record
{
    private:
        list2_node* next = nullptr;
        list2_node* prev = nullptr;
    public:
        list2_node() = default;
        list2_node(const list2_node&) = delete;
        list2_node(list2_node&& r) : record((record&&)r){
            next = r.next; r.next = nullptr;
            prev = r.prev; r.prev = nullptr;
        }
        ~list2_node(){
            next = nullptr;
            prev = nullptr;
        }
        list2_node& operator= (const list2_node&) = delete;
        list2_node& operator=(list2_node&& r){
            *(record*)(this) = (record&&)r;
            next = r.next; r.next = nullptr;
            prev = r.prev; r.prev = nullptr;
            return *this;
        }
        list2_node* get_next() const{
            return next;
        }
        void set_next(list2_node* r){
            next = r;
        }
        list2_node* get_prev() const{
            return prev;
        }
        void set_prev(list2_node* r){
            prev = r;
        }
        friend class list2;
};

class list2
{
    private:
        list2_node * head = nullptr;
    public:
        ~list2(){
            delete_list();
        }
        io_status read (FILE *fp = stdin, unsigned int max_read = -1){
            list2_node buf;
            io_status ret;
            list2_node *curr, *tail;
            unsigned int cnt = 1;
            if ((ret = buf.read(fp)) != io_status::success) return ret;
            head = new list2_node;
            if (head == nullptr) return io_status::memory;
            *head = (list2_node&&)buf;
            curr = head;
            while(buf.read(fp) == io_status::success){
                if (cnt == max_read) break;
                tail = new list2_node;
                if (tail == nullptr){
                    delete_list();
                    return io_status::memory;
                }
                *tail = (list2_node&&) buf;
                curr->set_next(tail);
                tail->set_prev(curr);
                curr = tail;
            }
            if (!feof(fp)){
                delete_list();
                return io_status::format;
            }
            return io_status::success;
        }
        io_status insert(const char* name, int phone, int group){
            list2_node* new_head = new list2_node;
            if (!new_head)
                return io_status::memory;
            list2_node* old_head = head;
            int res = new_head->init(name, phone, group);
            if (res != 0)
                return io_status::memory;
            head = new_head;
            new_head->set_next(old_head);
            new_head->set_prev(nullptr);
            old_head->set_prev(new_head);
            return io_status::success;

        }
        void delete_list(){
            list2_node *curr, *next;
            for(curr = head; curr; curr = next){
                next = curr->get_next();
                delete curr;
            }
            head = 0;
        }

        void print(command& cmd){
            list2_node *curr;
            for(curr = head; curr; curr = curr->get_next()){
                curr->print(cmd.get_ordering(), stdout);
            }
        }

        void delete_element(list2_node* x){
            list2_node* dop;
            if (x == head){
                dop = head->get_next();
                if (dop)
                    dop->set_prev(nullptr);
                head->set_next(nullptr);
                delete head;
                head = dop;
            }
            else{
                if (x->get_next())
                    x->get_next()->set_prev(x->get_prev());
                x->get_prev()->set_next(x->get_next());
                delete x;
                x = 0;
            }
        }

        unsigned int get_length () const{
            list2_node* curr;
            unsigned int cnt = 0;
            for(curr = head; curr != nullptr; curr = curr->get_next()){
                cnt++;
            }
            return cnt;
        }
        list2_node* get_head(){
            return head;
        }
        void delete_command(command& cmd){
            
            list2_node* curr = head;
            for (;curr;){
                if (cmd.apply(*curr)){
                    if (curr == head){

                        curr = head->get_next();
                        if (curr)
                            curr->set_prev(nullptr);
                        delete head;
                        head = curr;
                    }
                    else{
                        list2_node* next = curr->get_next();
                        curr->get_prev()->set_next(next);
                        if (next)
                            next->set_prev(curr->get_prev());
                        delete curr;
                        curr = next;
                    }
                } else {
                    curr = curr->get_next();
                }
            }
        }

        int insert_command(command& cmd){ // может быть надо поправить на io_status
            list2_node* curr = head;
            for (;curr;curr = curr->get_next()){
                if (cmd.compare_name(condition::eq, *curr) && cmd.compare_phone(condition::eq, *curr) &&\
                cmd.compare_group(condition::eq, *curr))
                    return 1;
            }
            insert(cmd.get_name(), cmd.get_phone(), cmd.get_group());
            return 0;
        }


};


#endif