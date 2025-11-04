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
        int get_value(){
            return value;
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

class tree;

class tree_node : public student
{
    private:
        tree_node * left = nullptr;
        tree_node * right = nullptr;
    public:
        tree_node () = default;
        tree_node (const tree_node& x) = delete;
        tree_node (tree_node&& x) : student ((student&&)x){
            erase_links ();
            x.erase_links ();
        }
        ~tree_node (){
            erase_links ();
        }
        tree_node& operator= (const tree_node& x) = delete;
        tree_node& operator= (tree_node&& x){
            if (this == &x)
                return *this;
            (student&&) *this = (student&&) x;
            erase_links ();
            x.erase_links ();
            return *this;
        }
        friend class tree;
    private:
        void erase_links ()
        { left = nullptr; right = nullptr; }
};


class tree
{
    private:
        tree_node * root = nullptr;
    public:
        tree () = default;
        tree (const tree& x) = delete;
        tree (tree&& x){
            root = x.root; x.root = nullptr;
        }
        ~tree (){
            delete_subtree (root);
            root = nullptr;
        }
        tree& operator= (const tree& x) = delete;
        tree& operator= (tree&& x){
            if (this == &x)
            return *this;
            delete_subtree (root);
            root = x.root; x.root = nullptr;
            return *this;
        }
        void print (unsigned int r = 10, FILE *fp = stdout) const{
            print_subtree (root, 0, r, fp);
        }
        io_status read (FILE * fp = stdin, unsigned int max_read = -1){
            unsigned int cnt = 0;
            tree_node x;
            while (x.read(fp) == io_status::success){
                cnt += 1;
                if (cnt == max_read) break;
                tree_node* curr = new tree_node((tree_node&&) x);
                if (curr == nullptr){
                    delete_subtree(root);
                    return io_status::memory;
                }
                if (root == nullptr){
                    root = curr;
                }
                else{
                    add_node_subtree(root, curr);
                }
            }
            if (!feof(fp)){
                delete_subtree(root);
                return io_status::format;
            }
            return io_status::success;
        }
        int solve1(tree_node* nach);
        int solve2(tree_node* nach);
        int solve3();
        int solve4(tree_node* nach, int* inner_max);
        int solve5(tree_node* nach);
        int poisk_min(tree_node* nach);
        int cnt_min(tree_node* nach, int min);
        int udalenie(tree_node* nach, int min, tree_node* parent);
        int solve6();
        int solve1_();
        int solve2_();
        int solve3_();
        int solve4_();
        int solve5_();
    private:
        static void delete_subtree (tree_node * curr){
            if (curr == nullptr)
            return;
            delete_subtree (curr->left);
            delete_subtree (curr->right);
            delete curr;
        }
        static void print_subtree (tree_node * curr, int level, int r,
        FILE *fp = stdout){
            if (curr == nullptr || level > r)
            return;
            int spaces = level * 2;
            for (int i = 0; i < spaces; i++)
                printf (" ");
            curr->print (fp);
            print_subtree (curr->left, level + 1, r, fp);
            print_subtree (curr->right, level + 1, r, fp);
        }
        static void add_node_subtree (tree_node * curr, tree_node *x){
            if (*x < *curr){
                if (curr->left == nullptr){
                    curr->left = x;
                }
                else{
                    add_node_subtree(curr->left, x);
                }
            }
            else{
                if (curr->right == nullptr){
                    curr->right = x;
                }
                else{
                    add_node_subtree(curr->right, x);
                }
            }
        }
};

int max(int a, int b);
int max(int a, int b, int c);

#endif