#include "student.h"

template <class T> class avl_tree;
template <class T>
class avl_tree_node : public T
{
    private:
        avl_tree_node<T> * left = nullptr;
        avl_tree_node<T> * right = nullptr;
        int balance = 0;
    public:
        avl_tree_node () = default;
        avl_tree_node (const avl_tree_node<T>& x) = delete;
        avl_tree_node (avl_tree_node<T>&& x) = default;
        ~avl_tree_node () = default;
        avl_tree_node<T>& operator= (const avl_tree_node<T>& x) = delete;
        avl_tree_node<T>& operator= (avl_tree_node<T>&& x) = default;
    friend class avl_tree<T>;
};
template <class T>
class avl_tree
{
    private:
        avl_tree_node<T> * root = nullptr;
    public:
        avl_tree () = default;
        io_status read (FILE * fp = stdin){
            avl_tree_node<T> x;
            avl_tree_node<T>* y;
            int grow;
            while (x.read(fp) == io_status::success){
                y = new avl_tree_node<T> ((avl_tree_node<T>&&)x);
                if (!y){
                    delete_subtree(root);
                    return io_status::memory;
                }
                AddBalance(y, root, &grow);
            }
            if (!feof(fp)){
                delete_subtree(root);
                return io_status::format;
            }
            return io_status::success;
        }
        void print (unsigned int r = 10, FILE *fp = stdout) const{
            print_subtree (root, 0, r, fp);
        }
        avl_tree_node<T>* L1(avl_tree_node<T>* A){
            avl_tree_node<T>* B = A->left;
            A->left = B->right;
            B->right = A;
            if (B->balance){
                A->balance = 0;
                B->balance = 0;
            } 
            else{
                A->balance = -1;
                B->balance = 1;
            }
            return B;
        }
        avl_tree_node<T> *L2(avl_tree_node<T> *A) {
            avl_tree_node<T> *B, *C;
            B = A->left;
            C = B->right;
            A->left = C->right;
            B->right = C->left;
            C->left = B;
            C->right = A;
            switch (C->balance) {
                case 0:
                    A->balance = 0;
                    B->balance = 0;
                    break;
                case -1:
                    A->balance = 1;
                    B->balance = 0;
                    break;
                case 1:
                    A->balance = 0;
                    B->balance = -1;
            }
            C->balance = 0;
            return C;
        }
        avl_tree_node<T>* R1(avl_tree_node<T>* A){
            avl_tree_node<T>* B;
            B = A->right;
            A->right = B->left;
            B->left = A;
            if (B->balance) {
                A->balance = 0;
                B->balance = 0;
            } 
            else{
                A->balance = 1;
                B->balance = -1;
            }
            return B;
        }
        avl_tree_node<T> *R2(avl_tree_node<T> *A) {
            avl_tree_node<T> *B, *C;
            B = A->right;
            C = B->left;
            B->left = C->right;
            A->right = C->left;
            C->left = A;
            C->right = B;
            switch (C->balance){
                case 0:
                    A->balance = 0;
                    B->balance = 0;
                    break;
                case 1:
                    A->balance = -1;
                    B->balance = 0;
                    break;
                case -1:
                    A->balance = 0;
                    B->balance = 1;
            }
            C->balance = 0;
            return C;
        }

        avl_tree_node<T> *AddBalance(avl_tree_node<T>* x, avl_tree_node<T> *root,int *grow){
            int incr;
            *grow = 0;
            /* пустое дерево: */
            if (!root) {
                *root = (avl_tree_node<T>&&)*x;
                if (root) {
                    root->left = root->right = 0;
                    root->balance = 0;
                    *grow = 1;
                }
                return root;
            }
            /* непустое дерево: */
            if (*x <= *root){ // левая балансировка:
                root->left = AddBalance(x, root->left, &incr);
                if (incr){
                    switch (root->balance){
                        case 0:
                            root->balance = -1;
                            *grow = 1;
                            break;
                        case 1:
                            root->balance = 0;
                            break;
                        case -1:
                            switch (root->left->balance){
                                case -1:
                                    root = L1(root);
                                    break;
                                case 1:
                                    root = L2(root);
                            }
                    }
                }
            }
            else{ // правая балансировка:
                root->right = AddBalance(x, root->right, &incr);
                if (incr){
                    switch (root->balance){
                        case 0:
                            root->balance = 1;
                            *grow = 1;
                            break;
                        case -1:
                            root->balance = 0;
                            break;
                        case 1:
                            switch (root->right->balance){
                                case 1:
                                    root = R1(root);
                                    break;
                                case -1:
                                    root = R2(root);
                            }
                    }
                }
            }
            return root;
        }
    private:
        static void delete_subtree (avl_tree_node<T> * curr){
            if (curr == nullptr)
                return;
            delete_subtree (curr->left);
            delete_subtree (curr->right);
            delete curr;
        }
        static void print_subtree (avl_tree_node<T> * curr, int level, int r, FILE *fp = stdout){
            if (curr == nullptr || level > r)
            return;
            int spaces = level * 2;
            for (int i = 0; i < spaces; i++)
                printf (" ");
            curr->print (fp);
            print_subtree (curr->left, level + 1, r, fp);
            print_subtree (curr->right, level + 1, r, fp);
        }
};