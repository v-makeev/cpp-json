#include <iostream>
#include "src/parser.h"

int main() {
    JsonParser::Dictionary a;
    a.parse(R"({"name":"Ivan","age":"18"})");
    std::cout << a.to_string() << std::endl;
    return 0;
}