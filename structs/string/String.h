#pragma once
#include "../vector/Vector.h"
#include "../Defines.h"
#include <stdio.h>
#include <string>

#define dstr std::string
#define smth_to_string std::to_string

inline dstr in_quotes(const dstr& s) {
    return "\"" + s + "\"";
}

dvec<dstr> split(const dstr& s, char c) {
    dstr cur = "";
    dvec<dstr> ans;
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

dvec<dstr> split(const dstr& s, const dstr& del) {
    dvec<dstr> v;
    dstr cur = "";
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

dstr substr(const dstr& s, int l, int r) {
    dstr ans = "";
    for (int i = l; i < r && i < (int)s.size(); ++i)
        ans += s[i];
    return ans;
}

dstr replace(const dstr& s, char c, const dstr& nc) {
    dstr ans = "";
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            ans += nc;
        } else {
            ans += s[i];
        }
    }
    return ans;
}

bool contain(const dstr& s, char c) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

dvec<int> all_entry_positions(const dstr& s, const dstr& sub) {
    dvec<int> ans;
    for (size_t i = 0; i < (s.size() - sub.size()); ++i) {
        bool flag = true;
        for (size_t j = 0; j < sub.size(); ++j) {
            if (s[i + j] != sub[j]) { flag = false; break; }
        }
        if (flag) { ans.push_back(i); }
    }
    return ans;
}

dvec<int> all_own_entry_positions(const dstr& s, const dstr& sub) {
    dvec<int> ans;
    for (size_t i = 0; i < (s.size() - sub.size()); ++i) {
        bool flag = true;
        for (size_t j = 0; j < sub.size(); ++j) {
            if (s[i + j] != sub[j]) { flag = false; break; }
        }
        if (!flag) { continue; } 
        if (ans.empty() || (dlast(ans) + dsize(sub)) <= i) {
            ans.push_back(i); 
        }
    }
    return ans;
}

dstr replace(const dstr& s, const dstr& old, const dstr& fr) {
    auto vec = all_own_entry_positions(s, old);
    int pos_in_vec = 0;
    dstr ans = "";
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

dstr pchar_to_string(const char* pbuf) {
    char *buf = (char *)pbuf;
    dstr ans = "";
    while(buf && *buf != '\0') {
        ans.push_back(*buf);
        buf++;
    }
    return ans;
}

bool is_double(const dstr& s) {
    if (dlast(s) == '.') { return false; }
    int cnt_point = 0;
    for (size_t i = s[0] == '-', val = 0; i < s.size(); ++i) {
        if (s[i] == '.') { ++cnt_point; continue; }
        if (s[i] > '9' || s[i] < '0') { return false; }
        if (cnt_point > 1) { return false; }
    }
    return true;
}

int dstr_to_int(const dstr& s, int& val) {
    sscanf(s.c_str(), "%d", &val);
    return 0;
}

int dstr_to_double(const dstr& s, double& val) {
    if (!is_double(s)) { return 1; }
    sscanf(s.c_str(), "%lf", &val);
    return 0;
}

int dstr_to_ll(const dstr& s, ll& val) {
    for (size_t i = (s[0] == '-'); i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') { return 1; }
    }
    sscanf(s.c_str(), "%lld", &val);
    return 0;
}

int dstr_to_ull(const dstr& s, ull& val) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') { return 1; }
    }
    sscanf(s.c_str(), "%llu", &val);
    return 0;
}

bool contain(const dstr& s, const dstr& sub) {
    return !all_entry_positions(s, sub).empty();
}