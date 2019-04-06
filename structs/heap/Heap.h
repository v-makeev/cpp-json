#pragma once
#include "../vector/Vector.h"

#define heap NHeap::nheap

namespace NHeap {
    template <class T, class Comparator>
    class nheap {
        Comparator cmp;
        dvec<T> values;
        void heapify_up(int num) {
            while(num) {
                int father = num >> 1;
                if (cmp(values[father], values[num])) { break; }
                else std::swap(values[father], values[num]);
                num = father;
            }
        }
        void heapify_down(int num) {
            int size = (int)values.size();
            while (num < size) {
                int l = (num << 1) + 1;
                if (l >= size) { break; }
                int r = (num << 1) + 2;
                int num_min = l;
                if (r < size && cmp(values[r], values[l])) {
                    num_min = r;
                }
                if (cmp(values[num_min], values[num])) {
                    std::swap(values[num], values[num_min]);
                    num = num_min;
                } else {
                    break;
                }
            }
        }
    public:
        typedef T value_type;
        typedef Comparator value_comparator;
        nheap(const dvec<T>& values, const Comparator& cmp) : values(values), cmp(cmp) { }
        nheap(const Comparator& cmp) : cmp(cmp) { values.clear(); }
        void push(const T& a);
        void pop();
        size_t size_heap() const {
            return values.size();
        }
        T operator[] (int i) const {
            return values[i];
        }
        T top() {
            return values[0];
        }
    };
    template<class T, class Comparator> 
    void nheap<T, Comparator>::push(const T& a) {
        values.push_back(a);
        heapify_up(values.size() - 1);
    }
    template<class T, class Comparator> 
    void nheap<T, Comparator>::pop() {
        std::swap(values[0], values[values.size() - 1]);
        values.pop_back();
        heapify_down(0);
    }
};