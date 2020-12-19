#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1000;
struct FHQTreap {
    struct Node {
        int key, pq;
        Node *l, *r;
        Node() : key(0), pq(rand()), l(nullptr), r(nullptr) {}
        void maintain() {}
    } nodes[maxn], *root;
    Node *merge(Node *a, Node *b) {
        if (!a)
            return b;
        if (!b)
            return a;
        assert(a && b);
        if (a->pq > b->pq) {
            a->r = merge(a->r, b);
            a->maintain();
            return a;
        } else {
            b->l = merge(a, b->l);
            b->maintain();
            return b;
        }
    }
    pair<Node *, Node*> split(Node *rt, int nkey) {
        if (!rt)
            return make_pair(nullptr, nullptr);
        if (rt->key <= nkey) {
            pair<Node*, Node*> res = split(rt->r, nkey);
            rt->r = res.first;
            rt->maintain();
            return make_pair(rt, res.second);
        } else {
            pair<Node*, Node*> res = split(rt->l, nkey);
            rt->l = res.second;
            rt->maintain();
            return make_pair(res.first, rt);
        }
    }
    Node* insert(Node *t) {
        pair<Node*, Node*> res = split(root, t->key);
        root = merge(merge(res.first, t), res.second);
        return t;
    }
    Node* erase(int key) {
        pair<Node*, Node*> res1 = split(root, key), res2 = split(res1.first, key - 1);
        root = merge(res2.first, merge(merge(res2.second->l, res2.second->r), res1.second));
        return res2.second;
    }
};
