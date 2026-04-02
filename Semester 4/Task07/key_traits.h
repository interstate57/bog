#ifndef KEY_TRAITS_H
#define KEY_TRAITS_H

#include <cstdlib>
#include <cstring>

#include "list2.h"
#include "command.h"
#include "enum.h"

struct name_key_traits {
    using key_type = const char*;

    static key_type get_key(const list2_node* n) { return n->get_name(); }
    static key_type get_cmd_key(const command& c) { return c.get_name(); }

    static int compare_keys(key_type a, key_type b) { return std::strcmp(a, b); }

    static bool cmd_key_equals_node(const command& c, const list2_node& n) {
        return c.compare_name(condition::eq, n);
    }

    static int hash_key(key_type name, int k) {
        int cnt = 0;
        for (int i = 0; name && name[i]; i++) cnt += (unsigned char)name[i];
        return (k > 0) ? (cnt % k) : 0;
    }
};

struct phone_key_traits {
    using key_type = int;

    static key_type get_key(const list2_node* n) { return n->get_phone(); }
    static key_type get_cmd_key(const command& c) { return c.get_phone(); }

    static int compare_keys(key_type a, key_type b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

    static bool cmd_key_equals_node(const command& c, const list2_node& n) {
        return c.compare_phone(condition::eq, n);
    }

    // Variant A: sum of digits of phone (base-10) mod k
    static int hash_key(key_type phone, int k) {
        if (k <= 0) return 0;
        int x = phone;
        if (x < 0) x = -x;
        int sum = 0;
        if (x == 0) sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum % k;
    }
};

#endif
