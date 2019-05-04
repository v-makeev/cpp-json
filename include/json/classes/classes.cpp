#include "classes.h"

#include <sstream>

namespace JsonBase {
    using std::make_unique;
    using std::make_shared;

    Element::Element() { }
    Element::Element(const Element& e) { }
    Element::~Element() { }
    string Element::as_string() const { return "__BASE__TYPE__"; }
    TypeElement Element::get_type() const { return TE_BASE; }

    Int::Int() : value{} { }
    Int::Int(int value) : value(value) { }
    Int::Int(const Int& i) : value(i.value) { }
    int Int::get_value() const { return value; }
    string Int::as_string() const {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
    TypeElement Int::get_type() const {
        return TE_INT;
    }
    Int::~Int() { }

    Double::Double() : value{} { }
    Double::Double(double value) : value(value) { }
    Double::Double(const Double& d) : value(d.value) { }
    string Double::as_string() const {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
    TypeElement Double::get_type() const {
        return TE_DOUBLE;
    }
    Double::~Double() { }

    String::String() : value{} { }
    String::String(const string& s) : value(s) { }
    String::String(const String& s) : value(s.value) { }
    string String::as_string() const {
        std::ostringstream ss;
        ss << '"' << value << '"';
        return ss.str();
    }
    TypeElement String::get_type() const {
        return TE_STRING;
    }
    String::~String() { }

    Array::Array() : value{} { }
    Array::Array(const Array& a) {
        for (size_t i = 0; i < a.value.size(); ++i) {
            if (a.value[i]->get_type() == TE_BASE)
                value.push_back(make_unique<Element>(*a.value[i]));
            if (a.value[i]->get_type() == TE_INT)
                value.push_back(make_unique<Int>(*(Int*)a.value[i].get()));
            if (a.value[i]->get_type() == TE_DOUBLE)
                value.push_back(make_unique<Double>(*(Double*)a.value[i].get()));
            if (a.value[i]->get_type() == TE_STRING)
                value.push_back(make_unique<String>(*(String*)a.value[i].get()));
            if (a.value[i]->get_type() == TE_ARRAY)
                value.push_back(make_unique<Array>(*(Array*)a.value[i].get()));
            if (a.value[i]->get_type() == TE_TREE)
                value.push_back(make_unique<Tree>(*(Tree*)a.value[i].get()));
        }
    }
    void Array::push_back(Element* e) {
        if (e->get_type() == TE_BASE)
            value.push_back(unique_ptr<Element>(e));
        if (e->get_type() == TE_INT)
            value.push_back(make_unique<Int>(*(Int*)e));
        if (e->get_type() == TE_DOUBLE)
            value.push_back(make_unique<Double>(*(Double*)e));
        if (e->get_type() == TE_STRING)
            value.push_back(make_unique<String>(*(String*)e));
        if (e->get_type() == TE_ARRAY)
            value.push_back(make_unique<Array>(*(Array*)e));
        if (e->get_type() == TE_TREE)
            value.push_back(make_unique<Tree>(*(Tree*)e));
    }
    void Array::push_back(const Int& i) {
        value.push_back(make_unique<Int>(i));
    }
    void Array::push_back(const Double& d) {
        value.push_back(make_unique<Double>(d));
    }
    void Array::push_back(const String& s) {
        value.push_back(make_unique<String>(s));
    }
    void Array::push_back(const Array& a) {
        value.push_back(make_unique<Array>(a));
    }
    void Array::push_back(const Tree& t) {
        value.push_back(make_unique<Tree>(t));
    }
    size_t Array::size() const { return value.size(); }
    Array::~Array() { }
    string Array::as_string() const {
        if (value.empty()) { return "[]"; }
        string ans = "[";
        for (auto el = value.begin(); el != value.end(); ++el) {
            if (el != value.begin())
                ans += ("," + (*el)->as_string());
            else
                ans += ((*el)->as_string());
        }
        return ans + "]";
    }
    TypeElement Array::get_type() const {
        return TE_ARRAY;
    }
    Tree::Tree() : value{} { }
    Tree::Tree(const Tree& t) {
        auto mp = t.value;
        for (auto el = mp.begin(); el != mp.end(); ++el) {
            auto pntr = el->second.get();
            switch (pntr->get_type()) {
                case TE_INT:
                    value.insert({el->first, make_shared<Int>(*(Int*)pntr)});
                    break;
                case TE_DOUBLE:
                    value.insert({el->first, make_shared<Double>(*(Double*)pntr)});
                    break;
                case TE_STRING:
                    value.insert({el->first, make_shared<String>(*(String*)pntr)});
                    break;
                case TE_ARRAY:
                    value.insert({el->first, make_shared<Array>(*(Array*)pntr)});
                    break;
                case TE_TREE:
                    value.insert({el->first, make_shared<Tree>(*(Tree*)pntr)});
                    break;
            }
        }
    }
    void Tree::insert(const string& name, Element* e) {
        if (e->get_type() == TE_BASE)
            value.insert({ name, shared_ptr<Element>(e) });
        if (e->get_type() == TE_INT)
            value.insert({ name, make_shared<Int>(*(Int*)e) });
        if (e->get_type() == TE_DOUBLE)
            value.insert({ name, make_shared<Double>(*(Double*)e) });
        if (e->get_type() == TE_STRING)
            value.insert({ name, make_shared<String>(*(String*)e) });
        if (e->get_type() == TE_ARRAY)
            value.insert({ name, make_shared<Array>(*(Array*)e) });
        if (e->get_type() == TE_TREE)
            value.insert({ name, make_shared<Tree>(*(Tree*)e) });
    }
    void Tree::insert(const string& name, const Int& i) {        
        value.insert({ name, make_shared<Int>(i) });
    }
    void Tree::insert(const string& name, const Double& d) {
        value.insert({ name, make_shared<Double>(d) });
    }
    void Tree::insert(const string& name, const String& s) {
        value.insert({ name, make_shared<String>(s) });
    }
    void Tree::insert(const string& name, const Array& a) {
        value.insert({ name, make_shared<Array>(a) });
    }
    void Tree::insert(const string& name, const Tree& t) {
        value.insert({ name, make_shared<Tree>(t) });
    }
    Array Tree::operator ()(const string& s) {
        return *(Array*)value[s].get();
    }
    Tree Tree::operator [](const string& s) {
        return *(Tree*)value[s].get();
    }
    string Tree::as_string() const {
        if (value.empty())
            return "{}";
        string ans = "{";
        for (auto el = value.begin(); el != value.end(); ++el) {
            if (el != value.begin())
                ans += (",\"" + el->first + "\":" + el->second->as_string());
            else
                ans += ("\"" + el->first + "\":" + el->second->as_string());
        }
        return ans + "}";
    }
    TypeElement Tree::get_type() const {
        return TE_TREE;
    }
    Tree::~Tree() { }
};