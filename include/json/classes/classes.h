#pragma once
#include "../../string/String.h"
#include "../../vector/Vector.h"
#include "../../map/Map.h"

#include <memory>

namespace JsonBase {
    using std::unique_ptr;
    using std::shared_ptr;
    enum TypeElement { TE_BASE, TE_INT, TE_DOUBLE, TE_STRING, TE_ARRAY, TE_TREE };

    struct Element;
    class Int;
    class Double;
    class String;
    class Array;
    class Tree;

    struct Element {
        Element();
        Element(const Element& e);
        virtual string as_string() const;
        virtual TypeElement get_type() const;
        ~Element();
    };
    class Int : public Element {
        int value;
    public:
        Int();
        Int(int value);
        Int(const Int& i);
        int get_value() const;
        string as_string() const override;
        TypeElement get_type() const override;
        ~Int();
    };
    class Double : public Element {
        double value;
    public:
        Double();
        Double(double value);
        Double(const Double& d);
        string as_string() const override;
        TypeElement get_type() const override;
        ~Double();
    };
    class String : public Element {
        string value;
    public:
        String();
        String(const string& s);
        String(const String& s);
        string as_string() const override;
        TypeElement get_type() const override;
        char& operator[](int i) { return value[i]; }
        char operator[](int i) const { return value[i]; }
        ~String();
    };
    class Array : public Element {
        vector<unique_ptr<Element>> value;
    public:
        Array();
        Array(const Array& a);

        void push_back(Element* e);
        void push_back(const Int& i);
        void push_back(const Double& d);
        void push_back(const String& s);
        void push_back(const Array& a);
        void push_back(const Tree& a);
        Element* operator[] (int i) { return value[i].get(); }
        size_t size() const;

        string as_string() const override;
        TypeElement get_type() const override;
        ~Array();
    };
    class Tree : public Element {
        map<string, shared_ptr<Element>> value;
    public:
        Tree();
        Tree(const Tree& t);

        void insert(const string& name, Element* e);
        void insert(const string& name, const Int& i);
        void insert(const string& name, const Double& d);
        void insert(const string& name, const String& s);
        void insert(const string& name, const Array& a);
        void insert(const string& name, const Tree& t);
        Array operator ()(const string& s);
        Tree operator [](const string& s);

        string as_string() const override;
        TypeElement get_type() const override;
        ~Tree();
    };
};