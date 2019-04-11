#include "json_tree.h"

namespace JsonStructs {
    auto json_tree::get_value() const {
        return this->values;
    }

    void json_tree::insert(const std::string &name, base_type *bt) {
        if (!bt) { return; }
        if (bt->type == ETE_ARRAY) {
            values.insert(std::make_pair(name, base_to_array(bt)));
        } else if (bt->type == ETE_DOUBLE) {
            values.insert(std::make_pair(name, base_to_double(bt)));
        } else if (bt->type == ETE_INT) {
            values.insert(std::make_pair(name, base_to_int(bt)));
        } else if (bt->type == ETE_STRING) {
            values.insert(std::make_pair(name, base_to_string(bt)));
        } else if (bt->type == ETE_TREE) {
            values.insert(std::make_pair(name, base_to_tree(bt)));
        }
    }

    const base_type *json_tree::operator[](const std::string &s) const {
        auto it = values.find(s);
        if (it == values.end()) {
            return nullptr;
        }
        return it->second;
    }

    base_type *json_tree::operator[](const std::string &s) {
        auto it = values.find(s);
        if (it == values.end()) {
            return nullptr;
        }
        return it->second;
    }

    base_type *json_tree::get_data(const std::string &s) {
        auto it = values.find(s);
        if (it == values.end()) {
            return nullptr;
        }
        return it->second;
    }

    json_tree::json_tree() {
        values.clear();
        set_type(ETE_TREE);
    }

    json_tree::json_tree(const json_tree &tree) : values(tree.values) {
        set_type(ETE_TREE);
    }

    bool json_tree::contains(const std::string &s) const {
        return values.find(s) != values.end();
    }
}