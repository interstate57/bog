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
        void solve1 (int k){
            if (k < 0) return;
            int len = (int) get_length();
            list2_node* curr;
            int cnt = 0;
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
        void solve2 (int k){
            if (k <= 0) return;
            list2_node* curr;
            for(curr = head; curr->get_next(); curr = curr->get_next()){
            }
            list2_node* tail = curr;
            for (curr = tail; curr; ){
                int cnt = 0;
                int fl = 0;
                list2_node* pr = curr;
                while(cnt < k){
                    if (pr->get_prev() == nullptr) break;
                    pr = pr->get_prev();
                    if (*curr > *pr){
                        fl = 1;
                        break;
                    }
                    cnt++;
                }
                if (fl == 1){
                    list2_node* priv = curr->get_prev();
                    if (curr->get_prev()){
                        curr->get_prev()->set_next(curr->get_next());
                    }
                    if (curr->get_next()){
                        curr->get_next()->set_prev(curr->get_prev());
                    }
                    delete curr;
                    curr = priv;
                }
                else{
                    curr = curr->get_prev();
                }
            }
        }
        void solve3 (int k){
            if (k <= 0) return;
            list2_node* curr;
            for (curr = head; curr; ){
                int cnt = 0;
                int fl = 0;
                list2_node* pr = curr;
                while(cnt < k){
                    if (pr->get_next() == nullptr) break;
                    pr = pr->get_next();
                    if (*curr > *pr){
                        fl = 1;
                        break;
                    }
                    cnt++;
                }
                if (fl == 1){
                    list2_node* sl = curr->get_next();
                    if (curr->get_prev()){
                        curr->get_prev()->set_next(curr->get_next());
                    }
                    if (curr->get_next()){
                        curr->get_next()->set_prev(curr->get_prev());
                    }
                    if (curr == head) head = sl;
                    delete curr;
                    curr = sl;
                }
                else{
                    curr = curr->get_next();
                }
            }
        }
        void solve5 (int k){
            list2_node* curr;
            int cnt = 1;
            int sch = 0;
            if (k < 0) return;
            for (curr = head; curr; ){
                list2_node* pr = curr;
                if (cnt == 1){
                    sch = 0;
                    while(true){
                        if (pr->get_next() == nullptr) break;
                        pr = pr->get_next();
                        if (*curr == *pr){
                            cnt += 1;
                        }
                        else{
                            break;
                        }
                    }
                }
                if (cnt > k){
                    sch += 1;
                    list2_node* sl = curr->get_next();
                    if (curr->get_prev()){
                        curr->get_prev()->set_next(curr->get_next());
                    }
                    if (curr->get_next()){
                        curr->get_next()->set_prev(curr->get_prev());
                    }
                    if (curr == head) head = sl;
                    delete curr;
                    curr = sl;
                    if (sch == cnt) cnt = 1;
                }
                else{
                    cnt = 1;
                    curr = curr->get_next();
                }
            }
        }
        void solve6 (int k){
            list2_node* curr;
            int cnt = 1;
            int sch = 0;
            if (k < 0) return;
            for (curr = head; curr; ){
                list2_node* pr = curr;
                if (cnt == 1){
                    sch = 0;
                    list2_node* next;
                    while(true){
                        if (pr->get_next() == nullptr) break;
                        next = pr->get_next();
                        if (*pr >= *next){
                            cnt += 1;
                        }
                        else{
                            break;
                        }
                        pr = next;
                    }
                }
                if (cnt > k){
                    sch += 1;
                    list2_node* sl = curr->get_next();
                    if (curr->get_prev()){
                        curr->get_prev()->set_next(curr->get_next());
                    }
                    if (curr->get_next()){
                        curr->get_next()->set_prev(curr->get_prev());
                    }
                    if (curr == head) head = sl;
                    delete curr;
                    curr = sl;
                    if (sch == cnt) cnt = 1;
                }
                else{
                    cnt = 1;
                    curr = curr->get_next();
                }
            }
        }
        void solve7 (int k){
            list2_node* curr;
            int cnt1 = 1;
            int cnt2 = 1;
            int fl = 0;
            list2_node* nach_ud = nullptr;
            list2_node* kon_ud = nullptr;;
            if (k < 0) return;
            for (curr = head; curr->get_next(); curr = curr->get_next()){
                if (*curr == *(curr->get_next())){
                    if (fl == 0){
                        cnt1 += 1;
                        fl = 1;
                    }
                    else if (fl == 1){
                        cnt1 += 1;
                    }
                    else if (fl == 2){
                        kon_ud = curr->get_prev();
                        cnt2 += 1;
                        fl = 3;
                    }
                    else if (fl == 3){
                        cnt2 += 1;
                    }
                }
                else{
                    if (fl == 0 || fl == 2){
                    }
                    else if (fl == 1){
                        if (cnt1 <= k){
                            cnt1 = 1;
                            fl = 0;
                        }
                        else{
                            nach_ud = curr->get_next();
                            fl = 2;
                        }
                    }
                    else if (fl == 3){
                        if (cnt2 <= k){
                            cnt2 = 1;
                            fl = 2;
                        }
                        else{
                            list2_node* dop = nach_ud;
                            list2_node* cmp = kon_ud->get_next();
                            nach_ud->get_prev()->set_next(kon_ud->get_next());
                            cmp->set_prev(nach_ud->get_prev());
                            while (dop != cmp){
                                list2_node* dopdop = dop->get_next();
                                delete dop;
                                dop = dopdop;
                            }
                            cnt1 = cnt2;
                            cnt2 = 1;
                            fl = 2;
                            nach_ud = curr->get_next();
                        }
                    }
                }
            }
            if (fl == 3){
                if (cnt2 <= k){
                }
                else{
                    list2_node* dop = nach_ud;
                    list2_node* cmp = kon_ud->get_next();
                    nach_ud->get_prev()->set_next(kon_ud->get_next());
                    cmp->set_prev(nach_ud->get_prev());
                    while (dop != cmp){
                        list2_node* dopdop = dop->get_next();
                        delete dop;
                        dop = dopdop;
                    }
                }
            }
        }
        void solve8 (int k){
            list2_node* curr;
            int cnt = 0;
            int fl = 0;
            list2_node* nach_ud = nullptr;
            list2_node* kon_ud = nullptr;;
            if (k < 0) return;
            for (curr = head; curr->get_next(); curr = curr->get_next()){
                if (*curr <= *(curr->get_next())){
                    if (fl == 0){
                        fl = 1;
                    }
                    else if (fl == 1){
                    }
                    else if (fl == 2){
                        kon_ud = curr->get_prev();
                        fl = 1;
                        if (cnt > k){
                            list2_node* dop = nach_ud;
                            list2_node* cmp = kon_ud->get_next();
                            nach_ud->get_prev()->set_next(kon_ud->get_next());
                            cmp->set_prev(nach_ud->get_prev());
                            while (dop != cmp){
                                list2_node* dopdop = dop->get_next();
                                delete dop;
                                dop = dopdop;
                            }
                        }
                        nach_ud = nullptr;
                        kon_ud = nullptr;
                    }
                }
                else{
                    if (fl == 0){
                    }
                    else if (fl == 1){
                        nach_ud = curr->get_next();
                        fl = 2;
                    }
                    else if (fl == 2){
                        cnt += 1;
                    }
                }
            }
        }
};

#endif