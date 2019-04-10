#pragma once

#include <stdio.h>
#include <string>

#include "vector.h"
#include "defines.h"


std::string in_quotes(const std::string &s) {
    return "\"" + s + "\"";
}

dvec<std::string> split(const std::string &s, char c) {
    std::string cur = "";
    dvec<std::string> ans;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            if (!cur.empty())
                ans.push_back(cur);
            cur = "";
        } else {
            cur += s[i];
        }
    }
    if (!cur.empty())
        ans.push_back(cur);
    return ans;
}

dvec<std::string> split(const std::string &s, const std::string &del) {
    dvec<std::string> v;
    std::string cur = "";
    for (size_t i = 0; i < s.size(); ++i) {
        bool flag = (i + del.size() <= s.size());
        for (size_t j = 0; j < del.size(); ++j) {
            if (!flag || del[j] != s[i + j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            if (!cur.empty())
                v.push_back(cur);
            cur = "";
            i = (i + del.size() - 1);
            continue;
        }
        cur += s[i];
    }
    if (!cur.empty())
        v.push_back(cur);
    return v;
}

std::string substr(const std::string &s, int l, int r) {
    std::string ans = "";
    for (int i = l; i < r && i < (int) s.size(); ++i)
        ans += s[i];
    return ans;
}

std::string replace(const std::string &s, char c, const std::string &nc) {
    std::string ans = "";
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            ans += nc;
        } else {
            ans += s[i];
        }
    }
    return ans;
}

bool contains(const std::string &s, char c) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

dvec<int> all_entry_positions(const std::string &s, const std::string &sub) {
    dvec<int> ans;
    for (size_t i = 0; i < (s.size() - sub.size()); ++i) {
        bool flag = true;
        for (size_t j = 0; j < sub.size(); ++j) {
            if (s[i + j] != sub[j]) {
                flag = false;
                break;
            }
        }
        if (flag) { ans.push_back(i); }
    }
    return ans;
}

dvec<int> all_own_entry_positions(const std::string &s, const std::string &sub) {
    dvec<int> ans;
    for (size_t i = 0; i < (s.size() - sub.size()); ++i) {
        bool flag = true;
        for (size_t j = 0; j < sub.size(); ++j) {
            if (s[i + j] != sub[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) { continue; }
        if (ans.empty() || (dlast(ans) + dsize(sub)) <= i) {
            ans.push_back(i);
        }
    }
    return ans;
}

std::string replace(const std::string &s, const std::string &old, const std::string &fr) {
    auto vec = all_own_entry_positions(s, old);
    int pos_in_vec = 0;
    std::string ans = "";
    for (size_t i = 0; i < s.size(); ++i) {
        if (pos_in_vec < dsize(vec) && i == vec[pos_in_vec]) {
            i += dsize(old) - 1;
            ++pos_in_vec;
            ans += fr;
        } else {
            ans += s[i];
        }
    }
    return ans;
}

bool is_double(const std::string &s) {
    if (dlast(s) == '.') {
        return false;
    }
    int cnt_point = 0;
    for (size_t i = s[0] == '-', val = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            ++cnt_point;
            continue;
        }
        if (s[i] > '9' || s[i] < '0' || cnt_point > 1) {
            return false;
        }
    }
    return true;
}

int str_to_int(const std::string &s, int &val) {
    sscanf(s.c_str(), "%d", &val);
    return 0;
}

int str_to_double(const std::string &s, double &val) {
    if (!is_double(s)) {
        return 1;
    }
    sscanf(s.c_str(), "%lf", &val);
    return 0;
}

int str_to_ll(const std::string &s, long long &val) {
    for (size_t i = (s[0] == '-'); i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return 1;
        }
    }
    sscanf(s.c_str(), "%lld", &val);
    return 0;
}

int str_to_ull(const std::string &s, unsigned long long &val) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return 1;
        }
    }
    sscanf(s.c_str(), "%llu", &val);
    return 0;
}

bool contains(const std::string &s, const std::string &sub) {
    return !all_entry_positions(s, sub).empty();
}