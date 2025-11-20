#include "student.h"

class tree;
class tree_node : public student
{
    private:
        tree_node * down = nullptr;
        tree_node * level = nullptr;
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
        void erase_links (){
            down = nullptr;
            level = nullptr;
        }
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
    void print (int r) const{
        print_subtree (root, 0, r);
    }
    io_status read (FILE * fp){
        tree_node x;
        while (x.read(fp) == io_status::success){
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
    int solve1(tree_node* nach, int k);
    int a1(int k);
    int solve2(tree_node* nach, int k, int* size);
    int a2(int k);
    int solve3(tree_node* nach, int k, int* height);
    int a3(int k);
    int solve4(tree_node* nach, int k, int curr_level);
    int a4(int k);
    int solve5(tree_node* nach, int k, int curr_level);
    int a5(int k);
    int solve6(tree_node* nach, int k, int curr_level);
    int a6(int k);
    void delete_subtree_dop(tree_node* curr, int k, int* cnt);
    int solve7(tree_node* nach, int k);
    int a7(int k);
    private:
    static void delete_subtree (tree_node * curr){
        if (curr == nullptr)
            return;
        tree_node * p, * next;
        for (p = curr->down; p; p = next){
            next = p->level;
            delete_subtree (p);
        }
        delete curr;
    }
    static void print_subtree (tree_node * curr, int level, int r){
        if (curr == nullptr || level > r)
            return;
        int spaces = level * 2;
        for (int i = 0; i < spaces; i++)
            printf (" ");
        curr->print ();
        for (tree_node * p = curr->down; p; p = p->level)
            print_subtree (p, level + 1, r);
    }
    static void add_node_subtree (tree_node* curr, tree_node* x){
        if (curr->down == nullptr){ // No any child node
            curr->down = x;
            return;
        }
        if (*x < *curr){
            if (*curr->down < *curr)
            // head of the list of child nodes < *curr
                add_node_subtree (curr->down, x);
            else{
                x->level = curr->down;
                curr->down = x;
            }
        }
        else if (*x == *curr){
            if (curr->down->level != nullptr){
                x->level = curr->down->level;
                curr->down->level = x;
            }
            else if (*curr->down < *curr){
                curr->down->level = x;
            }
            else{
                x->level = curr->down;
                curr->down = x;
            }
        }
        else{
            tree_node * p;
            for (p = curr->down; p->level; p = p->level){
                if (*p > *curr)
                // tail of the list of child nodes > *curr
                        add_node_subtree (p, x);
                else
                    p->level = x; // append at end of the list
            }
        }
    }
};