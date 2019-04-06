#pragma once
#include "../stack/Stack.h"
#include "Structs.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace NJsonParser {
    int parse_int(const dstr& s, NJsonStructs::json_int& ji);
    int parse_double(const dstr& s, NJsonStructs::json_double& jd);
    int parse_string(const dstr& s, NJsonStructs::json_string& js);
    int parse_array(const dstr& s, NJsonStructs::json_array& ja);
    int parse_tree(const dstr& s, NJsonStructs::json_tree& jt);

    int parse_named_int(const dstr& s, NJsonStructs::json_int& ji, dstr& name);
    int parse_named_double(const dstr& s, NJsonStructs::json_double& jd, dstr& name);
    int parse_named_string(const dstr& s, NJsonStructs::json_string& js, dstr& name);
    int parse_named_array(const dstr& s, NJsonStructs::json_array& ja, dstr& name);
    int parse_named_tree(const dstr& s, NJsonStructs::json_tree& jt, dstr& name);

    NJsonStructs::base_type* parse_element(const dstr& s) {
        NJsonStructs::json_int ji;
        if (!parse_int(s, ji)) { return new NJsonStructs::json_int(ji); }
        NJsonStructs::json_double jd;
        if (!parse_double(s, jd)) { return new NJsonStructs::json_double(jd); }
        NJsonStructs::json_string js;
        if (!parse_string(s, js)) { return new NJsonStructs::json_string(js); }
        NJsonStructs::json_array ja;
        if (!parse_array(s, ja)) { return new NJsonStructs::json_array(ja); }
        NJsonStructs::json_tree jt;
        if (!parse_tree(s, jt)) { return new NJsonStructs::json_tree(jt); }
        return nullptr;
    }

    NJsonStructs::base_type* parse_named_element(const dstr& s, dstr& name) {
        NJsonStructs::json_int ji;
        if (!parse_named_int(s, ji, name)) { return new NJsonStructs::json_int(ji); }
        NJsonStructs::json_double jd;
        if (!parse_named_double(s, jd, name)) { return new NJsonStructs::json_double(jd); }
        NJsonStructs::json_string js;
        if (!parse_named_string(s, js, name)) { return new NJsonStructs::json_string(js); }
        NJsonStructs::json_array ja;
        if (!parse_named_array(s, ja, name)) { return new NJsonStructs::json_array(ja); }
        NJsonStructs::json_tree jt;
        if (!parse_named_tree(s, jt, name)) { return new NJsonStructs::json_tree(jt); }
        return nullptr;
    }

    int parse_int(const dstr& s, NJsonStructs::json_int& ji) {
        ll val = 0;
        if (dstr_to_ll(s, val)) { return 1; }
        ji = NJsonStructs::json_int(val);
        return 0;
    }
    int parse_double(const dstr& s, NJsonStructs::json_double& jd) {
        double val;
        if (dstr_to_double(s, val)) {
            return 1;
        }
        jd = NJsonStructs::json_double(val);
        return 0;
    }
    int parse_string(const dstr& s, NJsonStructs::json_string& js) {
        if (s[0] != '"' || dlast(s) != '"') { return 1; }
        js = NJsonStructs::json_string(substr(s, 1, s.size() - 1));
        return 0;
    }

    int get_comment(const dstr& s, dstr& name, size_t &last) {
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
        // ':'
        ++last;
        return (name.empty() || cnt_quote != 2);
    }

    int parse_named_int(const dstr& s, NJsonStructs::json_int& ji, dstr& name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_int(str, ji);
    }
    int parse_named_double(const dstr& s, NJsonStructs::json_double& jd, dstr& name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_double(str, jd);
    }
    int parse_named_string(const dstr& s, NJsonStructs::json_string& js, dstr& name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_string(str, js);
    }
    int parse_named_array(const dstr& s, NJsonStructs::json_array& ja, dstr& name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_array(str, ja);
    }
    int parse_named_tree(const dstr& s, NJsonStructs::json_tree& jt, dstr& name) {
        size_t i;
        if (get_comment(s, name, i)) {
            return 1;
        }
        auto str = substr(s, i, s.size());
        return parse_tree(str, jt);
    }

    int get_comma_from_layer(const dstr& s, dvec<int>& commas) {
        commas.push_back(0);
        enum EState { ES_IN, ES_OUT };
        EState state = ES_OUT;
        dstack<char> brackets;
        enum { NEED_DEEP = 1 };
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '"') {
                if (state == ES_OUT) { state = ES_IN; }
                else if (state == ES_IN) { state = ES_OUT; }
                continue;
            }
            if (state == ES_IN) { continue; }
            if (s[i] == '{' || s[i] == '[') {
                brackets.push(s[i]);
                continue;
            }
            if (s[i] == '}') {
                if (brackets.empty()) { return 1; }
                if (brackets.top() != '{') { return 1; }
                brackets.pop();
                continue;
            }
            if (s[i] == ']') {
                if (brackets.empty()) { return 1; }
                if (brackets.top() != '[') { return 1; }
                brackets.pop();
                continue;
            }
            if (s[i] == ',' && brackets.size() == NEED_DEEP) {
                commas.push_back(i);
            }
        }
        commas.push_back(s.size() - 1);
        return 0;
    }

    int parse_array(const dstr& s, NJsonStructs::json_array& ja) {
        if (s[0] != '[' || dlast(s) != ']') return 1;
        /*найти все запятые 1-ого уровня*/
        dvec<int> commas;
        if (get_comma_from_layer(s, commas)) {
            return 1;
        }
        for (size_t i = 1; i < commas.size(); ++i) {
            dstr to_parse = substr(s, commas[i - 1] + 1, commas[i]);
            auto el = parse_element(to_parse);
            if (!el) { return 1; }
            ja.push_back(el);
        }
        return 0;
    }

    int parse_tree(const dstr& s, NJsonStructs::json_tree& jt) {
        if (s[0] != '{' || dlast(s) != '}') return 1;
        /*найти все запятые 1-ого уровня*/
        dvec<int> commas;
        if (get_comma_from_layer(s, commas)) {
            return 1;
        }
        std::cout.flush();
        for (size_t i = 1; i < commas.size(); ++i) {
            dstr name;
            auto el = parse_named_element(substr(s, commas[i - 1] + 1, commas[i]), name);
            if (!el) { return 1; }
            jt.insert(name, el);
        }
        return 0;
    }

    class dictionary {
        NJsonStructs::json_tree* tree;
    public:
        dictionary() : tree(nullptr) { 
            tree = new NJsonStructs::json_tree();
        }
        dictionary(NJsonStructs::json_tree* tree) : tree(tree) { }
        auto operator[] (const dstr &s) const {
            if (tree->contain(s)) {
                auto res = (tree->get_data(s));
                if (res->type == NJsonStructs::ETE_TREE) {
                    return dictionary((NJsonStructs::json_tree*)res);
                }
            }
            return dictionary();
        }
        auto operator()(const dstr& s) const {
            if (tree->contain(s)) {
                auto res = (tree->get_data(s));
                if (res->type == NJsonStructs::ETE_ARRAY) {
                    return *((NJsonStructs::json_array *)res);
                }
            }
            return NJsonStructs::json_array();
        }
        NJsonStructs::json_tree* get_root() const {
            return tree;
        }
        dstr to_string() {
            return tree->to_string();
        }
        bool insert(const dstr& s, NJsonStructs::base_type* bt) {
            if (!tree) { return 0; }
            tree->insert(s, bt);
            return 1;
        }
        bool parse(const dstr& s) {
            NJsonStructs::json_tree tr;
            if (parse_tree(s, tr)) {
                tree = nullptr;
                return false;
            }
            tree = new NJsonStructs::json_tree(tr);
            return true;
        }
        NJsonStructs::base_type* get_resource(const dstr& s) const {
            if (!tree->contain(s)) {
                return nullptr;
            }
            return tree->get_data(s);
        }
        dstr get_string(const dstr& s) const {
            if (!tree->contain(s)) {
                return "";
            }
            auto it = tree->get_data(s);
            if (it->type != NJsonStructs::ETE_STRING) {
                return "";
            }
            return ((NJsonStructs::json_string *)it)->get_value();
        }
        double get_double(const dstr& s) const {
            if (!tree->contain(s)) {
                return 0;
            }
            auto it = tree->get_data(s);
            if (it->type != NJsonStructs::ETE_DOUBLE) {
                return 0;
            }
            return ((NJsonStructs::json_double *)it)->get_value();
        }
        ll get_int(const dstr& s) const {
            if (!tree->contain(s)) {
                return 0;
            }
            auto it = tree->get_data(s);
            if (it->type != NJsonStructs::ETE_INT) {
                return 0;
            }
            return ((NJsonStructs::json_int *)it)->get_value();
        }
    };
};