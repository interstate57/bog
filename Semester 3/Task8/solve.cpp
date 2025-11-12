#include "solve.h"

void print_arr(tree_node** arr, int size);

void tree::fix_down(tree_node* nach){
    if (!nach->right && !nach->left) return;
    if (!nach->right && *nach < *nach->left){
        swap(nach, nach->left);
        fix_down(nach->left);
    }
    else if (!nach->left && *nach < *nach->right){
        swap(nach, nach->right);
        fix_down(nach->right);
    }
    else if (nach->right && nach->left){
        tree_node* max = max3(nach, nach->right, nach->left);
        if (max == nach->left){
            swap(nach, nach->left);
            fix_down(nach->left);
        }
        else if (max == nach->right){
            swap(nach, nach->right);
            fix_down(nach->right);
        }
    }
}

void tree::heapify(tree_node* nach){
    if (nach->left)
        heapify(nach->left);
    if (nach->right){
        heapify(nach->right);
    }
    tree_node* max = max3(nach, nach->right, nach->left);
    if (max == nach->left){
        swap(nach, nach->left);
        fix_down(nach->left);
    }
    else if (max == nach->right){
        swap(nach, nach->right);
        fix_down(nach->right);
    }
}

tree_node* max3(tree_node* a, tree_node* b, tree_node* c){
    return max2(max2(a, b), c);
}

tree_node* max2(tree_node* a, tree_node* b){
    return ((*a > *b) ? a : b);
}

void tree::a1(){
    heapify(root);
}

/*tree_node* tree::find_a(tree_node* nach, tree_node** parent){
    if (!nach) return 0;
    if (!nach->left && nach->right)
        return nach;
    tree_node* p = 0;
    tree_node* res_left = 0;
    tree_node* res_right = 0;
    if (nach->left){
        res_left = find_a(nach->left, &p);
    }
    if (nach->right){
        res_right = find_a(nach->right, &p);
    }
    if (res_left) {
        if (res_left == nach->left) {
            *parent = nach;
        }
        else {
            *parent = p;
        }
        return res_left;
    }
    if (res_right) {
        if (res_right == nach->right) {
            *parent = nach;
        }
        else {
            *parent = p;
        }
        return res_right;
    }
    return 0;
}*/

tree_node* tree::find_left_leaf(tree_node* nach, tree_node** parent){
    if (!nach) return 0;
    tree_node* p = 0;
    tree_node* res = 0;
    if (!nach->left && !nach->right){
        return nach;
    }
    if (nach->left){
        res = find_left_leaf(nach->left, &p);
    }
    if (res){
        if (res == nach->left){
            *parent = nach;
        }
        else{
            *parent = p;
        }
        return res;
    }
    return 0;
}

/*void tree::perebor_a(tree_node* nach){
    tree_node* parent_a = nullptr;
    tree_node* parent_leaf = nullptr;
    tree_node* a = find_a(nach, &parent_a);
    if (!a) return;
    tree_node* leaf = find_left_leaf(a->right, &parent_leaf);
    printf("1\n");
    if (leaf == nullptr){
        perebor_a(nach);
        return;
    }
    parent_leaf->left = nullptr;
    if (parent_a){
        if (a == parent_a->right){
            parent_a->right = leaf; 
        }
        else{
            parent_a->left = leaf; 
        }
    }
    leaf->right = a->right;
    leaf->left = a;
    a->right = nullptr;
    perebor_a(nach);
    return;
}*/

void tree::swap_elements(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf){
    if (leaf == nullptr){
        return;
    }
    std::cout << "Called swap elements: " << std::endl;
    a->print();
    leaf->print();
    std::cout << std::endl;
    
    parent_leaf->left = nullptr;
    if (parent_a){
        if (a == parent_a->right){
            parent_a->right = leaf; 
        }
        else{
            parent_a->left = leaf; 
        }
    }
    leaf->right = a->right;
    leaf->left = a;
    a->right = nullptr;
    return;
}

tree_node* tree::leftmost(tree_node* nach, tree_node** arr, int* size){
    if (!nach) return 0;
    tree_node* down = nach;
    tree_node* curr = nach;
    while (curr->left){
        arr[*size] = curr;
        *size += 1;
        down = curr->left;
        curr = curr->left;
    }
    return down;
}

tree_node* tree::get_next(tree_node* nach, tree_node** arr, int* size){
    //std::cout << "Called get_next for " << nach;
    //nach->print();
    tree_node* curr = nach;
    int cnt = *size;
    //printf("cnt = %d\n", cnt);
    if (curr->right){
        //printf("1\n");
        arr[cnt] = curr;
        cnt += 1;
        *size = cnt;
        // ---- нахуй ---
        //tree_node* res = leftmost(curr->right, arr, size);
        /*std::cout << "Leftmost: " << res;
        fflush(stdout);
        res->print();
        print_arr(arr, *size);
        return res;*/
        return leftmost(curr->right, arr, size);
    }
    while ((cnt > 0) && ((curr == arr[cnt - 1]->right) || (!arr[cnt - 1]->right))){
        //printf("1\n");
        curr = arr[cnt - 1];
        cnt -= 1;
    }
    *size = cnt;
    if (curr == root)
        return 0;
    *size -= 1;
    return arr[*size];
}

void tree::a3(){
    int len = get_height();
    tree_node** arr = new tree_node* [len];
    int cnt = 0;
    tree_node* curr = leftmost(root, arr, &cnt);
    tree_node* parent_leaf = 0;
    tree_node* leaf = 0;
    while (curr){
        /*printf("\n");
        curr->print();
        printf("\n");*/
        //print_arr(arr, cnt);
        if (!curr->left && curr->right){
            leaf = find_left_leaf(curr->right, &parent_leaf);
            leaf->print();
            swap_elements(curr, arr[cnt - 1], leaf, parent_leaf);
            print_subtree(root, 0, 4);
            arr[cnt] = curr;
            curr = leaf->right;
            cnt += 1;
        }
        else{

            //curr->left->print();
            curr = get_next(curr, arr, &cnt);
        }

    }
    delete [] arr;
}

void print_arr(tree_node** arr, int size){
    tree_node* curr = arr[0];
    int i = 0;
    printf("---------------\n");
    while (i < size){
        i += 1;
        curr->print();
        curr = arr[i];
    }
    printf("---------------\n");
}


