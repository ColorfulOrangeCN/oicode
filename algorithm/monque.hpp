#include <bits/stdc++.h>
namespace go {
    template<typename T, typename Container, typename _Less>
    struct MonQue {
        typedef std::pair<T, int> Meta;
        Container q;
        _Less comp;
        void push(const Meta& v) {
            while (!q.empty() && !comp(q.back().first, v.first))
                q.pop_back();
            q.push_back(v);
        }
        void update(int lr, int rr = 0x7fffffff) {
            while (!q.empty() && (q.front().second < lr || q.front().second > rr))
                q.pop_front();
        }
        Meta& front() {return q.front();}
    };
}
