#include "list.h"

int get_len(node* head){
    node* curr;
    int i = 0;
    for (curr = head; curr; curr = curr->next){
        i++;
    }
    return i;
}

void delete_list(node* head){
    node *curr, *next;
    for (curr = head; curr; curr = next){
        next = curr->next;
        free(curr->string);
        free(curr);
    }
}

io_status read_list(node** res, const char* name){
    char buf[LEN] = {0};
    FILE* fp = 0;
    int j;
    node *prev = 0;
    node* head = 0;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    while (fgets(buf, LEN, fp)){
        node* a = (node*)malloc(sizeof(node));
        for (j = 0; buf[j]; j++){
            if (buf[j] == '\n'){
                buf[j] = 0;
                break;
            }
        }
        if (!a){
            fclose(fp);
            delete_list(head);
            return ERROR_MEMORY;
        }
        a->string = (char*)malloc((j + 1) * sizeof(char));
        a->next = 0;
        if (!a->string){
            fclose(fp);
            free(a);
            delete_list(head);
            return ERROR_MEMORY;
        }
        strcpy(a->string, buf);
        if (!head){
            head = a;
            prev = head;
        }
        else{
            prev->next = a;
            prev = a;
        }
    }
    if (!feof(fp)){
        fclose(fp);
        delete_list(head);
        return ERROR_READ;
    }
    *res = head;
    return SUCCESS;
}

void print_list(node* head, int p){
    int i;
    node* curr = head;
    for (i = 0; i < p && curr; i++){
        printf("%s\n", curr->string);
        curr = curr->next;
    }
}