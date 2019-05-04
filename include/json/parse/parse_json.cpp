#include "parse_json.h"

#include <sstream>

namespace JsonBase {
    using std::istringstream;
    using std::make_shared;
    enum { SHIFT = 3, MIN_LENGTH_STRING = 2, MIN_LENGTH_TREE = 2, MIN_LENGTH_ARRAY = 2 };
    bool get_name(const string& s, string& ans) {
        if (s[0] != '"') return false;
        ans.clear();
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == '"') return true;
            ans.push_back(s[i]);
        }
        return false;
    }
    bool parse_named_int(const string& s, string& name, shared_ptr<Int>& p) {
        if (!get_name(s, name)) { return false; }
        if ((name.size() + SHIFT - 1) >= s.size() || s[name.size() + SHIFT - 1] != ':') return false;
        if (!parse_int(s.substr(SHIFT + name.size(), s.size() - name.size() - SHIFT), p)) { return false; }
        return true;
    }
    bool parse_named_double(const string& s, string& name, shared_ptr<Double>& p) {
        if (!get_name(s, name)) { return false; }
        if ((name.size() + SHIFT - 1) >= s.size() || s[name.size() + SHIFT - 1] != ':') return false;
        if (!parse_double(s.substr(SHIFT + name.size(), s.size() - name.size() - SHIFT), p)) { return false; }
        return true;
    }
    bool parse_named_string(const string& s, string& name, shared_ptr<String>& p) {
        if (!get_name(s, name)) { return false; }
        if ((name.size() + SHIFT - 1) >= s.size() || s[name.size() + SHIFT - 1] != ':') return false;
        if (!parse_string(s.substr(SHIFT + name.size(), s.size() - name.size() - SHIFT), p)) { return false; }
        return true;
    }
    bool parse_named_array(const string& s, string& name, shared_ptr<Array>& p) {
        if (!get_name(s, name)) { return false; }
        if ((name.size() + SHIFT - 1) >= s.size() || s[name.size() + SHIFT - 1] != ':') return false;
        if (!parse_array(s.substr(SHIFT + name.size(), s.size() - name.size() - SHIFT), p)) { return false; }
        return true;
    }
    bool parse_named_tree(const string& s, string& name, shared_ptr<Tree>& p) {
        if (!get_name(s, name)) { return false; }
        if ((name.size() + SHIFT - 1) >= s.size() || s[name.size() + SHIFT - 1] != ':') return false;
        if (!parse_tree(s.substr(SHIFT + name.size(), s.size() - name.size() - SHIFT), p)) { return false; }
        return true;
    }

    bool parse_int(const string& s, shared_ptr<Int>& p) {
        int val;
        istringstream in(s);
        if (!(in >> val)) {
            return false;
        }
        if (s != std::to_string(val)) {
            return false;
        }
        p = make_shared<Int>(val);
        return true;
    }
    bool parse_double(const string& s, shared_ptr<Double>& p) {
        double val;
        istringstream in(s);
        if (!(in >> val)) {
            return false;
        }
        p = make_shared<Double>(val);
        return true;
    }
    bool parse_string(const string& s, shared_ptr<String>& p) {
        if (s.size() < MIN_LENGTH_STRING || s[0] != '"' || s[s.size() - 1] != '"') { return false; }
        auto ans = (s.substr(1, s.size() - 2));
        p = make_shared<String>(ans);
        return true;
    }
    bool parse_array(const string& s, shared_ptr<Array>& p) {
        if (s.size() < MIN_LENGTH_ARRAY) { return false; }
        if (s.size() == MIN_LENGTH_ARRAY) { return true; }
        if (s[0] != '[' || s[s.size() - 1] != ']') { return false; }
        vector<size_t> comma{0};
        enum { IN_QUOTE, OUT_QUOTE } state = OUT_QUOTE;
        int deep = 0;
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == '"' && state == IN_QUOTE) { state = OUT_QUOTE; continue; }
            else if (s[i] == '"' && state == OUT_QUOTE) { state = IN_QUOTE; continue; }
            if (state == IN_QUOTE) { continue; }
            if (s[i] == '[' || s[i] == '{') ++deep;
            if (s[i] == ']' || s[i] == '}') --deep;
            if (s[i] == ',' && !deep) { comma.push_back(i); }
        }
        Array ans;
        comma.push_back(s.size() - 1);
        for (size_t i = 1; i < comma.size(); ++i) {
            auto sub = s.substr(comma[i - 1] + 1, comma[i] - comma[i - 1] - 1);
            shared_ptr<Int> si;
            shared_ptr<Double> sd;
            shared_ptr<String> ss;
            shared_ptr<Array> sa;
            shared_ptr<Tree> st;
            if (parse_int(sub, si)) {
                ans.push_back(*si);
            } else if (parse_double(sub, sd)) {
                ans.push_back(*sd);
            } else if (parse_string(sub, ss)) {
                ans.push_back(*ss);
            } else if (parse_array(sub, sa)) {
                ans.push_back(*sa);
            } else if (parse_tree(sub, st)) {
                ans.push_back(*st);
            } else {
                return false;
            }
        }
        p = make_shared<Array>(ans);
        return true;
    }
    bool parse_tree(const string& s, shared_ptr<Tree>& p) {
        if (s.size() < MIN_LENGTH_TREE) { return false; }
        if (s[0] != '{' || s[s.size() - 1] != '}') { return false; }
        vector<size_t> comma{0};
        enum { IN_QUOTE, OUT_QUOTE } state = OUT_QUOTE;
        int deep = 0;
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == '"' && state == IN_QUOTE) { state = OUT_QUOTE; continue; }
            else if (s[i] == '"' && state == OUT_QUOTE) { state = IN_QUOTE; continue; }
            if (state == IN_QUOTE) { continue; }
            if (s[i] == '[' || s[i] == '{') ++deep;
            if (s[i] == ']' || s[i] == '}') --deep;
            if (s[i] == ',' && !deep) { comma.push_back(i); }
        }
        Tree ans;
        comma.push_back(s.size() - 1);
        string name;
        for (size_t i = 1; i < comma.size(); ++i) {
            auto sub = s.substr(comma[i - 1] + 1, comma[i] - comma[i - 1] - 1);
            shared_ptr<Int> si;
            shared_ptr<Double> sd;
            shared_ptr<String> ss;
            shared_ptr<Array> sa;
            shared_ptr<Tree> st;
            if (parse_named_int(sub, name, si)) {
                ans.insert(name, *si);
            } else if (parse_named_double(sub, name, sd)) {
                ans.insert(name, *sd);
            } else if (parse_named_string(sub, name, ss)) {
                ans.insert(name, *ss);
            } else if (parse_named_array(sub, name, sa)) {
                ans.insert(name, *sa);
            } else if (parse_named_tree(sub, name, st)) {
                ans.insert(name, *st);
            } else {
                return false;
            }
        }
        p = make_shared<Tree>(ans);
        return true;
    }
};