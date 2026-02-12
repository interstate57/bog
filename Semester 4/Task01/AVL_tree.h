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
        ~avl_tree_node (){
            erase_links();
        }
        avl_tree_node<T>& operator= (const avl_tree_node<T>& x) = delete;
        avl_tree_node<T>& operator= (avl_tree_node<T>&& x) = default;
    private:
        void erase_links(){
            left = 0; right = 0; balance = 0;
        }
    friend class avl_tree<T>;
};
template <class T>
class avl_tree
{
    private:
        avl_tree_node<T> * root = nullptr;
    public:
        avl_tree () = default;
        ~avl_tree(){
            delete_subtree(root);
            root = 0;
        }
        io_status read (FILE * fp = stdin){
            avl_tree_node<T> x;
            int grow;
            while (x.read(fp) == io_status::success){
                root = AddBalance(x, root, &grow);
                if (root == 0)
                    break;
                //printf("%s\n", (root == 0 ? "Xyu" : "Pizda"));
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



        avl_tree_node<T> *AddBalance(avl_tree_node<T>& x, avl_tree_node<T> *nach,int *grow){
            int incr;
            *grow = 0;
            /* пустое дерево: */
            if (nach == 0) {
                nach = new avl_tree_node<T> ((avl_tree_node<T>&&)x);
                if (nach) {
                    nach->left = nach->right = 0;
                    nach->balance = 0;
                    *grow = 1;
                }
                return nach;
            }
            /* непустое дерево: */
            if (x <= *nach){ // левая балансировка:
                nach->left = AddBalance(x, nach->left, &incr);
                if (incr){
                    switch (nach->balance){
                        case 0:
                            nach->balance = -1;
                            *grow = 1;
                            break;
                        case 1:
                            nach->balance = 0;
                            break;
                        case -1:
                            switch (nach->left->balance){
                                case -1:
                                    nach = L1(nach);
                                    break;
                                case 1:
                                    nach = L2(nach);
                            }
                    }
                }
            }
            else{ // правая балансировка:
                nach->right = AddBalance(x, nach->right, &incr);
                if (incr){
                    switch (nach->balance){
                        case 0:
                            nach->balance = 1;
                            *grow = 1;
                            break;
                        case -1:
                            nach->balance = 0;
                            break;
                        case 1:
                            switch (nach->right->balance){
                                case 1:
                                    nach = R1(nach);
                                    break;
                                case -1:
                                    nach = R2(nach);
                            }
                    }
                }
            }
            return nach;
        }
        bool name_from_s(avl_tree_node<T>* curr, const char* s){
            size_t len = curr->length();
            if (len == strspn(curr->get_name(), s))
                return true;
            return false;
        }
        bool is_balanced() const {
            int height;
            return is_balanced_(root, &height);
        }
        bool is_balanced_(avl_tree_node<T>* nach, int* height) const {
            if (!nach) {
                *height = 0;
                return true;
            }
            *height = 0;
            int height_left = 0;
            int height_right = 0;
            if (nach->left) {
                if (!is_balanced_(nach->left, &height_left))
                    return false;
            }
            if (nach->right) {
                if (!is_balanced_(nach->right, &height_right))
                    return false;
            }
            if (std::abs(height_left - height_right) > 1)
                return false;
            *height = std::max(height_left, height_right) + 1;
            return true;
        }
        int solve1_(avl_tree_node<T>* nach, const char* s){
            if (!nach)
                return 0;
            if (nach->left == 0 && nach->right == 0){
                if (name_from_s(nach, s))
                    return 1;
                return 0;
            }
            return solve1_(nach->left, s) + solve1_(nach->right, s);
        }
        int solve1(const char* s){
            return solve1_(root, s);
        }
        int solve2_(avl_tree_node<T>* nach, const char* s){
            if (!nach)
                return 0;
            if (!name_from_s(nach, s))
                return 0;
            if (!nach->left && !nach->right)
                return 1;
            int res = 0;
            if (nach->left) {
                res = solve2_(nach->left, s);
            }
            if (nach->right) {
                res = std::max(res, solve2_(nach->right, s));
            }
            if (res > 0) {
                res += 1;
            }
            return res;
        }
        int solve2(const char* s){
            return solve2_(root, s);
        }
        int solve3_(avl_tree_node<T>* nach, const char* s, int* cnt){
            if (!nach)
                return 0;
            int left = solve3_(nach->left, s, cnt);
            int right = solve3_(nach->right, s, cnt);
            bool left_good = (!nach->left) || left > 0;//name_from_s(nach->left, s);
            bool right_good = (!nach->right) || right > 0;
            bool parent_good = name_from_s(nach, s);
            int res = left + right + 1;
            if (left_good && right_good && parent_good) {
                *cnt += 1;
            }
            else {
                res = 0;
            }
            return res;
        }
        int solve3(const char* s){
            int cnt = 0;
            solve3_(root, s, &cnt);
            return cnt;
        }
        int solve5_(avl_tree_node<T>* nach, const char* s, int* max){
            if (!nach)
                return 0;
            int parent = name_from_s(nach, s);
            int res_r = solve5_(nach->right, s, max);
            int res_l = solve5_(nach->left, s, max);
            //*max = std::max(std::abs(res_r - res_l), *max);
            *max = (std::abs(res_l - res_r) > *max) ? res_l - res_r : *max;
            if (parent)
                return res_r + res_l + 1;
            return res_r + res_l;
        }
        int solve5(const char* s){
            int max = 0;
            solve5_(root, s, &max);
            return max;
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
            if (curr == nullptr || level >= r)
            return;
            int spaces = level * 2;
            for (int i = 0; i < spaces; i++)
                printf (" ");
            curr->print (fp);
            print_subtree (curr->left, level + 1, r, fp);
            print_subtree (curr->right, level + 1, r, fp);
        }
};