#include "tree.h"

int tree::solve1(tree_node* nach, int k){
    if (!nach) return 0;
    int cnt = 0;
    int res = 0;
    tree_node* curr = nach->down;
    for (;curr; curr = curr->level){
        cnt += 1;
        res += solve1(curr->down, k);
    }
    if (cnt == k)
        res += 1;
    return res;
}

int tree::a1(int k){
    return solve1(root, k);
}

int tree::solve2(tree_node* nach, int k, int* size){
    if (!nach) return 0;
    int cnt = 0;
    *size = 0;
    tree_node* curr = nach->down;
    for (;curr; curr = curr->level){
        int tsize = 0;
        cnt += solve2(curr->down, k, &tsize);
        *size += tsize;
    }
    if (*size <= k)
        cnt += 1;
    return cnt;
}

int tree::a2(int k){
    int size = 0;
    return solve2(root, k, &size);
}

int tree::solve3(tree_node* nach, int k, int* height){
    if (!nach) return 0;
    int max = 0;
    int cnt = 0;
    tree_node* curr = nach->down;
    for (;curr; curr = curr->level){
        int theight = 0;
        cnt += solve3(curr->down, k, &theight);
        if (max < theight){
            max = theight;
        }
    }
    *height = max + 1;
    if (*height <= k)
        cnt += 1;
    return cnt;
}

int tree::a3(int k){
    int height = 0;
    return solve3(root, k, &height);
}

/*int tree::solve4(tree_node* nach, int k, int curr_level){
    tree_node* curr = nach->down;
    
}*/

int tree::solve5(tree_node* nach, int k, int curr_level){
    if (!nach) return 0;
    int cnt = 0;
    tree_node* curr = nach->down;
    for (;curr; curr = curr->level){
        if (k == curr_level + 1){
            cnt += 1;
            continue;
        }
        cnt += solve5(curr->down, k, curr_level + 1);
    }
    return cnt;
}

int tree::a5(int k){
    return solve5(root, k, 0);
}

int tree::solve6(tree_node* nach, int k, int curr_level){
    if (!nach) return 0;
    int cnt = 0;
    tree_node* curr = nach->down;
    if (k <= curr_level){
        cnt += 1;
    }
    for (;curr; curr = curr->level){
        cnt += solve5(curr->down, k, curr_level + 1);
    }
    return cnt;
}

int tree::a6(int k){
    return solve6(root, k, 0);
}

int tree::solve7(tree_node* nach, int k){
    if (!nach) return 0;
    int cnt = 0;
    tree_node* predcurr = nach;
    tree_node* curr = nach->down;
    for (;curr;curr = curr->level){
        if (curr->get_value() <= k){
            cnt += 1;
            if (curr == nach->down){
                nach->down = curr->level;
            }
            else{
                predcurr->level = curr->level;
            }
            delete_subtree_dop(curr, k, &cnt);
            curr = 0;
        }
    }
    return cnt;
}

void tree::delete_subtree_dop(tree_node* curr, int k, int* cnt){
    if (curr == nullptr)
            return;
        tree_node * p, * next;
        for (p = curr->down; p; p = next){
            next = p->level;
            if (p->get_value() <= k)
                *cnt += 1;
            delete_subtree (p);
        }
        delete curr;
}

int tree::a7(int k){
    return solve7(root, k);
}