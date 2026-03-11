#ifndef LIST2_H
#define LIST2_H
#include "enum.h"
#include "command.h"


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
        void delete_list(){
            list2_node *curr, *next;
            for(curr = head; curr; curr = next){
                next = curr->get_next();
                delete curr;
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
};

#endif