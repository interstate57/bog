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
    tree_node* max = 0;
    if (nach->left)
        heapify(nach->left);
    if (nach->right){
        heapify(nach->right);
    }
    if (nach->left && nach->right){
        max = max3(nach, nach->right, nach->left);
    }
    else if (!nach->left && nach->right){
        max = max2(nach, nach->right);
    }
    else if (!nach->right && nach->left){
        max = max2(nach, nach->left);
    }
    else{
        max = nach;
    }
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


void tree::swap_elements_left(tree_node** curr, tree_node* a, tree_node* b, tree_node* c, tree_node* parent_c){
    if (c == 0)
        return;
    if (parent_c  == 0){
        return;
    }
    else{
        parent_c->left = 0;
    }
    *curr = c;
    c->left = a;
    c->right = b;
    a->left = 0;
    a->right = 0;
    return;
}

void tree::a3_(tree_node** nach){
    if (*nach == 0)
        return;
    tree_node* dop  = *nach;
    tree_node* a = 0;
    tree_node* b = 0;
    tree_node* c = 0;
    tree_node* parent_c = 0;
    if (!dop->left && dop->right){
        a = dop;
        b = dop->right;
        c = find_left_leaf(b, &parent_c);
        swap_elements_left(nach, a, b, c, parent_c);
    }
    if (*nach != 0){
        a3_(&((*nach)->left));
        a3_(&((*nach)->right));
    }
}

void tree::a3(){
    a3_(&root);
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
    
    bool yes_left = !curr->left ? false : true, yes_right = !curr->right ? false : true;
    int hleft = 0, hright = 0;

    if (curr->left)
        find_sk_subtrees(curr->left, s, k, &hleft, &yes_left);
    if (curr->right)
        find_sk_subtrees(curr->right, s, k, &hright, &yes_right);
    bool s_in_curr = strstr(curr->get_name(), s);
    *height = std::max(hleft, hright) + 1;
    *is_s_subtree = yes_left && yes_right && s_in_curr;
    if (curr->get_value() == 6197215){
        curr->print();
        printf("hleft = %d, hright = %d, yes_left = %d, yes_right = %d\n", hleft, hright, yes_left, yes_right);
    }
    /*if (!*is_s_subtree)
        *height = 0;*/
    if (!s_in_curr){
        if (yes_left && hleft >= k){
            delete_subtree(curr->left);
            curr->left = 0;
        }
        if (yes_right && hright >= k){
            delete_subtree(curr->right);
            curr->right = 0;
        }
        *is_s_subtree = false;
        return;
    }
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


