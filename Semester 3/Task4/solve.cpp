#include "solve.h"

int solve1(list_node* head){
    int cnt = 0;
    student* max = head;
    list_node* curr;
    for (curr = head; curr; curr = curr->get_next()){
        if (*max < *curr){
            max = curr;
            cnt = 1;
        }
        else if (*max == *curr){
            cnt++;
        }
    }
    return cnt;
}

int solve2(list_node* head){
    int cnt = 0;
    list_node* curr;
    if (head == nullptr) return 0;
    list_node* pred = head;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*curr > *pred) cnt++;
        pred = curr;
    }
    return cnt;
}

int solve3(list_node* head){
    int cnt = 0;
    list_node* curr;
    if (head == nullptr) return 0;
    list_node* predpred = head;
    if (predpred->get_next() == nullptr) return 1;
    list_node* pred = predpred->get_next();
    if (pred->get_next() == nullptr){
        if (*pred == *predpred) return 2;
        else{
            return 1;
        }
    }
    if (*predpred >= *pred) cnt = 1;
    else cnt = 0;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*curr <= *pred && *pred >= *predpred) cnt++;
        predpred = pred;
        pred = curr;
    }
    if (*pred >= *predpred) cnt++;
    return cnt;
}

int solve4(list_node* head){
    int res = -1;
    list_node* curr;
    if (head == nullptr) return 4;
    list_node* pred = head;
    if (pred->get_next() == nullptr) return 4;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*pred < *curr){
            if (res == 2) return 0;
            if (res == -1) res = 1;
            else{
                if (res == 3) res = 1;
            }
        }
        else if (*pred > *curr){
            if (res == 1) return 0;
            if (res == -1) res = 2;
            else{
                if (res == 3) res = 2;
            }
        }
        else{
            if (res == -1) res = 3;
        }
        pred = curr;
    }
    return res;
}

int solve5(list_node* head){
    int cnt = 0;
    int max = 0;
    list_node* curr;
    if (head == nullptr) return 0;
    list_node* pred = head;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*curr > *pred){
            if (cnt == 0) cnt = 2;
            else cnt++;
        }
        else{
            max = (max < cnt) ? cnt : max;
            cnt = 0;
        }
        pred = curr;
    }
    max = (max < cnt) ? cnt : max;
    return max;
}

int solve6(list_node* head){
    int cnt = 0;
    int fl = 0;
    list_node* curr;
    if (head == nullptr) return 0;
    list_node* pred = head;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*curr == *pred){
            if (fl == 0){
                fl = 1;
                cnt += 1;
            }
        }
        else{
            fl = 0;
        }
        pred = curr;
    }
    return cnt;
}

int solve7(list_node* head){
    int cnt = 0;
    int fl = 0;
    int max = 0;
    list_node* curr;
    if (head == nullptr) return 0;
    list_node* pred = head;
    for (curr = pred->get_next(); curr; curr = curr->get_next()){
        if (*curr == *pred){
            fl = 1;
            max = (max < cnt) ? cnt : max;
            cnt = 0;
        }
        else{
            if (fl == 0) continue;
            else{
                cnt++;
            }
        }
        pred = curr;
    }
    return max - 1;
}