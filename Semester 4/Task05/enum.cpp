#include "enum.h"

std::ostream& operator<<(std::ostream& os, const condition& c) {
    const char* str;
    switch (c) {
        case condition::none:
            str = "none"; break;
        case condition::eq:
            str = "eq"; break;
        case condition::ne:
            str = "ne"; break;
        case condition::lt:
            str = "lt"; break;
        case condition::gt:
            str = "gt"; break;
        case condition::le:
            str = "le"; break;
        case condition::ge:
            str = "ge"; break;
        case condition::like:
            str = "like"; break;
        case condition::nlike:
            str = "not like"; break;
        default:
            str = "another";
    }
    os << str;
    return os;
}


std::ostream& operator<<(std::ostream& os, const percent_location& c) {
    const char* str;
    switch (c) {
        case percent_location::start:
            str = "start"; break;
        case percent_location::end:
            str = "end"; break;
        case percent_location::middle:
            str = "middle"; break;
        case percent_location::both:
            str = "both"; break;
        default:
            str = "another";
    }
    os << str;
    return os;
}

std::ostream& operator<<(std::ostream& os, const like_type& c) {
    const char* str;
    switch (c) {
        case like_type::percent:
            str = "%"; break;
        case like_type::underline:
            str = "_"; break;
        case like_type::in_between:
            str = "[]"; break;
        case like_type::not_in_between:
            str = "[^]"; break;
        case like_type::nothing:
            str = "nothing"; break;
        default:
            str = "another"; break;
    }
    os << str;
    return os;
}



std::ostream& operator<<(std::ostream& os, const ordering& c) {
    const char* str;
    switch (c) {
        case ordering::name:
            str = "name "; break;
        case ordering::phone:
            str = "phone "; break;
        case ordering::group:
            str = "group "; break;
        case ordering::none:
            str = "none "; break;
        default:
            str = "another"; break;
    }
    os << str;
    return os;
}

