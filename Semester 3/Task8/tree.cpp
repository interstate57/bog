#include "tree.h"

int tree::solve1(tree_node* nach) const{
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

int tree::solve2(tree_node* nach) const{
    if (!nach) return 0;
    return max(1 + solve2(nach->left), 1 + solve2(nach->right));
}

int max3(int a, int b, int c){
    return max(a, max(b, c));
}


void tree::solve3(tree_node* nach, int ur, int* b) const{
    b[ur] += 1;
    if (nach->left)
        solve3(nach->left, ur + 1, b);
    if (nach->right)
        solve3(nach->right, ur + 1, b);
    return;
}

int tree::solve4(tree_node* nach, int* inner_max) const{
    if (!nach) return 0;
    int left = 0, right = 0;
    int hleft = solve4(nach->left, &left);
    int hright = solve4(nach->right, &right);
    *inner_max = max3(std::abs(hleft - hright), left, right);
    return max(hleft, hright) + 1;
}

int tree::solve5(tree_node* nach) const{
    if (!nach) return 0;
    int res = solve5(nach->left) + solve5(nach->right);
    if ((!nach->left && nach->right) || (!nach->right && nach->left))
        res = res + 1;
    return res;
}

int tree::solve6(tree_node* nach) const{
    if (!nach) return 0;
    int res = solve6(nach->left) + solve6(nach->right);
    if (nach->left && nach->right)
        res = res + 1;
    return res;
}

int tree::solve7(tree_node* nach) const{
    if (!nach) return 0;
    int res = solve7(nach->left) + solve7(nach->right);
    res = res + 1;
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
int tree::cnt_min(tree_node* nach, int min){
    if (!nach) return 0;
    int res = nach->get_value() == min ? 1 : 0;
    res += cnt_min(nach->left, min) + cnt_min(nach->right, min);
    return res;
}


int tree::udalenie(tree_node* nach, int min, tree_node* parent){
    if (!nach)
        return 0;

    int res = cnt_min(nach, min);
    if (nach->get_value() == min) {
        delete_subtree(nach);
        if (parent && parent->left == nach) {
            parent->left = nullptr;
        }
        else if (parent && parent->right == nach) {
            parent->right = nullptr;
        }
        return res;
    }
    udalenie(nach->left, min, nach);
    udalenie(nach->right, min, nach);
    return res;
}

int tree::get_count_leaf() const{
    return solve1(root);
}

int tree::get_height() const{
    return solve2(root);
}

int tree::get_width() const{
    int glub = get_height();
    int* b = new int [glub];
    for (int i = 0; i < glub; i++){
        b[i] = 0;
    }
    solve3(root, 0, b);
    int max = b[0];
    for (int i = 1; i < glub; i++){
        if (max < b[i]){
            max = b[i];
        }
    }
    delete [] b;
    return max;
}

int tree::get_balance() const{
    int inner_max = 0;
    solve4(root, &inner_max);
    return inner_max;
}

int tree::get_count_1() const{
    return solve5(root);
}

int tree::get_count_2() const{
    return solve6(root);
}

int tree::get_count_total() const{
    return solve7(root);
}