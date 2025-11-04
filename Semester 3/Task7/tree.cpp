#include "tree.h"

int tree::solve1(tree_node* nach){
    int cnt = 0;
    tree_node* curr = nach;
    if (!curr->left && !curr->right) cnt += 1;
    if (curr->left != nullptr){
        cnt += solve1(curr->left);
    }
    if (curr->right != nullptr){
        cnt += solve1(curr->right);
    }
    return cnt;
}

int max(int a, int b){
    return a > b ? a : b;
}

int tree::solve2(tree_node* nach){
    if (!nach) return 0;
    return max(1 + solve2(nach->left), 1 + solve2(nach->right));
}

int max3(int a, int b, int c){
    return max(a, max(b, c));
}

// возвращать пару: глубина этого поддерева; максимальная разность высот в этом поддереве
int tree::solve4(tree_node* nach, int* inner_max){
    if (!nach) return 0;
    int left = 0, right = 0;
    int hleft = solve4(nach->left, &left);
    int hright = solve4(nach->right, &right);
    *inner_max = max3(std::abs(hleft - hright), left, right);
    return max(hleft, hright) + 1;
}

int tree::solve5(tree_node* nach){
    if (!nach) return 0;
    int res = solve5(nach->left) + solve5(nach->right);
    if ((!nach->left && nach->right) || (!nach->right && nach->left))
        res = res + 1;
    return res;
}

int tree::solve6(){
    int min = poisk_min(root);
    int res = udalenie(root, min);
    return res;
}

int tree::poisk_min(tree_node* nach){
    int res = nach->get_value();
    if (nach->left) {
        res = std::min(res, poisk_min(nach->left));
    }
    if (nach->right) {
        res = std::min(res, poisk_min(nach->right));
    }
    return res;
}

int tree::udalenie(tree_node* nach, int min){
    int cnt = 0;
    if (nach == nullptr)
        return 0;
    if (nach->get_value() == min){
        cnt += 1;
    }
    cnt += udalenie (nach->left, min);
    cnt += udalenie (nach->right, min);
    delete nach;
    return cnt;
}

int tree::solve1_(){
    return solve1(root);
}

int tree::solve2_(){
    return solve2(root);
}

int tree::solve4_(){
    int inner_max = 0;
    solve4(root, &inner_max);
    return inner_max;
}

int tree::solve5_(){
    return solve5(root);
}

