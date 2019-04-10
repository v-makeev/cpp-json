#include "../structs.h"

namespace JsonStructs {
    double json_double::get_value() const {
        return value;
    }

    double &json_double::get_value() {
        return value;
    }

    json_double::json_double(double value) : value(value) {
        set_type(ETE_DOUBLE);
    }

    json_double::json_double(const json_double &jdouble) : value(jdouble.value) {
        set_type(ETE_DOUBLE);
    }

    json_double::json_double(const json_int &jint) : value(jint.get_value()) {
        set_type(ETE_DOUBLE);
    }

    bool json_double::operator==(double val) const {
        return value == val;
    }

    json_double operator+(const json_double &j1, const json_double &j2) {
        return json_double{j1.value + j2.value};
    }

    json_double operator-(const json_double &j1, const json_double &j2) {
        return json_double{j1.value - j2.value};
    }

    json_double operator*(const json_double &j1, const json_double &j2) {
        return json_double{j1.value * j2.value};
    }

    json_double operator/(const json_double &j1, const json_double &j2) {
        return json_double{j1.value / j2.value};
    }
}