#pragma once

#include <iostream>

#include "../include/string.h"
#include "../include/vector.h"
#include "../include/map.h"


namespace JsonStructs {

    enum ETypeElement {
        ETE_NONE,
        ETE_INT,
        ETE_DOUBLE,
        ETE_STRING,
        ETE_ARRAY,
        ETE_TREE,
    };

    struct base_type {
        ETypeElement type;

        base_type() : type(ETE_NONE) {}

        void set_type(ETypeElement ntype);

        std::string to_string();

        base_type *get_data(const int &i) const;

        base_type *operator[](const int &i) const;
    };

    class json_int : public base_type {
        long long value;
    public:
        json_int();

        explicit json_int(const long long &value);

        json_int(const json_int &jint);

        long long &get_value();

        long long get_value() const;

        bool operator==(long long val) const;

        friend json_int operator+(const json_int &j1, const json_int &j2);

        friend json_int operator-(const json_int &j1, const json_int &j2);

        friend json_int operator*(const json_int &j1, const json_int &j2);

        friend json_int operator/(const json_int &j1, const json_int &j2);

        friend json_int operator%(const json_int &j1, const json_int &j2);

        friend json_int operator^(const json_int &j1, const json_int &j2);

        friend json_int operator&(const json_int &j1, const json_int &j2);
    };

    class json_double : public base_type {
        double value;
    public:
        explicit json_double(double value = 0);

        json_double(const json_double &jdouble);

        explicit json_double(const json_int &jint);

        double &get_value();

        double get_value() const;

        bool operator==(double val) const;

        friend json_double operator+(const json_double &j1, const json_double &j2);

        friend json_double operator-(const json_double &j1, const json_double &j2);

        friend json_double operator*(const json_double &j1, const json_double &j2);

        friend json_double operator/(const json_double &j1, const json_double &j2);
    };

    class json_string : public base_type {
        std::string value;
    public:
        explicit json_string(const std::string &value);

        json_string();

        size_t size() const;

        char operator[](int i) const;

        char &operator[](int i);

        std::string get_value() const;

        bool operator==(const std::string &val) const;

        friend json_string operator+(const json_string &j1, const json_string &j2);
    };

    class json_tree : public base_type {
        dmap<std::string, base_type *> values;
    public:
        json_tree();

        json_tree(const json_tree &tree);

        bool contains(const std::string &s) const;

        base_type *get_data(const std::string &s);

        base_type *operator[](const std::string &s);

        const base_type *operator[](const std::string &s) const;

        void insert(const std::string &name, base_type *bt);

        auto get_value() const;
    };

    class json_array : public base_type {
        dvec<base_type *> values;
    public:
        json_array();

        ~json_array();

        explicit json_array(const dvec<base_type *> &values);

        dvec<base_type *> get_value() const;

        base_type *operator[](int i);

        const base_type *operator[](int i) const;

        int size() const;

        void push_back(const base_type *bt);

        template <typename T>
        void push_back(const T &val);
    };
};