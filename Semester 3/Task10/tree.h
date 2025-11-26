#include "student.h"

template <class T> class tree;

template <class T>
class tree_node : public T
{
    private:
        tree_node * left = nullptr;
        tree_node * right = nullptr;
    public:
        tree_node () = default;
        tree_node (const tree_node& x) = delete;
        tree_node (tree_node&& x) : T ((T&&)x){
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
            (T&&) *this = (T&&) x;
            erase_links ();
            x.erase_links ();
            return *this;
        }
        friend class tree<T>;
    private:
        void erase_links ()
        { left = nullptr; right = nullptr; }
};

template <class T>
class tree
{
    private:
        tree_node<T> * root = nullptr;
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
            tree_node<T> x;
            while (x.read(fp) == io_status::success){
                cnt += 1;
                tree_node<T>* curr = new tree_node<T>((tree_node<T>&&) x);
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
                if (cnt == max_read) break;
            }
            if (!feof(fp)){
                delete_subtree(root);
                return io_status::format;
            }
            return io_status::success;
        }
        int solve1(tree_node<T>* nach);
        int solve2(tree_node<T>* nach);
        void solve3(tree_node<T>* nach, int ur, int* b);
        int solve4(tree_node<T>* nach, int* inner_max);
        int solve5(tree_node<T>* nach);
        int poisk_min(tree_node<T>* nach);
        int cnt_min(tree_node<T>* nach, int min);
        int udalenie(tree_node<T>* nach, int min, tree_node<T>* parent);
        int solve6();
        int solve1_();
        int solve2_();
        int solve3_();
        int solve4_();
        int solve5_();
    private:
        static void delete_subtree (tree_node<T> * curr){
            if (curr == nullptr)
            return;
            delete_subtree (curr->left);
            delete_subtree (curr->right);
            delete curr;
        }
        static void print_subtree (tree_node<T> * curr, int level, int r,
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
        static void add_node_subtree (tree_node<T> * curr, tree_node<T> *x){
            /*curr->print();
            x->print();
            printf("\n");*/
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

template <class T>
int tree<T>::solve1(tree_node<T>* nach){
    int cnt = 0;
    tree_node<T>* curr = nach;
    if (!curr->left && !curr->right) cnt += 1;
    if (curr->left != nullptr){
        cnt += solve1(curr->left);
    }
    if (curr->right != nullptr){
        cnt += solve1(curr->right);
    }
    return cnt;
}

int max(int a, int b){
    return a > b ? a : b;
}

template <class T>
int tree<T>::solve2(tree_node<T>* nach){
    if (!nach) return 0;
    return max(1 + solve2(nach->left), 1 + solve2(nach->right));
}

int max3(int a, int b, int c){
    return max(a, max(b, c));
}

template <class T>
int tree<T>::solve3_(){
    int glub = solve2_();
    int* b = new int [glub];
    for (int i = 0; i < glub; i++){
        b[i] = 0;
    }
    solve3(root, 0, b);
    int max = b[0];
    for (int i = 1; i < glub; i++){
        if (max < b[i]){
            max = b[i];
        }
    }
    delete [] b;
    return max;
}

template <class T>
void tree<T>::solve3(tree_node<T>* nach, int ur, int* b){
    b[ur] += 1;
    if (nach->left)
        solve3(nach->left, ur + 1, b);
    if (nach->right)
        solve3(nach->right, ur + 1, b);
    return;
}

template <class T>
int tree<T>::solve4(tree_node<T>* nach, int* inner_max){
    if (!nach) return 0;
    int left = 0, right = 0;
    int hleft = solve4(nach->left, &left);
    int hright = solve4(nach->right, &right);
    *inner_max = max3(std::abs(hleft - hright), left, right);
    return max(hleft, hright) + 1;
}

template <class T>
int tree<T>::solve5(tree_node<T>* nach){
    if (!nach) return 0;
    int res = solve5(nach->left) + solve5(nach->right);
    if ((!nach->left && nach->right) || (!nach->right && nach->left))
        res = res + 1;
    return res;
}

template <class T>
int tree<T>::solve6(){
    int fl = 0;
    int min = poisk_min(root);
    if (root)
        fl = (root->get_value() == min);
    
    int res = udalenie(root, min, 0);
    if (fl)
        root = nullptr;
    return res;
}

template <class T>
int tree<T>::poisk_min(tree_node<T>* nach){
    int res = nach->get_value();
    if (nach->left) {
        res = std::min(res, poisk_min(nach->left));
    }
    if (nach->right) {
        res = std::min(res, poisk_min(nach->right));
    }
    return res;
}

template <class T>
int tree<T>::cnt_min(tree_node<T>* nach, int min){
    if (!nach) return 0;
    int res = nach->get_value() == min ? 1 : 0;
    res += cnt_min(nach->left, min) + cnt_min(nach->right, min);
    return res;
}

template <class T>
int tree<T>::udalenie(tree_node<T>* nach, int min, tree_node<T>* parent){
    if (!nach)
        return 0;

    int res = cnt_min(nach, min);
    if (nach->get_value() == min) {
        delete_subtree(nach);
        if (parent && parent->left == nach) {
            parent->left = nullptr;
        }
        else if (parent && parent->right == nach) {
            parent->right = nullptr;
        }
        return res;
    }
    udalenie(nach->left, min, nach);
    udalenie(nach->right, min, nach);
    return res;
}

template <class T>
int tree<T>::solve1_(){
    return solve1(root);
}

template <class T>
int tree<T>::solve2_(){
    return solve2(root);
}

template <class T>
int tree<T>::solve4_(){
    int inner_max = 0;
    solve4(root, &inner_max);
    return inner_max;
}

template <class T>
int tree<T>::solve5_(){
    return solve5(root);
}