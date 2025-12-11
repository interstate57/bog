#include "student.h"

enum class colors{
    invalid,
    red,
    black,
};

template <class T> class rb_tree;
template <class T>
class rb_tree_node : public T
{
    private:
        rb_tree_node<T>* left = 0;
        rb_tree_node<T>* right = 0;
        rb_tree_node<T>* parent = 0;
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
            static_cast<T*>(this)->print_2(fp);
            if (this->parent) {
                std::cout << "(Parent: ";
                static_cast<T*>(this->parent)->print_2(fp);
                std::cout << ")";
            }
            std::cout << std::endl;
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
            if (*x < *curr){
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
            print_subtree(root, 0, 10);
            printf("\n");
            if (!x->parent) {
                root = x;
                x->color = colors::black;
                return;
            }
            rb_tree_node<T>* parent = x->parent;
            if (parent->color == colors::black){ // корень черный, значит, в противном случае grandparent точно есть
                return;
            }
            rb_tree_node<T>* grandparent = parent->parent;
            rb_tree_node<T>* uncle = 0;
            if (parent == grandparent->right){
                uncle = grandparent->left;
                if (!uncle || uncle->color == colors::black){ 
                    if (parent->left == x){
                        printf("5\n");
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
                        printf("6\n");
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
                else{ // перекраска без перестановки
                    printf("7, 8\n");
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
                        printf("1\n");
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
                        printf("2\n");
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
                else{ // перекраска без перестановки 
                    printf("3, 4\n");
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
        int solve1_(b_tree_node<T> * nach, int k, int* res){
            if (!nach)
                return 0;
            int cnt = 1;
            cnt += solve1_(nach->left, k, res) + solve1_(nach->right, k, res);
            if (cnt <= k){
                *res += 1;
            }
            return cnt;
        }

        int solve1(int k){
            int size = 0;
            solve1_(root, k, &size);
            return size;
        }
        int solve2_(b_tree_node<T> * nach, int k, int* res){
            if (!nach){
                return 1;
            }
            int max = 0;
            
            max += 1;
            if (max <= k){
                *res += nach->size;
            }
            return max;
        }
        int solve3(int k){
            int res = 0;
            solve3_(root, k, &res);
            return res;
        }
        int solve5_(b_tree_node<T> * nach, int level){
            if (!nach){
                return 0;
            }
            if (level == 0)
                return nach->size;
            
            int cnt = 0;
            for (int i = 0; i < nach->size + 1; i++){
                cnt += solve5_(nach->children[i], level - 1);
            }
            return cnt;
        }
        int solve5(int k){
            int level = k;
            return solve5_(root, level);
        }
        int solve6_(b_tree_node<T> * nach, int length){
            if (!nach)
                return 0;
            if (length == 0){
                return nach->size;
            }
            int cnt = 0;
            for (int i = 0; i < nach->size + 1; i++){
                cnt += solve6_(nach->children[i], length - 1);
            }
            if (cnt > 0)
                cnt += nach->size;
            return cnt;
        }
        int solve6(int k){
            return solve6_(root, k - 1);
        }
    private:
        static void print_subtree (rb_tree_node<T> * curr, int level, int r,
        FILE *fp = stdout){
            if (curr == nullptr || level > r)
            return;
            int spaces = level * 4; //fix na 2
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