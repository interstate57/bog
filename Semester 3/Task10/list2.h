

#include "student.h"

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
        static int m;
        static int r;
    public:
        list2 () = default;
        ~list2(){
            delete_list();
            head = 0;
        }
        list2 (list2&& x){
            head = x.head;
            x.head = 0;
        }
        list2 operator= (const list2& x) = delete;
        list2& operator= (list2&& x){
            if (this == &x)
                return *this;
            delete_list();
            head = x.head;
            x.head = 0;
            return *this;
        }
        int operator< (const list2& b) const{
            int n = this->get_length();
            int m = b.get_length();
            if ((n == 0 && m > 0) || *head < *b.head)
                return 1;
            return 0;
        }
        io_status read (FILE *fp = stdin){
            list2_node buf;
            io_status ret;
            list2_node *curr, *tail;
            int cnt = 1;
            if ((ret = buf.read(fp)) != io_status::success) return ret;
            head = new list2_node;
            if (head == nullptr) return io_status::memory;
            *head = (list2_node&&)buf;
            curr = head;
            if (m == 1){
                head->set_next(0);
                head->set_prev(0);
                return io_status::success;
            }
            while(buf.read(fp) == io_status::success){
                cnt += 1;
                tail = new list2_node;
                if (tail == nullptr){
                    delete_list();
                    return io_status::memory;
                }
                *tail = (list2_node&&) buf;
                curr->set_next(tail);
                tail->set_prev(curr);
                curr = tail;
                if (cnt == m) {
                    curr->set_next(0);
                    break;
                }
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
        void print (FILE *fp = stdout) const{
            list2_node* curr;
            int cnt = 0;
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
        static void set_m (int m){ 
            list2::m = m; 
        }
        static void set_r (int r){ 
            list2::r = r; 
        }
        int get_value(){
            return head->get_value();
        }
};