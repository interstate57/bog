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


tree_node* tree::find_left_leaf(tree_node* nach, tree_node** parent, int cnt){
    if (!nach) return 0;
    tree_node* p = 0;
    tree_node* res = 0;
    if (!nach->left && !nach->right){
        if (cnt == 0) 
            return 0;
        return nach;
    }
    if (nach->left){
        res = find_left_leaf(nach->left, &p, 1);
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


void tree::swap_elements_left(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf){
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

tree_node* tree::get_next_left(tree_node* nach, tree_node** arr, int* size){
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
            int cnt1 = 0;
            leaf = find_left_leaf(curr->right, &parent_leaf, cnt1);
            if (!leaf){
                arr[cnt] = curr;
                curr = curr->right;
                cnt += 1;
                continue;
            }
            swap_elements_left(curr, arr[cnt - 1], leaf, parent_leaf);
            if (leaf && leaf->right){
                arr[cnt] = leaf;
                curr = leaf->right;
                cnt += 1;
            }
            else{
                curr = get_next_left(leaf, arr, &cnt);
            }
        }
        else{

            curr = get_next_left(curr, arr, &cnt);
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

void tree::a5(const student& student){
    int hight = 0;
    char* s = student.get_name();
    int k = student.get_value();
    bool is_s_subtree = true;
    find_sk_subtrees(root, s, k, &hight, &is_s_subtree);
    if (is_s_subtree){
        delete_subtree(root);
        root = 0;
    }
    return;
}


void tree::find_sk_branches(tree_node* curr, char* s, int k, int* height, bool* is_s_subtree){
    if (!curr) {
        *height = 0;
        *is_s_subtree = true;
        return;
    }
    
    bool yes_left = true, yes_right = true;
    int hleft = 0, hright = 0;

    if (curr->left)
        find_sk_branches(curr->left, s, k, &hleft, &yes_left);
    if (curr->right)
        find_sk_branches(curr->right, s, k, &hright, &yes_right);
    
    bool curr_has_s = strstr(curr->get_name(), s);
    //printf("For student = ");
    //curr->print();
    //printf("curr_has_s = %d\n", curr_has_s);
    *height = 0;
    if (yes_left){
        *height = std::max(hleft, *height);
        //printf("height = %d", *height);
    }
    if (yes_right){
        *height = std::max(hright, *height);
        //printf("height = %d", *height);
    }
    if (!curr_has_s){
        *height = 0;
    } 
    else{
        *height += 1;
    }
    //printf("height = %d, hright = %d, hleft = %d\n", *height, hright, hleft);
    //printf("\n");
    
    *is_s_subtree = (yes_left || yes_right) && curr_has_s;
    if (yes_left && hleft >= k && !curr_has_s){
        delete_subtree(curr->left);
        curr->left = 0;
        *is_s_subtree = false;
        return;
    }
    else if (yes_right && hright >= k && !curr_has_s){
        delete_subtree(curr->right);
        curr->right = 0;
        *is_s_subtree = false;
        return;
    }
    return;
}

void tree::a6(const student& student){
    int hight = 0;
    char* s = student.get_name();
    int k = student.get_value();
    bool is_s_subtree = true;
    find_sk_branches(root, s, k, &hight, &is_s_subtree);
    if (is_s_subtree){
        delete_subtree(root);
        root = 0;
    }
    return;
}

tree_node* tree::find_right_leaf(tree_node* nach, tree_node** parent, int cnt){
    if (!nach) return 0;
    tree_node* p = 0;
    tree_node* res = 0;
    if (!nach->right && !nach->left){
        if (cnt == 0)
            return 0;
        return nach;
    }
    if (nach->right){
        res = find_right_leaf(nach->right, &p, 1);
    }
    if (res){
        if (res == nach->right){
            *parent = nach;
        }
        else{
            *parent = p;
        }
        return res;
    }
    return 0;
}


void tree::swap_elements_right(tree_node* a, tree_node* parent_a, tree_node* leaf, tree_node* parent_leaf){
    if (leaf == nullptr){
        return;
    }
    parent_leaf->right = nullptr;
    if (parent_a){
        if (a == parent_a->left){
            parent_a->left = leaf; 
        }
        else{
            parent_a->right = leaf; 
        }
    }
    if (a->left == leaf){
        leaf->left = 0;
    }
    else{
        leaf->left = a->left;
    }
    leaf->right = a;
    a->left = nullptr;
    return;
}

tree_node* tree::rightmost(tree_node* nach, tree_node** arr, int* size){
    if (!nach) return 0;
    tree_node* down = nach;
    tree_node* curr = nach;
    while (curr->right){
        arr[*size] = curr;
        *size += 1;
        down = curr->right;
        curr = curr->right;
    }
    return down;
}

tree_node* tree::get_next_right(tree_node* nach, tree_node** arr, int* size){
    tree_node* curr = nach;
    int cnt = *size;
    if (curr->left){
        arr[cnt] = curr;
        cnt += 1;
        *size = cnt;
        return rightmost(curr->left, arr, size);
    }
    while ((cnt > 0) && ((curr == arr[cnt - 1]->left) || (!arr[cnt - 1]->left))){
        curr = arr[cnt - 1];
        cnt -= 1;
    }
    *size = cnt;
    if (curr == root)
        return 0;
    *size -= 1;
    return arr[*size];
}

void tree::a4(){
    int len = get_height();
    tree_node** arr = new tree_node* [len];
    int cnt = 0;
    tree_node* curr = rightmost(root, arr, &cnt);
    tree_node* parent_leaf = 0;
    tree_node* leaf = 0;
    while (curr){
        if (!curr->right && curr->left){
            parent_leaf = curr;
            int cnt = 0;
            leaf = find_right_leaf(curr->left, &parent_leaf, cnt);
            if (!leaf){
                arr[cnt] = curr;
                curr = curr->left;
                cnt += 1;
                continue;
            }
            swap_elements_right(curr, arr[cnt - 1], leaf, parent_leaf);
            if (leaf && leaf->left){
                arr[cnt] = leaf;
                curr = leaf->left;
                cnt += 1;
            }
            else{
                curr = get_next_right(leaf, arr, &cnt);
            }
        }
        else{

            curr = get_next_right(curr, arr, &cnt);
        }

    }
    delete [] arr;
}