#include "json_string.h"

namespace JsonStructs {
    json_string operator+(const json_string &j1, const json_string &j2) {
        return json_string{j1.value + j2.value};
    }

    std::string json_string::get_value() const {
        return this->value;
    }

    json_string::json_string(const std::string &value) : value(value) {
        set_type(ETE_STRING);
    }

    json_string::json_string() : value("") {
        set_type(ETE_STRING);
    }

    size_t json_string::size() const {
        return value.size();
    }

    char json_string::operator[](int i) const {
        return value[i];
    }

    char &json_string::operator[](int i) {
        return value[i];
    }

    bool json_string::operator==(const std::string &val) const {
        return value == val;
    }
}