#pragma once

#include <iostream>

#include "../include/string.h"
#include "../include/vector.h"
#include "../include/map.h"


namespace JsonStructs {

    enum ETypeElement {
        ETE_NONE,
        ETE_INT,
        ETE_DOUBLE,
        ETE_STRING,
        ETE_ARRAY,
        ETE_TREE,
    };

    struct base_type {
        ETypeElement type;

        base_type() : type(ETE_NONE) {}

        void set_type(ETypeElement ntype) {
            type = ntype;
        }

        std::string to_string();

        base_type *get_data(const int &i) const;

        base_type *operator[](const int &i) const {
            return get_data(i);
        }
    };

    class json_int : public base_type {
        long long value;
    public:
        json_int() : value(0) {
            set_type(ETE_INT);
        }

        json_int(const long long &value) : value(value) {
            set_type(ETE_INT);
        }

        json_int(const json_int &jint) : value(jint.value) {
            set_type(ETE_INT);
        }

        long long &get_value();

        long long get_value() const;

        bool operator==(long long val) const {
            return value == val;
        }

        friend json_int operator+(const json_int &j1, const json_int &j2);

        friend json_int operator-(const json_int &j1, const json_int &j2);

        friend json_int operator*(const json_int &j1, const json_int &j2);

        friend json_int operator/(const json_int &j1, const json_int &j2);

        friend json_int operator%(const json_int &j1, const json_int &j2);

        friend json_int operator^(const json_int &j1, const json_int &j2);

        friend json_int operator&(const json_int &j1, const json_int &j2);
    };

    class json_double : public base_type {
        double value;
    public:
        json_double(double value = 0) : value(value) {
            set_type(ETE_DOUBLE);
        }

        json_double(const json_double &jdouble) : value(jdouble.value) {
            set_type(ETE_DOUBLE);
        }

        json_double(const json_int &jint) : value(jint.get_value()) {
            set_type(ETE_DOUBLE);
        }

        double &get_value();

        double get_value() const;

        bool operator==(double val) const {
            return value == val;
        }

        friend json_double operator+(const json_double &j1, const json_double &j2);

        friend json_double operator-(const json_double &j1, const json_double &j2);

        friend json_double operator*(const json_double &j1, const json_double &j2);

        friend json_double operator/(const json_double &j1, const json_double &j2);
    };

    class json_string : public base_type {
        std::string value;
    public:
        json_string(const std::string &value) : value(value) {
            set_type(ETE_STRING);
        }

        json_string() : value("") {
            set_type(ETE_STRING);
        }

        size_t size() const {
            return value.size();
        }

        char operator[](int i) const {
            return value[i];
        }

        char &operator[](int i) {
            return value[i];
        }

        std::string get_value() const;

        bool operator==(const std::string &val) const {
            return value == val;
        }

        friend json_string operator+(const json_string &j1, const json_string &j2);
    };

    class json_tree : public base_type {
        dmap<std::string, base_type *> values;
    public:
        json_tree() {
            values.clear();
            set_type(ETE_TREE);
        }

        json_tree(const json_tree &tree) : values(tree.values) {
            set_type(ETE_TREE);
        }

        bool constains(const std::string &s) const {
            return values.find(s) != values.end();
        }

        base_type *get_data(const std::string &s);

        base_type *operator[](const std::string &s);

        const base_type *operator[](const std::string &s) const;

        void insert(const std::string &name, base_type *bt);

        auto get_value() const;
    };

    class json_array : public base_type {
        dvec<base_type *> values;
    public:
        json_array() {
            values.clear();
            set_type(ETE_ARRAY);
        }

        ~json_array() {
            for (auto el : values) {
                delete el;
            }
        }
        json_array(const dvec<base_type *> &values) : values(values) {
            set_type(ETE_ARRAY);
        }

        dvec<base_type *> get_value() const {
            return values;
        }

        base_type *operator[](int i) {
            return values[i];
        }

        const base_type *operator[](int i) const {
            return values[i];
        }

        int size() const {
            return (int) values.size();
        }


        void push_back(const base_type *bt);

        void push_back(const json_int &ji);

        void push_back(const json_double &jd);

        void push_back(const json_string &js);

        void push_back(const json_array &ja);

        void push_back(const json_tree &jt);
    };

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

    long long json_int::get_value() const {
        return value;
    }

    long long &json_int::get_value() {
        return value;
    }

    json_int operator+(const json_int &j1, const json_int &j2) {
        return json_int{j1.value + j2.value};
    }

    json_int operator-(const json_int &j1, const json_int &j2) {
        return json_int{j1.value - j2.value};
    }

    json_int operator*(const json_int &j1, const json_int &j2) {
        return json_int{j1.value * j2.value};
    }

    json_int operator/(const json_int &j1, const json_int &j2) {
        return json_int{j1.value / j2.value};
    }

    json_int operator%(const json_int &j1, const json_int &j2) {
        return json_int{j1.value % j2.value};
    }

    json_int operator^(const json_int &j1, const json_int &j2) {
        return json_int{j1.value ^ j2.value};
    }

    json_int operator&(const json_int &j1, const json_int &j2) {
        return json_int{j1.value & j2.value};
    }

    json_double operator+(const json_double &j1, const json_double &j2) {
        return json_double{j1.value + j2.value};
    }

    json_double operator-(const json_double &j1, const json_double &j2) {
        return json_double{j1.value - j2.value};
    }

    json_double operator*(const json_double &j1, const json_double &j2) {
        return json_double{j1.value * j2.value};
    }

    json_double operator/(const json_double &j1, const json_double &j2) {
        return json_double{j1.value / j2.value};
    }

    double json_double::get_value() const {
        return value;
    }

    double &json_double::get_value() {
        return value;
    }

    json_string operator+(const json_string &j1, const json_string &j2) {
        return json_string{j1.value + j2.value};
    }

    std::string json_string::get_value() const {
        return this->value;
    }

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

    void json_array::push_back(const json_int &ji) {
        values.push_back(new json_int{ji});
    }

    void json_array::push_back(const json_double &jd) {
        values.push_back(new json_double{jd});
    }

    void json_array::push_back(const json_string &js) {
        values.push_back(new json_string{js});
    }

    void json_array::push_back(const json_array &ja) {
        values.push_back(new json_array{ja});
    }

    void json_array::push_back(const json_tree &jt) {
        values.push_back(new json_tree{jt});
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
};