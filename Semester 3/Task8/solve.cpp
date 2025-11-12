#include "solve.h"

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

tree_node* tree::find_a(tree_node* nach, tree_node** parent){
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
}

tree_node* tree::find_left_leaf(tree_node* nach, tree_node** parent){
    if (!nach) return 0;
    tree_node* p = 0;
    tree_node* res = 0;
    if (!nach->left && !nach->right){
        return nach;
    }
    if (nach->left && !nach->right){
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

void tree::perebor_a(tree_node* nach){
    tree_node* parent_a = nullptr;
    tree_node* parent_leaf = nullptr;
    tree_node* a = find_a(nach, &parent_a);
    if (!a) return;
    tree_node* leaf = find_left_leaf(a->right, &parent_leaf);
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
}

void tree::a3(){
    perebor_a(root);
}