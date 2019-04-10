#include "../structs.h"

namespace JsonStructs {
    json_array *base_to_array(const base_type *bt) {
        if (bt->type == ETE_ARRAY) {
            json_array ja = *((json_array *) bt);
            return new json_array{ja};
        }
        return nullptr;
    }

    json_double *base_to_double(const base_type *bt) {
        if (bt->type == ETE_DOUBLE) {
            json_double jd = *((json_double *) bt);
            return new json_double{jd};
        }
        return nullptr;
    }

    json_int *base_to_int(const base_type *bt) {
        if (bt->type == ETE_INT) {
            json_int ji = *((json_int *) bt);
            return new json_int{ji};
        }
        return nullptr;
    }

    json_string *base_to_string(const base_type *bt) {
        if (bt->type == ETE_STRING) {
            json_string js = *((json_string *) bt);
            return new json_string(js);
        }
        return nullptr;
    }

    json_tree *base_to_tree(const base_type *bt) {
        if (bt->type == ETE_TREE) {
            json_tree jt = *((json_tree *) bt);
            return new json_tree(jt);
        }
        return nullptr;
    }

    std::string base_type::to_string() {
        if (type == ETE_NONE) {
            return "None";
        }
        if (type == ETE_INT) {
            return std::to_string((static_cast<json_int *>(this))->get_value());
        }
        if (type == ETE_DOUBLE) {
            return std::to_string((static_cast<json_double *>(this))->get_value());
        }
        if (type == ETE_STRING) {
            return in_quotes((static_cast<json_string *>(this))->get_value());
        }
        if (type == ETE_ARRAY) {
            auto vec = (static_cast<json_array *>(this))->get_value();
            std::string ans = "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                ans += vec[i]->to_string();
                if ((i + 1) != vec.size()) {
                    ans.push_back(',');
                }
            }
            return ans + "]";
        }
        if (type == ETE_TREE) {
            std::string ans = "{";
            auto mp = (static_cast<json_tree *>(this))->get_value();
            size_t ind = 1;
            for (auto it = mp.begin(); it != mp.end(); ++it, ++ind) {
                std::string name = in_quotes(it->first);
                ans += (name + ":") + it->second->to_string();
                if (ind != mp.size()) {
                    ans.push_back(',');
                }
            }
            return ans + "}";
        }
        return "";
    }

    base_type *base_type::get_data(const int &i) const {
        if (type == ETE_ARRAY) {
            return (*((json_array *) this))[i];
        }
        return nullptr;
    }

    void base_type::set_type(ETypeElement ntype) {
        type = ntype;
    }

    base_type *base_type::operator[](const int &i) const {
        return get_data(i);
    }
}