#ifndef student_H
#define student_H
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
enum class io_status
{
    success,
    eof,
    format,
    memory,
    wrong_file
};
class student
{
    private:
        char * name = nullptr;
        int value = 0;
    public:
        student () = default;
        student (const student& x) = delete;
        student (student&& x){
            name = x.name; x.name = nullptr;
            value = x.value; x.value = 0;
        }
        student (char* name, int value){
            init (name, value);
        }
        ~student (){
            erase ();
        }
        student& operator= (const student& x) = delete;
        student& operator= (student&& x){
            if (this == &x)
                return *this;
            erase ();
            name = x.name; x.name = nullptr;
            value = x.value; x.value = 0;
            return *this;
        }
        void print (FILE* fp = stdout) const{
            fprintf(fp, "%s %d\n", name, value);
        }
        io_status read (FILE * fp){
            const int LEN = 1234;
            char n[LEN];
            int v;
            if (fscanf (fp, "%s%d", n, &v) != 2){
                if (! feof (fp))
                    return io_status::format;
                return io_status::eof;
            }
            erase();
            return init (n, v);
        }
        int operator> (const student& x) const{
            return (cmp (x) > 0 ? 1 : 0);
        }
        int operator< (const student& x) const{
            return (cmp (x) < 0 ? 1 : 0);
        }
        int operator<= (const student& x) const{
            return ((cmp (x) < 0 || cmp (x) == 0) ? 1 : 0);
        }
        int operator>= (const student& x) const{
            return ((cmp (x) > 0 || cmp (x) == 0) ? 1 : 0);
        }
        int operator== (const student& x) const{
            return (cmp (x) == 0 ? 1 : 0);
        }
        void init_f(int res){
            name = new char[8];
            strcpy(name, "Student");
            value = res;
        }
    private:
        io_status init (const char * n, int v){
            value = v;
            if (n != nullptr){
                size_t len = strlen (n);
                name = new char [len + 1];
                if (name != nullptr){
                    for (size_t i = 0; i <= len; i++)
                    name[i] = n[i];
                }
                else
                    return io_status::memory;
            }
            return io_status::success;
        }
        void erase (){
            value = 0;
            if (name != nullptr){
                delete [] name;
                name = nullptr;
            }
        }
        int cmp (const student& x) const{
            if (name == nullptr){
                if (x.name != nullptr)
                    return -1;
                return value - x.value;
            }
            if (x.name == nullptr)
                return 1;
            int res = strcmp (name, x.name);
            if (res)
                return res;
            return value - x.value;
        }
};

class list2_node : public student
{
    private:
        list2_node* next = nullptr;
        list2_node* prev = nullptr;
    public:
        list2_node() = default;
        list2_node(const list2_node&) = delete;
        list2_node(list2_node&& r) : student((student&&)r){
            next = r.next; r.next = nullptr;
            prev = r.prev; r.prev = nullptr;
        }
        ~list2_node(){
            next = nullptr;
            prev = nullptr;
        }
        list2_node& operator= (const list2_node&) = delete;
        list2_node& operator=(list2_node&& r){
            *(student*)(this) = (student&&)r;
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
        void print (unsigned int r = 10, FILE *fp = stdout) const{
            list2_node* curr;
            unsigned int cnt = 0;
            for(curr = head; curr != nullptr; curr = curr->get_next()){
                if (cnt == r) break;
                curr->print(fp);
                cnt++;
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
        void solve1 (unsigned int k){
            unsigned int len = get_length();
            list2_node* curr;
            unsigned int cnt = 0;
            if (k % len == 0) return;
            k = k % len;
            for(curr = head; curr; curr = curr->get_next()){
                if (cnt == (len - k)) break;
                cnt++;
            }
            list2_node* new_head = curr;
            for(; curr->get_next(); curr = curr->get_next()){
            }
            list2_node* tail = curr;
            tail->set_next(head);
            head->set_prev(tail);
            new_head->get_prev()->set_next(nullptr);
            new_head->set_prev(nullptr);
            head = new_head;
        }
};

#endif