#ifndef RB_TREE_H
#define RB_TREE_H
#include <stdio.h>
#include <string.h>
#include <memory>
#include "io_status.h"

enum class colors{
    invalid,
    red,
    black,
};

template <class T> class rb_tree;
template <class T>
class rb_tree_node
{
    private:
        rb_tree_node<T>* left = 0;
        rb_tree_node<T>* right = 0;
        rb_tree_node<T>* parent = 0;
        T word = 0;
        colors color = colors::invalid;
    public:
        rb_tree_node () = default;
        rb_tree_node (const rb_tree_node<T>& x) = delete;
        rb_tree_node (rb_tree_node<T>&& x) : T ((T&&) x){
            erase_links ();
            left = x.left;
            right = x.right;
            parent = x.parent;
            color = x.color;
            x.erase_links ();
        }
        ~rb_tree_node (){
            erase_links ();
        }
        rb_tree_node<T>& operator= (const rb_tree_node<T>& x) = delete;
        rb_tree_node<T>& operator= (rb_tree_node<T>&& x){
            if (this == &x)
                return *this;
            (T&&) *this = (T&&) x;
            erase_links ();
            x.erase_links ();
            return *this;
        }
        void print (FILE * fp = stdout){
            switch (color)
            {
                case colors::red:
                fprintf(fp, "RED:   ");
                break;
                case colors::black:
                fprintf(fp, "BLACK: ");
                break;
                case colors::invalid:
                fprintf(fp, "invalid ");
                break;
            };
            static_cast<T*>(this)->print(fp);
        }
        friend class rb_tree<T>;
    private:
        void erase_links(){
            right = 0;
            left = 0;
            parent = 0;
            color = colors::invalid;
        }
};

template <class T>
class rb_tree
{
    private:
        rb_tree_node<T>* root = 0;
    public:
        rb_tree () = default;
        ~rb_tree (){
            delete_subtree (root);
            root = nullptr;
        }
        io_status read (FILE* fp){
            rb_tree_node<T> x;
            rb_tree_node<T>* y;
            while (x.read(fp) == io_status::success){
                y = new rb_tree_node<T> ((rb_tree_node<T>&&)x);
                if (!y){
                    delete_subtree(root);
                    return io_status::memory;
                }
                add_node(y);
            }
            if (!feof(fp)){
                delete_subtree(root);
                return io_status::format;
            }
            return io_status::success;
        }
        io_status add_word(T& str) {
			rb_tree_node<T> *curr;
			if (*str == nullptr) {
				return io_status::success;
			}
			curr = new rb_tree_node<T>();
			if (!curr) {
				return io_status::memory;
			}
			curr->word = std::make_unique<char *>(*str.get());
			if (!(curr->word)) {
				delete curr;
				return io_status::memory;
			}
			add_node(curr);
			return io_status::success;
		}

		int find_word(T& str) {
			rb_tree_node<T> *curr = root;
			while (curr) {
				int cmp = strcmp(*curr->word.get(), *str);
				if (cmp == 0) {
					return 1;
				}
				else if (cmp > 0) {
					curr = curr->left;
				}
				else {
					curr = curr->right;
				}
			}
			return 0;
		}
        void add_node (rb_tree_node<T>* x){
            if (root == 0){
                root = x;
                root->color = colors::black;
            }
            else{
                add_rb_subtree(root, x);
            }
        }
        void add_rb_subtree (rb_tree_node<T>* curr, rb_tree_node<T>* x){
            if (strcmp(*x->word, *curr->word) < 0){
                if (curr->left == 0){
                    curr->left = x;
                    x->parent = curr;
                    x->color = colors::red;
                    fix_tree(x);
                }
                else{
                    add_rb_subtree(curr->left, x);
                }
            }
            else{
                if (curr->right == 0){
                    curr->right = x;
                    x->parent = curr;
                    x->color = colors::red;
                    fix_tree(x);
                }
                else{
                    add_rb_subtree(curr->right, x);
                }
            }
        }
        void fix_tree(rb_tree_node<T>* x){
            if (!x->parent) {
                root = x;
                x->color = colors::black;
                return;
            }
            rb_tree_node<T>* parent = x->parent;
            if (parent->color == colors::black){
                return;
            }
            rb_tree_node<T>* grandparent = parent->parent;
            rb_tree_node<T>* uncle = 0;
            if (parent == grandparent->right){
                uncle = grandparent->left;
                if (!uncle || uncle->color == colors::black){ 
                    if (parent->left == x){
                        x->parent = grandparent->parent;
                        if (x->parent == 0) {
                            root = x;
                        }
                        else{
                            if (x->parent->left == grandparent) {
                                x->parent->left = x;
                            } 
                            else{
                                x->parent->right = x;
                            }
                        }
                        grandparent->left = uncle;
                        if (uncle){
                            uncle->parent = grandparent;
                        }
                        grandparent->right = x->left;
                        if (x->left){
                            x->left->parent = grandparent;
                        }
                        x->left = grandparent;
                        grandparent->parent = x;
                        parent->left = x->right;
                        if (x->right){
                            x->right->parent = parent;
                        }
                        x->right = parent;
                        parent->parent = x;
                        x->color = colors::black;
                        grandparent->color = colors::red;
                    }
                    else{
                        parent->parent = grandparent->parent;
                        if (parent->parent == 0)
                            root = parent;
                        else{
                            if (parent->parent->left == grandparent) {
                                parent->parent->left = parent;
                            } 
                            else{
                                parent->parent->right = parent;
                            }
                        }
                        grandparent->right = parent->left;
                        if (parent->left){
                            parent->left->parent = grandparent;
                        }
                        parent->left = grandparent;
                        grandparent->parent = parent;
                        parent->color = colors::black;
                        grandparent->color = colors::red;
                    }
                }
                else{
                    grandparent->color = colors::red;
                    uncle->color = colors::black;
                    parent->color = colors::black;
                    this->fix_tree(grandparent);
                }
            }
            else{
                uncle = grandparent->right;
                if (!uncle || uncle->color == colors::black){ 
                    if (parent->left == x){
                        parent->parent = grandparent->parent;
                        if (parent->parent == nullptr)
                            root = parent;
                        else{
                            if (parent->parent->left == grandparent) {
                                parent->parent->left = parent;
                            } 
                            else{
                                parent->parent->right = parent;
                            }
                        }
                        grandparent->left = parent->right;
                        if (parent->right){
                            parent->right->parent = grandparent;
                        }
                        parent->right = grandparent;
                        grandparent->parent = parent;
                        parent->color = colors::black;
                        grandparent->color = colors::red;
                    }
                    else{
                        x->parent = grandparent->parent;
                        if (x->parent == nullptr)
                            root = x;
                        else{
                            if (x->parent->left == grandparent) {
                                x->parent->left = x;
                            } 
                            else{
                                x->parent->right = x;
                            }
                        }
                        grandparent->left = x->right;
                        if (x->right){
                            x->right->parent = grandparent;
                        }
                        grandparent->right = uncle;
                        if (uncle){
                            uncle->parent = grandparent;
                        }
                        x->right = grandparent;
                        grandparent->parent = x;
                        parent->right = x->left;
                        if (x->left){
                            x->left->parent = parent;
                        }
                        x->left = parent;
                        parent->parent = x;
                        x->color = colors::black;
                        grandparent->color = colors::red;
                    }
                }
                else{
                    grandparent->color = colors::red;
                    uncle->color = colors::black;
                    parent->color = colors::black;
                    fix_tree(grandparent);
                }
            }
        }
        void print (unsigned int r = 10, FILE *fp = stdout) const{
            print_subtree (root, 0, r, fp);
        }
    private:
        static void print_subtree (rb_tree_node<T> * curr, int level, int r,
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
        static void delete_subtree (rb_tree_node<T> * curr){
            if (curr == nullptr)
            return;
            delete_subtree (curr->left);
            delete_subtree (curr->right);
            delete curr;
        }
};

#endif