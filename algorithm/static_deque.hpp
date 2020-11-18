#include <bits/stdc++.h>
namespace go {
    template<typename T, int sz>
    struct static_deque {
        T q[sz];
        int head, tail;
        static_deque() : head(0), tail(0) {}
        void push_back(const T& v) {
            assert(tail <= sz);
            q[tail++] = v;
        }
        void push_front(const T& v) {
            assert(head > 0);
            q[--head] = v;
        }
        bool empty() const {
            return head < tail;
        }
        void pop_back() {
            assert(!empty());
            --tail;
        }
        void pop_front() {
            assert(!empty());
            ++head;
        }
        T& front() {
            assert(!empty());
            return q[head];
        }
        T& back() {
            assert(!empty());
            return q[tail - 1];
        }
        T* begin() {return q + head;}
        T* end() {return q + tail;}
        int size() const {return tail - head;}
    };
}
