#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <string.h>

#include "enum.h"
#include "list2.h"

class comparator{
    private:
        ordering first = ordering::none;
        ordering second = ordering::none;
        ordering third = ordering::none;

    public:
        comparator(const ordering first_, const ordering second_, const ordering third_){
            first = first_;
            second = second_;
            third = third_;
        }
        ~comparator() = default;
        bool operator()(const list2_node* a, const list2_node* b){
            int cmp;
            switch(first){
                case ordering::name:
                    cmp = strcmp(a->get_name(), b->get_name());
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (a->get_phone() == b->get_phone())
                        break;
                    return a->get_phone() < b->get_phone();
                case ordering::group:
                    if (a->get_group() == b->get_group())
                        break;
                    return a->get_group() < b->get_group();
                case ordering::none:
                    return true;
            }
            switch(second){
                case ordering::name:
                    cmp = strcmp(a->get_name(), b->get_name());
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (a->get_phone() == b->get_phone())
                        break;
                    return a->get_phone() < b->get_phone();
                case ordering::group:
                    if (a->get_group() == b->get_group())
                        break;
                    return a->get_group() < b->get_group();
                case ordering::none:
                    return true;
            }
            switch(third){
                case ordering::name:
                    cmp = strcmp(a->get_name(), b->get_name());
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (a->get_phone() == b->get_phone())
                        break;
                    return a->get_phone() < b->get_phone();
                case ordering::group:
                    if (a->get_group() == b->get_group())
                        break;
                    return a->get_group() < b->get_group();
                case ordering::none:
                    return true;
            }
            return true;
        }
};

#endif