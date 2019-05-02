#pragma once
#include "../classes/classes.h"

namespace JsonBase {
    bool parse_named_int(const string& s, string& name, shared_ptr<Int>& p);
    bool parse_named_double(const string& s, string& name, shared_ptr<Double>& p);
    bool parse_named_string(const string& s, string& name, shared_ptr<String>& p);
    bool parse_named_array(const string& s, string& name, shared_ptr<Array>& p);
    bool parse_named_tree(const string& s, string& name, shared_ptr<Tree>& p);

    bool parse_int(const string& s, shared_ptr<Int>& p);
    bool parse_double(const string& s, shared_ptr<Double>& p);
    bool parse_string(const string& s, shared_ptr<String>& p);
    bool parse_array(const string& s, shared_ptr<Array>& p);
    bool parse_tree(const string& s, shared_ptr<Tree>& p);
};