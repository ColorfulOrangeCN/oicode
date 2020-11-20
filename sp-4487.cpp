#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, lgn = 17;
struct FHQTreap {
    struct Node {
        int py, sum, x, maxsec, lsec, rsec, size;
        Node *lc, *rc;
        Node() : py(rand()), sum(0), maxsec(0), lsec(0), rsec(0), size(1) {}
        void update() {
            if (lc && rc) {
                sum = lc->sum + rc->sum + x;
                maxsec = max({lc->maxsec, rc->maxsec, lc->rsec + x + rc->lsec});
                lsec = max(lc->lsec, lc->sum + x + max(rc->lsec, 0));
                rsec = max(rc->rsec, rc->sum + x + max(lc->rsec, 0));
                size = lc->size + rc->size + 1;
            } else if (lc) {
                sum = lc->sum + x;
                maxsec = max(lc->maxsec, lc->rsec + x);
                lsec = max(lc->lsec, lc->sum + x);
                rsec = max(x, lc->rsec + x);
                size = lc->size + 1;
            } else if (rc) {
                sum = rc->sum + x;
                maxsec = max(rc->maxsec, rc->rsec + x);
                rsec = max(rc->rsec, rc->sum + x);
                lsec = max(x, rc->lsec + x);
                size = rc->size + 1;
            } else {
                maxsec = lsec = rsec = sum = x;
                size = 1;
            }
        }
    } nodes[maxn * 2], *root;
    int newp;
    FHQTreap() : newp(0) {}
    typedef Node* NP;
    NP merge(NP l, NP r) {
        if (!l) {
            r->update();
            return r;
        }
        if (!r) {
            l->update();
            return l;
        }
        assert(l && r);
        cerr << "MERGE " << l->x << ' ' << r->x << endl;
        if (l->py > r->py) {
            l->rc = merge(l->rc, r);
            l->update();
            return l;
        } else {
            r->lc = merge(l, r->lc);
            r->update();
            return r;
        }
    }
    pair<NP, NP> split(NP rt, int sz) {
        cerr << "BEFORE SPLIT "<< rt << ' ' << sz << endl;
        if (!rt)
            return make_pair(nullptr, nullptr);
        assert(rt->size >= sz);
        cerr << "SPLIT " << rt->size << ' ' << rt->x << ' ' << sz << endl;
        if ((rt->lc ? rt->lc->size : 0) + 1 <= sz) {
            pair<NP, NP> res = split(rt->rc, sz - (rt->lc ? rt->lc->size : 0) - 1);
            rt->rc = res.first;
            rt->update();
            return make_pair(rt, res.second);
        } else {
            pair<NP, NP> res = split(rt->lc, sz);
            rt->lc = res.second;
            rt->update();
            return make_pair(res.first, rt);
        }
    }
    inline NP getNode(int x) {
        nodes[newp].x = x;
        nodes[newp].update();
        return nodes + (newp++);
    }
    NP insert(Node *t, int p) {
        cerr << root->size << endl;
        pair<NP, NP> res = split(root, p - 1);
        cerr << "INSERT "<< res.first->size << ' ' << res.second << endl;
        root = merge(res.first, merge(t, res.second));
        cerr << "AFTER INSERT " << root->size << endl;
        return t;
    }
    NP erase(int p) {
        pair<NP, NP> res1 = split(root, p);
        cerr << res1.first->size << endl;
        pair<NP, NP> res2 = split(res1.first, 1);
        assert(res2.second && res2.second->size == 1);
        root = merge(res2.first, res1.second);
        return res2.second;
    }
    int getans(int l, int r) {
        pair<NP, NP> res1 = split(root, r), res2 = split(res1.first, l - 1);
        assert(res2.second);
        int ans = res2.second->maxsec;
        root = merge(merge(res2.first, res2.second), res1.second);
        return ans;
    }
} fhq;
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        FHQTreap::NP t = fhq.getNode(a);
        fhq.root = fhq.merge(fhq.root, t);
        assert(fhq.root->size == i);
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        char op;
        int x, y;
        cin >> op >> x;
        if (op == 'I') {
            cin >> y;
            fhq.insert(fhq.getNode(y), x);
        } else if (op == 'D') {
            fhq.erase(x);
        } else if (op == 'R') {
            cin >> y;
            FHQTreap::NP t = fhq.erase(x);
            t->x = y;
            t->update();
            fhq.insert(t, x);
        } else {
            cin >> y;
            cout << fhq.getans(x, y) << '\n';
        }
    }
    return 0;
}
