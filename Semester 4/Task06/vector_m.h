#ifndef VECTOR_M_H
#define VECTOR_M_H
#include <stdio.h>
#include "list2.h"
#include "command.h"

class vector_m{
    private:
        int m = 0;
        list2_node** data = nullptr;
        int curr_number = 0;
    public:
        vector_m() = default;
        ~vector_m(){
            delete[] data;
            data = nullptr;
            m = 0;
            curr_number = 0;
        }
        int init(int x){
            m = x;
            data = new list2_node*[m];
            if (!data)
                return -1;
            for (int i = 0; i < m; i++) data[i] = nullptr;
            return 0;
        }
        int get_curr_number(){
            return curr_number;
        }
        list2_node* get_data_i(int i){
            if (i < curr_number)
                return data[i];
            return nullptr;
        }
        int bin_search(list2_node* x) {
            int lhs = 0, rhs = curr_number, mid;
            while (lhs != rhs) {
                mid = (lhs + rhs) / 2;
                if (strcmp(x->get_name(), data[mid]->get_name()) < 0) {
                    lhs = mid + 1;
                }
                else {
                    rhs = mid;
                }
            }
            return rhs;
        }
        list2_node* move_right(int nach, list2_node* vstavka){ ///
            int end;
            list2_node* dop1 = nullptr;
            list2_node* dop2 = nullptr;
            if (curr_number == 0){
                data[0] = vstavka;
                curr_number += 1;
                return nullptr;
            }
            if (nach == m)
                return vstavka;
            if (curr_number + 1 <= m){
                end = curr_number + 1;
            }
            else{
                end = m;
            }
            for (int i = nach; i < end - 1; i++){
                if (i == nach){
                    dop1 = data[i];
                    data[i] = vstavka;
                }
                else{
                    dop2 = data[i];
                    data[i] = dop1;
                    dop1 = dop2;
                }
            }
            if (curr_number + 1 <= m){
                data[end - 1] = dop1;
            }
            else{
                dop2 = data[end - 1];
                data[end - 1] = dop1;
                curr_number += 1;
                return dop2;
            }
            curr_number += 1;
            return nullptr;
        }

        void move_left(int i){
            int j;
            for (j = i + 1; j < curr_number; j++){
                data[j - 1] = data[j];
                data[j] = 0;
            }
            curr_number -= 1;
        }

        void delete_vector_element(int i){
            // Вектор хранит только указатели на элементы основного списка, не владеет ими.
            move_left(i);
        }

        list2_node* insert(list2_node* x){
            int vst = bin_search(x);
            list2_node* res = move_right(vst, x);
            if (res != nullptr)
                return res;
            return nullptr;
        }
};

#endif