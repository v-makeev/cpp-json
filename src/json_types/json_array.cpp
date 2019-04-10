#pragma once

#include "../structs.h"
#include "base_type.cpp"

namespace JsonStructs {
    void json_array::push_back(const base_type *bt) {
        if (bt->type == ETE_ARRAY) {
            values.push_back(base_to_array(bt));
        } else if (bt->type == ETE_DOUBLE) {
            values.push_back(base_to_double(bt));
        } else if (bt->type == ETE_INT) {
            values.push_back(base_to_int(bt));
        } else if (bt->type == ETE_STRING) {
            values.push_back(base_to_string(bt));
        } else if (bt->type == ETE_TREE) {
            values.push_back(base_to_tree(bt));
        } else {
            values.push_back((base_type *) bt);
        }
    }

    json_array::json_array() {
        values.clear();
        set_type(ETE_ARRAY);
    }

    json_array::~json_array() {
        for (auto el : values) {
            delete el;
        }
    }

    json_array::json_array(const dvec<base_type *> &values) : values(values) {
        set_type(ETE_ARRAY);
    }

    dvec<base_type *> json_array::get_value() const {
        return values;
    }

    base_type *json_array::operator[](int i) {
        return values[i];
    }

    const base_type *json_array::operator[](int i) const {
        return values[i];
    }

    int json_array::size() const {
        return (int) values.size();
    }

    template<typename T>
    void json_array::push_back(const T &val) {
        auto p = new T;
        values.push_back(p);
    }
}