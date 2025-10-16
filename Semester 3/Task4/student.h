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
        void print () const{
            printf ("%s %d\n", name, value);
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

class list_node : public student
{
    private:
        list_node* next = nullptr;
    public:
        list_node() = default;
        list_node(const list_node&) = delete;
        list_node(list_node&& r) : student((student&&)r){
            next = r.next; r.next = nullptr;
        }
        ~list_node(){
            next = nullptr;
        }
        list_node& operator= (const list_node&) = delete;
        list_node& operator=(list_node&& r){
            *(student*)(this) = (student&&)r;
            next = r.next; r.next = nullptr;
            return *this;
        }
        list_node* get_next() const{
            return next;
        }
        void set_next(list_node* r){
            next = r;
        }
};

#endif