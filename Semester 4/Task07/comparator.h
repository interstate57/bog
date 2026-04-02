#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <string.h>

#include "enum.h"


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
        bool operator()(const char* namea, const char* nameb, int phonea, int phoneb, int groupa, int groupb){
            int cmp;
            switch(first){
                case ordering::name:
                    cmp = strcmp(namea, nameb);
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (phonea == phoneb)
                        break;
                    return phonea < phoneb;
                case ordering::group:
                    if (groupa == groupb)
                        break;
                    return groupa < groupb;
                case ordering::none:
                    return true;
            }
            switch(second){
                case ordering::name:
                    cmp = strcmp(namea, nameb);
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (phonea == phoneb)
                        break;
                    return phonea < phoneb;
                case ordering::group:
                    if (groupa == groupb)
                        break;
                    return groupa < groupb;
                case ordering::none:
                    return true;
            }
            switch(third){
                case ordering::name:
                    cmp = strcmp(namea, nameb);
                    if (cmp == 0)
                        break;
                    return cmp < 0 ? true : false;
                case ordering::phone:
                    if (phonea == phoneb)
                        break;
                    return phonea < phoneb;
                case ordering::group:
                    if (groupa == groupb)
                        break;
                    return groupa < groupb;
                case ordering::none:
                    return true;
            }
            return true;
        }
};

#endif