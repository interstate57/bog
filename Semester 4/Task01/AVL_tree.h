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
    int read (FILE * fp = stdin){
        avl_tree_node<T>* root = 0;
        T x;
        int incr;
        while (x.read(fp) == 1){
            root = AddBalance(x, root, &incr);
            if (root == 0){
                break;
            }
        }
    }
    void print (int r, FILE *fp = stdout);
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

    avl_tree_node<T> *AddBalance(T x, avl_tree_node<T> *root,int *grow){
        int incr;
        *grow = 0;
        /* пустое дерево: */
        if (!root) {
            root = new avl_tree_node<T> ((avl_tree_node<T>&&)x);
            if (root) {
                root->left = root->right = 0;
                root->value = x;
                root->balance = 0;
                *grow = 1;
            }
            return root;
        }
        /* непустое дерево: */
        if (x <= root->value){ // левая балансировка:
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
                                root = Rebuild_L1(root);
                                break;
                            case 1:
                                root = Rebuild_L2(root);
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
                                root = Rebuild_R1(root);
                                break;
                            case -1:
                                root = Rebuild_R2(root);
                        }
                }
            }
        }
        return root;
    }
};