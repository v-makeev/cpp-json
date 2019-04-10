#pragma once

#include <iostream>
#include <sstream>

#include "../include/stack.h"
#include "structs.h"
#include <stdio.h>


namespace JsonParser {
    int parse_int(const std::string &s, JsonStructs::json_int &ji);

    int parse_double(const std::string &s, JsonStructs::json_double &jd);

    int parse_string(const std::string &s, JsonStructs::json_string &js);

    int parse_array(const std::string &s, JsonStructs::json_array &ja);

    int parse_tree(const std::string &s, JsonStructs::json_tree &jt);

    int parse_named_int(const std::string &s, JsonStructs::json_int &ji, std::string &name);

    int parse_named_double(const std::string &s, JsonStructs::json_double &jd, std::string &name);

    int parse_named_string(const std::string &s, JsonStructs::json_string &js, std::string &name);

    int parse_named_array(const std::string &s, JsonStructs::json_array &ja, std::string &name);

    int parse_named_tree(const std::string &s, JsonStructs::json_tree &jt, std::string &name);

    JsonStructs::base_type *parse_element(const std::string &s) {
        JsonStructs::json_int ji;
        if (!parse_int(s, ji)) {
            return new JsonStructs::json_int{ji};
        }
        JsonStructs::json_double jd;
        if (!parse_double(s, jd)) {
            return new JsonStructs::json_double{jd};
        }
        JsonStructs::json_string js;
        if (!parse_string(s, js)) {
            return new JsonStructs::json_string{js};
        }
        JsonStructs::json_array ja;
        if (!parse_array(s, ja)) {
            return new JsonStructs::json_array{ja};
        }
        JsonStructs::json_tree jt;
        if (!parse_tree(s, jt)) {
            return new JsonStructs::json_tree{jt};
        }
        return nullptr;
    }

    JsonStructs::base_type *parse_named_element(const std::string &s, std::string &name) {
        JsonStructs::json_int ji;
        if (!parse_named_int(s, ji, name)) {
            return new JsonStructs::json_int{ji};
        }
        JsonStructs::json_double jd;
        if (!parse_named_double(s, jd, name)) {
            return new JsonStructs::json_double{jd};
        }
        JsonStructs::json_string js;
        if (!parse_named_string(s, js, name)) {
            return new JsonStructs::json_string{js};
        }
        JsonStructs::json_array ja;
        if (!parse_named_array(s, ja, name)) {
            return new JsonStructs::json_array{ja};
        }
        JsonStructs::json_tree jt;
        if (!parse_named_tree(s, jt, name)) {
            return new JsonStructs::json_tree{jt};
        }
        return nullptr;
    }

    int parse_int(const std::string &s, JsonStructs::json_int &ji) {
        long long val = 0;
        if (str_to_ll(s, val)) {
            return 1;
        }
        ji = JsonStructs::json_int(val);
        return 0;
    }

    int parse_double(const std::string &s, JsonStructs::json_double &jd) {
        double val;
        if (str_to_double(s, val)) {
            return 1;
        }
        jd = JsonStructs::json_double(val);
        return 0;
    }

    int parse_string(const std::string &s, JsonStructs::json_string &js) {
        if (s[0] != '"' || dlast(s) != '"') {
            return 1;
        }
        js = JsonStructs::json_string(substr(s, 1, s.size() - 1));
        return 0;
    }

    int get_comment(const std::string &s, std::string &name, size_t &last) {
        name.clear();
        int cnt_quote = 0;
        last = 0;
        for (; last < s.size() && cnt_quote < 2; ++last) {
            if (s[last] == '"') {
                ++cnt_quote;
                continue;
            }
            if (cnt_quote == 1) {
                name.push_back(s[last]);
            }
        }
        ++last;
        return (name.empty() || cnt_quote != 2);
    }

    int parse_named_int(const std::string &s, JsonStructs::json_int &ji, std::string &name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_int(str, ji);
    }

    int parse_named_double(const std::string &s, JsonStructs::json_double &jd, std::string &name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_double(str, jd);
    }

    int parse_named_string(const std::string &s, JsonStructs::json_string &js, std::string &name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_string(str, js);
    }

    int parse_named_array(const std::string &s, JsonStructs::json_array &ja, std::string &name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_array(str, ja);
    }

    int parse_named_tree(const std::string &s, JsonStructs::json_tree &jt, std::string &name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_tree(str, jt);
    }

    int get_comma_from_layer(const std::string &s, dvec<int> &commas) {
        commas.push_back(0);
        enum EState {
            ES_IN, ES_OUT
        };
        EState state = ES_OUT;
        dstack<char> brackets;
        enum {
            DEPTH = 1
        };
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '"') {
                if (state == ES_OUT) {
                    state = ES_IN;
                } else {
                    state = ES_OUT;
                }
                continue;
            }
            if (state == ES_IN) {
                continue;
            }
            if (s[i] == '{' || s[i] == '[') {
                brackets.push(s[i]);
                continue;
            }
            if (s[i] == '}') {
                if (brackets.empty() || brackets.top() != '{') {
                    return 1;
                }
                brackets.pop();
                continue;
            }
            if (s[i] == ']') {
                if (brackets.empty() || brackets.top() != '[') {
                    return 1;
                }
                brackets.pop();
                continue;
            }
            if (s[i] == ',' && brackets.size() == DEPTH) {
                commas.push_back(i);
            }
        }
        commas.push_back(s.size() - 1);
        return 0;
    }

    int parse_array(const std::string &s, JsonStructs::json_array &ja) {
        if (s[0] != '[' || dlast(s) != ']') return 1;
        /*найти все запятые 1-ого уровня*/
        dvec<int> commas;
        if (get_comma_from_layer(s, commas)) {
            return 1;
        }
        for (size_t i = 1; i < commas.size(); ++i) {
            std::string to_parse = substr(s, commas[i - 1] + 1, commas[i]);
            auto el = parse_element(to_parse);
            if (!el) {
                return 1;
            }
            ja.push_back(el);
        }
        return 0;
    }

    int parse_tree(const std::string &s, JsonStructs::json_tree &jt) {
        if (s[0] != '{' || dlast(s) != '}') return 1;
        /*найти все запятые 1-ого уровня*/
        dvec<int> commas;
        if (get_comma_from_layer(s, commas)) {
            return 1;
        }
        std::cout.flush();
        for (size_t i = 1; i < commas.size(); ++i) {
            std::string name;
            auto el = parse_named_element(substr(s, commas[i - 1] + 1, commas[i]), name);
            if (!el) { return 1; }
            jt.insert(name, el);
        }
        return 0;
    }


    class Dictionary {
        JsonStructs::json_tree *tree;
    public:
        Dictionary() : tree(nullptr) {
            tree = new JsonStructs::json_tree{};
        }

        Dictionary(JsonStructs::json_tree *tree) {
            tree = new JsonStructs::json_tree(*tree);
        }

        ~Dictionary() {
            delete tree;
        }

        auto operator[](const std::string &s) const {
            if (tree->constains(s)) {
                auto res = (tree->get_data(s));
                if (res->type == JsonStructs::ETE_TREE) {
                    return Dictionary((JsonStructs::json_tree *) res);
                }
            }
            return Dictionary();
        }

        auto operator()(const std::string &s) const {
            if (tree->constains(s)) {
                auto res = (tree->get_data(s));
                if (res->type == JsonStructs::ETE_ARRAY) {
                    return *((JsonStructs::json_array *) res);
                }
            }
            return JsonStructs::json_array();
        }

        JsonStructs::json_tree *get_root() const {
            return tree;
        }

        std::string to_string() {
            return tree->to_string();
        }

        bool insert(const std::string &s, JsonStructs::base_type *bt) {
            if (!tree) {
                return 0;
            }
            tree->insert(s, bt);
            return 1;
        }

        bool parse(const std::string &s) {
            JsonStructs::json_tree tr;
            if (parse_tree(s, tr)) {
                tree = nullptr;
                return false;
            }
            tree = new JsonStructs::json_tree(tr);
            return true;
        }

        JsonStructs::base_type *get_resource(const std::string &s) const {
            if (!tree->constains(s)) {
                return nullptr;
            }
            return tree->get_data(s);
        }

        std::string get_string(const std::string &s) const {
            if (!tree->constains(s)) {
                return "";
            }
            auto it = tree->get_data(s);
            if (it->type != JsonStructs::ETE_STRING) {
                return "";
            }
            return ((JsonStructs::json_string *) it)->get_value();
        }

        double get_double(const std::string &s) const {
            if (!tree->constains(s)) {
                return 0;
            }
            auto it = tree->get_data(s);
            if (it->type != JsonStructs::ETE_DOUBLE) {
                return 0;
            }
            return ((JsonStructs::json_double *) it)->get_value();
        }

        long long get_int(const std::string &s) const {
            if (!tree->constains(s)) {
                return 0;
            }
            auto it = tree->get_data(s);
            if (it->type != JsonStructs::ETE_INT) {
                return 0;
            }
            return ((JsonStructs::json_int *) it)->get_value();
        }
    };
};