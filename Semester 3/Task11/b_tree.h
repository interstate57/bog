#include "student.h"
template <class T> class b_tree_node;
template <class T> class b_tree;
template <class T>
class b_tree_node
{
    private:
        T* values = nullptr; // 2*m elements array
        int size = 0; // number of children
        b_tree_node** children = nullptr; // 2*m+1 elements array
    public:
        b_tree_node () = default;
        b_tree_node (const b_tree_node& x) = delete;
        b_tree_node (b_tree_node&& x){
            values = x.values;
            children = x.children;
            size = x.size;
            x.erase_links ();
        }
        b_tree_node& operator= (const b_tree_node& x) = delete;
        b_tree_node& operator= (b_tree_node&& x){
            if (this == &x)
                return *this;
            delete_node ();
            values = x.values;
            children = x.children;
            size = x.size;
            x.erase_links ();
            return *this;
        }
        ~b_tree_node (){
            delete_node ();
        }
        void print (int p = 0, FILE* fp = stdout){
            for (int i = 0; i < size; ++i){
                for (int j = 0; j < p; j++)
                    fprintf(fp, " ");
                fprintf (fp, "values[%2d] ", i + 1);
                values[i].print (fp);
            }
        }
        // Look for position for insert
        int bin_search (const T& x) const{
            int l = 0, r = size, m;
            while (l != r){
                m = (l + r) / 2;
                if (values[m] < x)
                    l = m + 1;
                else
                    r = m;
            }
            return l;
        }
        friend class b_tree<T>;
    private:
        void erase_links (){
            values = nullptr;
            children = nullptr;
            size = 0;
        }
        void delete_node (){
            if (values != nullptr)
                delete[] values; // destructor for each value[i]
            if (children != nullptr)
            // each children[i] is T* - standard type
                delete[] children;
            erase_links ();
        }
        io_status init (int m){
        // default constructor for T is called
            values = new T[2 * m];
            if (values == nullptr)
                return io_status::memory;
            children = new b_tree_node*[2 * m + 1];
            if (children == nullptr){
                delete[] values;
                values = nullptr;
                return io_status::memory;
            }
            for (int i = 0; i < 2 * m + 1; ++i)
            // there is no default constructor for T*
                children[i] = nullptr;
            size = 0;
            return io_status::success;
        }
        // Insert value ’x’ with children ’down’ at position ’index’
        // into the node (assuming enough space)
        void add_value (T& x, b_tree_node<T>* down, int index){
            for (int i = size; i > index; i--){
                values[i] = static_cast<T&&>(values[i - 1]);
                children[i + 1] = children[i];
            }
            values[index] = static_cast<T&&>(x);
            children[index + 1] = down;
            size++;
        }
};

template <class T>
class b_tree
{
    private:
        int m = 0; // B-tree base
        b_tree_node<T> * root = nullptr;
    public:
        b_tree (int i = 0) { m = i; }
        io_status read (FILE * fp = stdin){ 
           T x;
            while (x.read(fp) == io_status::success){
                io_status dop;
                dop = add_value(x);
                if (dop != io_status::success){
                    delete_subtree(root);
                    return io_status::memory;
                }
            }
            if (!feof(fp)){
                delete_subtree(root);
                return io_status::format;
            }
            return io_status::success;
        }
        void print (int r, FILE * fp = stdout) const{
            print_subtree (root, 0, r, fp);
        }
        ~b_tree(){
            delete_subtree (root);
            erase_links ();
        }

        int solve1_(b_tree_node<T> * nach, int k){
            if (!nach || !nach->children)
                return 0;
            int i = 0;
            int cnt = 0;
            b_tree_node<T>* curr = 0;
            for (i = 0; i < nach->size + 1; i++){
                curr = nach->children[i];
                cnt += solve1_(curr, k);
            }
            if (cnt == k)
                return i;
            return 0;
        }
        
        int solve1(int k){
            return solve1_(root, k);
        }
        /*
        int solve2_(b_tree_node<T> * nach, int k, int* res){
            if (!nach->children){
                *res += nach->size;
                return 1;
            }
            int i = 0;
            int cnt = 0;
            b_tree_node<T>* next = 0;
            for (b_tree_node<T>* curr = nach->children[i]; curr; curr = next){
                cnt += solve2_(curr, k, res);
                i += 1;
                next = nach->children[i];
            }
            cnt += 1;
            if (cnt <= k){
                *res += i;
            }
            return cnt;
        }*/

        int solve2_(b_tree_node<T> * nach, int k, int* res){
            if (!nach || !nach->children)
                return 0;
            int i = 0;
            int cnt = 0;
            b_tree_node<T>* curr = 0;
            for (i = 0; i < nach->size + 1; i++){
                curr = nach->children[i];
                cnt += solve2_(curr, k, res);
            }
            cnt += 1;
            if (cnt <= k){
                *res += i;
            }
            return cnt;
        }

        int solve2(int k){
            int size = 0;
            solve2_(root, k, &size);
            return size;
        }
        int solve3_(b_tree_node<T> * nach, int k, int* res){
            if (!nach->children){
                *res += nach->size;
                return 1;
            }
            int i = 0;
            int max = 0;
            b_tree_node<T>* curr = nach->children[i];
            for (;curr;curr = curr->children[i + 1]){
                int level_i = solve3_(curr->children[i], k, res);
                max = (level_i > max) ? level_i : max;
                i += 1;
            }
            max += 1;
            if (max <= k){
                *res += i;
            }
            return max;
        }
        int solve3(int k){
            int res = 0;
            solve3_(root, k, &res);
            return res;
        }
        int solve5_(b_tree_node<T> * nach, int level){
            if (level == 0)
                return nach->size;
            if (!nach->children){
                return 0;
            }
            int i = 0;
            int cnt = 0;
            b_tree_node<T>* curr = nach->children[i];
            for (;curr;curr = curr->children[i + 1]){
                cnt = solve5_(curr->children[i], level - 1);
                i += 1;
            }
            return cnt;
        }
        int solve5(int k){
            int level = k + 1;
            return solve5_(root, level);
        }
        /*int solve6_(b_tree_node<T> * nach, int length, int* res){
            if (length == 0){
                *res += nach->size;
                return 1;
            }
            if (!nach->children){
                return 0;
            }
            int i = 0;
            int cnt = 0;
            b_tree_node<T>* curr = nach->children[i];
            for (;curr;curr = curr->children[i + 1]){
                cnt += solve6_(curr->children[i], length - 1);
                i += 1;
            }
            if (cnt > 0){
                *res += i;
                return 1;
            }
            return 0;
        }
        int solve6(int k){
            int length = k;
            return solve6_(root, length);
        }*/
    private:
        void erase_links (){
            m = 0;
            root = nullptr;
        }
        static void delete_subtree (b_tree_node<T> * curr){
            if (curr == nullptr)
                return;
            for (int i = 0; i <= curr->size; i++)
                delete_subtree (curr->children[i]);
            delete curr;
        }
        static void print_subtree (b_tree_node<T> * curr,
        int level, int r, FILE * fp = stdout){
            if (curr == nullptr || level > r)
                return;
            curr->print (level, fp);
            for (int i = 0; i <= curr->size; i++){
                if (curr->children[i] && level + 1 <= r){
                    for (int j = 0; j < level; j++)
                    fprintf (fp, " ");
                    fprintf (fp, "children[%2d]\n", i);
                    print_subtree (curr->children[i], level + 1, r, fp);
                }
            }
        }
        // Add element x to tree
        io_status add_value (T& x){
            if (root == nullptr){
                root = new b_tree_node<T>();
                if (root == nullptr)
                    return io_status::memory;
                if (root->init(m) != io_status::success){
                    delete root;
                    return io_status::memory;
                }
                root->values[0] = static_cast<T&&>(x);
                root->size = 1;
                return io_status::success;
            }
            b_tree_node<T> *curr = root, *down = nullptr;
            io_status r = add_value_subtree (curr, down, x, m);
            if (r == io_status::memory)
                return io_status::memory;
            if (r == io_status::success)
                return io_status::success;
            // иначе r == io_status::create и был создан новый узел
            // который возвращается в ’down’
            // Создаем новый корень с одним значением ’x’
            // и двумя потомками ’curr’ and ’down’
            b_tree_node<T>* p = new b_tree_node<T>();
            if (p == nullptr)
                return io_status::memory;
            if (p->init (m) != io_status::success){
                delete p;
                return io_status::memory;
            }
            p->values[0] = static_cast<T&&>(x);
            p->children[0] = curr;
            p->children[1] = down;
            p->size = 1;
            root = p;
            return io_status::success;
        }
        // Insert value ’x’ with children ’down’ at subtree ’curr’
        static io_status add_value_subtree
        (b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m){
            int index = curr->bin_search (x);
            b_tree_node<T>* p = curr->children[index];
            if (p != nullptr){ // Есть потомок
                io_status r = add_value_subtree (p, down, x, m);
                if (r == io_status::memory)
                return io_status::memory;
                if (r == io_status::success)
                return io_status::success;
            // иначе r == io_status::create
            // и был создан новый узел,
            // который возвращается в ’down’
            }
            else
                down = nullptr;
            if (curr->size < 2 * m){ // Есть свободное место в текущем узле
                curr->add_value (x, down, index);
                return io_status::success;
            }
            else{ // Создаем новый узел
                b_tree_node<T>* p = new b_tree_node<T>();
                if (p == nullptr)
                    return io_status::memory;
                if (p->init (m) != io_status::success){
                    delete p;
                    return io_status::memory;
                }
                if (index == m){ // ’x’ ровно посередине.
                // Перемещаем вторую половину в новый узел
                    for (int i = 1; i <= m; i++){
                        p->values[i - 1]
                        = static_cast<T&&>(curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                    }
                    p->children[0] = down; // меньше всех
                }
                if (index < m){ // ’x’ в первой половине.
                // Перемещаем вторую половину в новый узел
                for (int i = 0; i < m; i++){
                    p->values[i]
                    = static_cast<T&&>(curr->values[i + m]);
                    p->children[i] = curr->children[i + m];
                    curr->children[i + m] = nullptr;
                }
                p->children[m] = curr->children[2 * m];
                curr->children[2 * m] = nullptr;
                // сдвигаем элементы вправо
                // и вставляем ’x’ в позицию ’index’
                for (int i = m; i > index; i--){
                    curr->values[i]
                    = static_cast<T&&> (curr->values[i - 1]);
                    curr->children[i + 1] = curr->children[i];
                }
                curr->children[index + 1] = down;
                curr->values[index] = static_cast<T&&>(x);
                x = static_cast<T&&> (curr->values[m]);
                // новый ’x’ - максимальный
                }
                if (index > m){ // ’x’ во второй половине.
                // Перемещаем вторую половину до ’index’
                // в новый узел
                    p->children[0] = curr->children[m + 1];
                    curr->children[m + 1] = nullptr;
                    for (int i = 1 ; i < index - m; i++){
                        p->values[i - 1]
                        = static_cast<T&&> (curr->values[i + m]);
                        p->children[i] = curr->children[i + m + 1];
                        curr->children[i + m + 1] = nullptr;
                    }
                    // Вставляем ’x’ в нужную позицию
                    p->values[index - m - 1] = static_cast<T&&> (x);
                    p->children[index - m] = down;
                    // Перемещаем остаток второй половины в новый узел
                    for (int i = index - m + 1; i <= m; i++){
                        p->values[i - 1]
                        = static_cast<T&&> (curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                    }
                    x = static_cast<T&&> (curr->values[m]);
                // новый ’x’ - максимальный
                }
                down = p;
                p->size = m;
                curr->size = m;
                return io_status::create;
            // создан новый узел, он возвращается в ’down’
            }
            return io_status::success;
        }
};
