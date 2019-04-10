#include "../structs.h"

namespace JsonStructs {
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

    json_int::json_int() : value(0) {
        set_type(ETE_INT);
    }

    json_int::json_int(const long long &value) : value(value) {
        set_type(ETE_INT);
    }

    json_int::json_int(const json_int &jint) : value(jint.value) {
        set_type(ETE_INT);
    }

    bool json_int::operator==(long long val) const {
        return value == val;
    }
}

