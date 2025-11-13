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


void tree::swap_elements(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf){
    if (leaf == nullptr){
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
    if (a->right == leaf){
        leaf->right = 0;
    }
    else{
        leaf->right = a->right;
    }
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
    tree_node* curr = nach;
    int cnt = *size;
    if (curr->right){
        arr[cnt] = curr;
        cnt += 1;
        *size = cnt;
        return leftmost(curr->right, arr, size);
    }
    while ((cnt > 0) && ((curr == arr[cnt - 1]->right) || (!arr[cnt - 1]->right))){
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
        if (!curr->left && curr->right){
            parent_leaf = curr;
            leaf = find_left_leaf(curr->right, &parent_leaf);
            if (!leaf){
                arr[cnt] = curr;
                curr = curr->right;
                cnt += 1;
                continue;
            }
            swap_elements(curr, arr[cnt - 1], leaf, parent_leaf);
            if (leaf && leaf->right){
                arr[cnt] = leaf;
                curr = leaf->right;
                cnt += 1;
            }
            else{
                curr = get_next(leaf, arr, &cnt);
            }
        }
        else{

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



void tree::find_sk_subtrees(tree_node* curr, char* s, int k, int* height, bool* is_s_subtree){
    if (!curr) {
        *height = 0;
        *is_s_subtree = true;
        return;
    }
    
    bool yes_left = true, yes_right = true;
    int hleft = 0, hright = 0;
    if (curr->left)
        find_sk_subtrees(curr->left, s, k, &hleft, &yes_left);
    if (curr->right)
        find_sk_subtrees(curr->right, s, k, &hright, &yes_right);
    
    *height = std::max(hleft, hright) + 1;
    *is_s_subtree = yes_left && yes_right && (strstr(curr->get_name(), s));
    // а также && является ли s подстрокой curr
    
    if (yes_left && hleft >= k && !yes_right){
        delete_subtree(curr->left);
        curr->left = 0;
        *is_s_subtree = false;
        return;
    }
    else if (yes_right && hright >= k && !yes_left){
        delete_subtree(curr->right);
        curr->right = 0;
        *is_s_subtree = false;
        return;
    }
    else if (yes_left && hleft >= k && yes_right && hright >= k){
        delete_subtree(curr->left);
        curr->left = 0;
        delete_subtree(curr->right);
        curr->right = 0;
        *is_s_subtree = false;
        return;
    }
    return;
}

void tree::a5(char* s, int k){
    int hight = 0;
    bool is_s_subtree = true;
    find_sk_subtrees(root, s, k, &hight, &is_s_subtree);
    if (is_s_subtree){
        delete_subtree(root);
        root = 0;
    }
    return;
}
