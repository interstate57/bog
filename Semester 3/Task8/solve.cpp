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