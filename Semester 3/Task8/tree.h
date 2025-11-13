#ifndef tree_H
#define tree_H
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include "student.h"

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
        int solve1(tree_node* nach) const;
        int solve2(tree_node* nach) const;
        void solve3(tree_node* nach, int ur, int* b) const;
        int solve4(tree_node* nach, int* inner_max) const;
        int solve5(tree_node* nach) const;
        int solve6(tree_node* nach) const;
        int solve7(tree_node* nach) const;
        int poisk_min(tree_node* nach);
        int cnt_min(tree_node* nach, int min);
        int udalenie(tree_node* nach, int min, tree_node* parent);
        int get_count_leaf() const;
        int get_height() const;
        int get_width() const;
        int get_balance() const;
        int get_count_1() const;
        int get_count_2() const;
        int get_count_total() const;
        void a1();
        void fix_down(tree_node* nach);
        void heapify(tree_node* nach);
        tree_node* find_left_leaf(tree_node* nach, tree_node** parent, int cnt);
        void swap_elements_left(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf);
        tree_node* leftmost(tree_node* nach, tree_node** arr, int* size);
        tree_node* get_next_left(tree_node* nach, tree_node** arr, int* size);
        void a3();
        tree_node* find_right_leaf(tree_node* nach, tree_node** parent, int cnt);
        void swap_elements_right(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf);
        tree_node* rightmost(tree_node* nach, tree_node** arr, int* size);
        tree_node* get_next_right(tree_node* nach, tree_node** arr, int* size);
        void a4();
        void find_sk_subtrees(tree_node* curr, char* s, int k, int* height, bool* is_s_subtree);
        void a5(const student& student);
        void find_sk_branches(tree_node* curr, char* s, int k, int* height, bool* is_s_subtree);
        void a6(const student& student);
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
        static void swap(tree_node* first, tree_node* second){
            char * ntmp = first->get_name();
            int vtmp = first->get_value();
            first->set_name(second->get_name());
            second->set_name(ntmp);
            first->set_value(second->get_value());
            second->set_value(vtmp);
        }
};

#endif