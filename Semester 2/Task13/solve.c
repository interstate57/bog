#include "solve.h"
int solve1(node* head){
    int max = 0;
    char* curr_max = (char *)"";
    node* curr = head;
    while (curr){
        if(strcmp(curr_max, curr->string) == 0){
            max += 1;
        }
        else if (strcmp(curr_max, curr->string) < 0){
            curr_max = curr->string;
            max = 1;
        }
        curr = curr->next;
    }
    return max;
}

int solve2(node* head){
    int cnt = 0;
    node* prev = head;
    node* curr;
    if (!head) return 0;
    curr = head->next;
    while (curr){
        if (strcmp(curr->string, prev->string) > 0) cnt += 1;
        prev = curr;
        curr = prev->next;
    }
    return cnt;
}

int solve3(node* head){
    int cnt = 0;
    node* prev = head;
    node* curr;
    node* future;
    if (!head) return 0;
    curr = head->next;
    if (!curr) return 0;
    future = curr->next;
    if (!future) return 0;
    while (future){
        if (strcmp(curr->string, prev->string) >= 0 && strcmp(curr->string, future->string) >= 0) cnt += 1;
        prev = curr;
        curr = prev->next;
        future = curr->next;
    }
    return cnt;
}

int solve4(node* head){
    int cnt = 0, nach = 0, max = 0;
    node* prev = head;
    node* curr;
    node* future;
    if (!head) return 0;
    curr = head->next;
    if (!curr) return 0;
    future = curr->next;
    if (!future) return 0;
    while (future){
        if (strcmp(curr->string, prev->string) >= 0 && strcmp(curr->string, future->string) >= 0 && !nach){
            nach = 1;
        }
        else if(strcmp(curr->string, prev->string) >= 0 && strcmp(curr->string, future->string) >= 0 && nach){
            max = max > cnt ? max : cnt;
            cnt = 0;
        }
        else if (nach) cnt += 1;
        prev = curr;
        curr = prev->next;
        future = curr->next;
    }
    return max;
}

int solve5(node* head){
    int cnt = 1, max = 0;
    node* prev = head;
    node* curr;
    if (!head) return 0;
    curr = head->next;
    while (curr){
        if (strcmp(curr->string, prev->string) > 0) cnt += 1;
        else{
            max = max > cnt ? max : cnt;
            cnt = 1;
        }
        prev = curr;
        curr = prev->next;
    }
    max = max > cnt ? max : cnt;
    return max;
}

int solve6(node* head){
    int cnt = 0, nach = 0;
    node* prev = head;
    node* curr;
    if (!head) return 0;
    curr = head->next;
    while (curr){
        if (strcmp(curr->string, prev->string) == 0 && nach == 0){
            nach = 1;
            cnt += 1;
        }
        else if (strcmp(curr->string, prev->string) != 0){
            nach = 0;
        }
        prev = curr;
        curr = prev->next;
    }
    return cnt;
}

int solve7(node* head){
    int cnt = 0, nach = 0, max = 0;
    node* prev = head;
    node* curr;
    if (!head) return 0;
    curr = head->next;
    while (curr){
        if (strcmp(curr->string, prev->string) == 0 && nach == 0){
            nach = 1;
            max = max > cnt ? max : cnt;
            cnt = 0;
        }
        else if (strcmp(curr->string, prev->string) != 0 && nach == 1){
            nach = 0;
        }
        else if (strcmp(curr->string, prev->string) != 0 && nach == 0){
            cnt += 1;
        }
        prev = curr;
        curr = prev->next;
    }
    return max;
}

node* solve8(node* head){
    node* prev = head;
    node* curr;
    if (!head) return 0;
    curr = head->next;
    while(prev && curr){
        if (strcmp(prev->string, curr->string) >= 0){
            head = curr;
            free(prev->string);
            free(prev);
            prev = curr;
            curr = curr->next;
        }
        else{
            break;
        }
    }
    while (curr && curr->next){
        if (strcmp(curr->string, curr->next->string) >= 0){
            prev->next = curr->next;
            free(curr->string);
            free(curr);
            curr = prev->next;
        }
        else{
            prev = curr;
            curr = prev->next;
        }
    }
    return head;
}

node* solve9(node* head){
    node* prev = head;
    node* curr;
    node* future;
    if (!head) return 0;
    curr = head->next;
    if (!curr) return 0;
    future = curr->next;
    while (future){
        if (strcmp(curr->string, future->string) >= 0 && strcmp(curr->string, prev->string) >= 0){
            prev->next = future;
            free(curr->string);
            free(curr);
        }
        else{
            prev = curr;
        }
        curr = prev->next;
        future = curr->next;
    }
    return head;
}

node* solve10(node* head){
    node* prev = head;
    node* curr;
    node* nach = head;
    int fl = 0;
    if (!head) return 0;
    curr = head->next;
    while (curr){
        if (strcmp(prev->string, curr->string) >= 0){
            free(prev->string);
            free(prev);
            prev = curr;
            head = prev;
            curr = prev->next;
            fl = 1;
        }
        else if (!(strcmp(prev->string, curr->string) >= 0) && fl == 1){
            free(prev->string);
            free(prev);
            head = curr;
            prev = curr;
            curr = prev->next;
        }
        else if(fl == 0){
            break;
        }
    }
    return head;
}