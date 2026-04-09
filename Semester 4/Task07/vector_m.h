#ifndef VECTOR_M_H
#define VECTOR_M_H
#include <stdio.h>
#include "list2.h"
#include "command.h"

template <typename T>
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

        list2_node* move_right(int nach, list2_node* vstavka){
            if (curr_number == 0){
                data[0] = vstavka;
                curr_number = 1;
                return nullptr;
            }
            if (nach < 0) nach = 0;
            if (nach > curr_number) nach = curr_number;
            if (nach == m)
                return vstavka;

            if (curr_number < m){
                for (int i = curr_number; i > nach; --i){
                    data[i] = data[i - 1];
                }
                data[nach] = vstavka;
                ++curr_number;
                return nullptr;
            }

            list2_node* out = data[m - 1];
            for (int i = m - 1; i > nach; --i){
                data[i] = data[i - 1];
            }
            data[nach] = vstavka;
            return out;
        }

        

        void move_left(int i){
            int j;
            for (j = i + 1; j < curr_number; j++){
                data[j - 1] = data[j];
                data[j] = nullptr;
            }
            curr_number -= 1;
        }

        void delete_vector_element(int i){
            move_left(i);
        }

        list2_node* insert(list2_node* x){
            int vst = bin_search(x);
            list2_node* res = move_right(vst, x);
            if (res != nullptr)
                return res;
            return nullptr;
        }
        int bin_search(list2_node* x) {
            throw 1;
        }
};

template<> int vector_m<int>::bin_search(list2_node* x){
    int lhs = 0, rhs = curr_number, mid;
    while (lhs != rhs) {
        mid = (lhs + rhs) / 2;
        if (x->get_phone() < data[mid]->get_phone()) {
            rhs = mid;
        }
        else {
            lhs = mid + 1;
        }
    }
    return rhs;
}


template<> int vector_m<const char*>::bin_search(list2_node* x){
    int lhs = 0, rhs = curr_number, mid;
    while (lhs != rhs) {
        mid = (lhs + rhs) / 2;
        if ((strcmp(x->get_name(), data[mid]->get_name()) < 0)) {
            rhs = mid;
        }
        else {
            lhs = mid + 1;
        }
    }
    return rhs;
}


#endif