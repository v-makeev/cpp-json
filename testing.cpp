#include "include/json/parse/parse_json.h"

#include <iostream>

using namespace std;
using namespace JsonBase;

int main() {
    string s;
    cin >> s;
    shared_ptr<Tree> tree;
    if (!parse_tree(s, tree)) {
        cout << "parse error\n";
    } else {
        cout << tree->as_string();
    }
    return 0;
}