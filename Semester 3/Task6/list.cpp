#include "list.h"

void list::sort1(){
    list_node* new_head = nullptr;
    list_node* dop;
    list_node* predcurr;
    list_node* curr;
    list_node* next;
    if (head->get_next() == nullptr) return;
    for (;head->get_next();){
        predcurr = head;
        curr = head->get_next();
        if (*curr < *predcurr){
            predcurr->set_next(curr->get_next());
            curr->set_next(predcurr);
            head = curr;
            dop = curr;
            curr = predcurr;
            predcurr = dop;
        }
        next = curr->get_next();
        for (;next;){
            if (*next < *curr){
                curr->set_next(next->get_next());
                next->set_next(curr);
                predcurr->set_next(next);
                predcurr = next;
                next = curr->get_next();
            }
            else{
                predcurr = curr;
                curr = next;
                next = curr->get_next();
            }
        }
        predcurr->set_next(nullptr);
        if (new_head != nullptr){
            curr->set_next(new_head);
        }
        new_head = curr;
    }
    if (new_head != nullptr){
        head->set_next(new_head);
        new_head = head;
    }
    head = new_head;
}

void list::sort2(){
    list_node* new_head = nullptr;
    list_node* new_tail = nullptr;
    list_node* predmin;
    list_node* curr;
    list_node* min;
    for (;head->get_next();){
        predmin = nullptr;
        min = head;
        for (curr = head; curr->get_next();curr = curr->get_next()){
            if (*curr->get_next() < *min){
                min = curr->get_next();
                predmin = curr;
            }
        }
        if (predmin != nullptr){
            predmin->set_next(min->get_next());
        }
        else{
            head = head->get_next();
        }
        if (new_head == nullptr){
            new_head = min;
        }
        else{
            new_tail->set_next(min);
        }
        new_tail = min;
    }
    if (new_head == nullptr){
        new_head = head;
    }
    else{
        new_tail->set_next(head);
    }
    head = new_head;
}

void list::sort3(){
    list_node* new_head = head;
    list_node* curr;
    list_node* next = nullptr;
    list_node* dop = nullptr;
    list_node* new_curr;
    int fl;
    head = head->get_next();
    new_head->set_next(nullptr);
    for (curr = head; curr; curr = next){
        fl = 0;
        next = curr->get_next();
        if (*curr <= *new_head){
            curr->set_next(new_head);
            new_head = curr;
            continue;
        }
        
        for (new_curr = new_head; new_curr->get_next(); new_curr = new_curr->get_next()){
            if (*curr >= *new_curr && *curr <= *new_curr->get_next()){
                dop = new_curr->get_next();
                new_curr->set_next(curr);
                curr->set_next(dop);
                fl = 1;
                break;
            }
        }
        if (fl == 0){
            new_curr->set_next(curr);
            curr->set_next(nullptr);
        }
    }
    head = new_head;
}

int list::diff(){
    int diff = 0;
    list_node* curr;
    for (curr = head; curr->get_next(); curr = curr->get_next()){
        if (*curr->get_next() < *curr) diff += 1;
    }
    return diff;
}

int length_(list_node* head){
    int cnt = 0;
    list_node* curr;
    for (curr = head; curr; curr = curr->get_next()){
        cnt += 1;
    }
    return cnt;
}

int list::get_length(){
    return length_(head);
}

list_node* merge(list_node* a, list_node* b, list_node** res_tail){
    list_node* new_head = nullptr;
    list_node* new_tail = nullptr;
    list_node* curra = a;
    list_node* currb = b;
    while (curra && currb){
        if (*curra < *currb){
            if (new_head == nullptr){
                new_head = curra;
            }
            else{
                new_tail->set_next(curra);
            }
            new_tail = curra;
            curra = curra->get_next();
        }
        else{
            if (new_head == nullptr){
                new_head = currb;
            }
            else{
                new_tail->set_next(currb);
            }
            new_tail = currb;
            currb = currb->get_next();
        }
    }
    if (curra == nullptr){
        while (currb){
            if (new_head == nullptr){
                new_head = currb;
            }
            else{
                new_tail->set_next(currb);
            }
            new_tail = currb;
            currb = currb->get_next();
        }
    }
    else{
        while (curra){
            if (new_head == nullptr){
                new_head = curra;
            }
            else{
                new_tail->set_next(curra);
            }
            new_tail = curra;
            curra = curra->get_next();
        }
    }
    *res_tail = new_tail;
    return new_head;
}

list_node* circumcise(list_node** current_head, int len){
    list_node* head = *current_head;
    list_node* tmp = head;
    list_node* tail = nullptr;
    for (int k = 0; k < len; ++k) {
        if (k + 1 == len) {
            tail = tmp;
        }
        tmp = tmp->get_next();
    }
    tail->set_next(nullptr);
    *current_head = tmp;
    return head;
}

void list::sort4(){
    int n = get_length();
    int j = 1;
    while (j < n) {
        list_node* tail = nullptr;
        list_node* curr = head;
        for (int i = 0; i < n; i += 2 * j) {
            list_node* first = nullptr;
            list_node* second = nullptr;
            list_node* res = nullptr;
            list_node *res_tail = nullptr;
            if (i + 2*j >= n) { 
                if (i+j >= n) { 
                    first = circumcise(&curr, n-i);
                    res = merge(first, second, &res_tail);
                }
                else{ 
                    first = circumcise(&curr, j);
                    second = circumcise(&curr, n-i-j);
                    res = merge(first, second, &res_tail);
                }
            }
            else {
                first = circumcise(&curr, j);
                second = circumcise(&curr, j);
                res = merge(first, second, &res_tail);
            }
            if (tail) {
                tail->set_next(res);
            }
            else {
                head = res;
            }
            tail = res_tail;    
        }
        j *= 2;
    }
}

list_node* sr(list_node* head){
    list_node* a = head;
    list_node* b;
    list_node* prev = nullptr;
    for (b = head; b && b->get_next(); b = b->get_next()->get_next()){
        if (prev == nullptr) prev = head;
        else prev = a;
        a = a->get_next();
    }
    if (a != nullptr){
        prev->set_next(a->get_next());
        a->set_next(nullptr);
    }
    return a;
}

void delenie(list_node* head, list_node** greater_head, list_node** equal_head, list_node** less_head, int* cntg, int* cntl){
    list_node* less = nullptr;
    list_node* greater = nullptr;
    list_node* mid = sr(head);
    /*printf("For sr = ");
    mid->print();*/
    list_node* equal = mid;
    *equal_head = mid;
    list_node* curr;
    for (curr = head; curr; curr = curr->get_next()){
        if (*curr < *mid){
            if (*less_head == nullptr){
                *less_head = curr;
            }
            else{
                less->set_next(curr);
            }
            less = curr;
            *cntl += 1;
        }
        else if (*curr == *mid){
            if (*equal_head == nullptr){
                *equal_head = curr;
            }
            else{
                equal->set_next(curr);
            }
            equal = curr;
        }
        else{
            if (*greater_head == nullptr){
                *greater_head = curr;
            }
            else{
                greater->set_next(curr);
            }
            greater = curr;
            *cntg += 1;
        }
    }
    if (less) less->set_next(nullptr);
    if (greater) greater->set_next(nullptr);
    if (equal) equal->set_next(nullptr);
    
}

/*list_node* qqsort(list_node* head){
    int n = length_(head);
    if (n < 2) return head;
    int cntg = 0, cntl = 0;
    list_node* greater_head = nullptr;
    list_node* equal_head = nullptr;
    list_node* less_head = nullptr;
    
    delenie(head, &greater_head, &equal_head, &less_head, &cntg, &cntl);
    greater_head = qqsort(greater_head);
    less_head = qqsort(less_head);
    return skleit(greater_head, equal_head, less_head);
}*/

list_node* qqsort(list_node* head){
    int n = length_(head);
    if (n < 2) return head;
    list_node* greater_head = nullptr;
    list_node* equal_head = nullptr;
    list_node* less_head = nullptr;
    list_node* otsortpr = nullptr;
    list_node* otsortlv = nullptr;
    while (n > 1){
        int cntg = 0, cntl = 0;
        greater_head = nullptr;
        equal_head = nullptr;
        less_head = nullptr;
        delenie(head, &greater_head, &equal_head, &less_head, &cntg, &cntl);
        /*printf("%d = cntg, %d = cntl\n", cntg, cntl);
        printf("prav:\n");
        printl(otsortpr);
        printf("lev:\n");
        printl(otsortlv);
        printf("\n");*/
        if (cntl > cntg && cntl > 2){
            greater_head = qqsort(greater_head);
            if (otsortpr  == nullptr){
                otsortpr = skleit(greater_head, equal_head, nullptr);
            }
            else{
                otsortpr = skleit(otsortpr, greater_head, equal_head);
            }
            head = less_head;
            n = cntl;
            continue;
        }
        else{
            if (cntl == 0){
                if (otsortlv == nullptr){
                    otsortlv = equal_head;
                }
                else{
                    otsortlv = skleit(equal_head, nullptr, otsortlv);
                }
                head = greater_head;
                n = cntg;
                continue;
            }
            if (cntl > 0){
                less_head = qqsort(less_head);
                if (otsortlv  == nullptr){
                    otsortlv = skleit(nullptr, equal_head, less_head);
                }
                else{
                    otsortlv = skleit(equal_head, less_head, otsortlv);
                }
                head = greater_head;
                n = cntg;
                continue;
            }
        }
    }
    head = skleit(otsortpr, head, otsortlv);
    //printl(head);
    return head;
}

/*void sort9 (student* a, int n){
    int i = 0, sr = 0; 
    student per;
    while (n > 1){
        i = 0;
        sr = n / 2;
        i = polov_sort(a[sr], a, n);
        if (i > n - i && n - i - 1 > 1){
            sort9(a + i + 1, n - i - 1);
            n = i;
            continue;
        }
        else{
            if (i == 0){
                a += 1;
                n -= 1;
                continue;
            }
            if (i > 0) {
                sort9(a + 0, i);
                a = a + i + 1;
                n = n - i - 1;
                continue;
            }
        }
    }
}*/

list_node* skleit(list_node* greater, list_node* equal, list_node* less){
    list_node* head;
    if (less)
        head = less;
    else if (equal)
        head = equal;
    else
        head = greater;
    list_node* curr = less;
    for (; curr && curr->get_next(); curr = curr->get_next());
    if (curr)
        curr->set_next(equal);
    else
        curr = equal;
    for (; curr && curr->get_next(); curr = curr->get_next());
    if (curr)
        curr->set_next(greater);
    return head;
}


void list::sort5(){
    head = qqsort(head);
}

void printl(list_node* head){
    list_node* curr = head;
    for (;curr;curr = curr->get_next()){
        curr->print();
    }
}