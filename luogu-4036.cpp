// #define NDEBUG
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 5;
typedef unsigned long long Data;
constexpr Data base = 1145141;
Data pp[maxn];
struct FHQTreap {
  struct Node {
    int v, pq;
    Node *l, *r;
    int sz;
    Data dat;
    inline void maintain() {
      sz = 1;
      if (l) {
        dat = l->dat + pp[l->sz] * v;
        sz += l->sz;
      } else {
        dat = v;
      }
      if (r) {
        dat += r->dat * pp[sz];
        sz += r->sz;
      }
    }
    Node() : l(nullptr), r(nullptr){}
  } nodes[maxn];
  Node *cache[maxn];
  int ccnt;
  FHQTreap() {
    ccnt = maxn;
    for (int i = 0; i < maxn; ++i)
      cache[i] = nodes + i;
  }
  Node* crtnd(int v) {
    Node *ptr = cache[--ccnt];
    *ptr = Node();
    ptr->v = v;
    ptr->maintain();
    ptr->pq = rand();
    return ptr;
  }
  inline void del(Node *ptr) {
    if (!ptr)
      return;
    cache[ccnt++] = ptr;
    del(ptr->l);
    del(ptr->r);
  }
  inline int nSize(Node* ptr) {
    if (ptr == nullptr)
      return 0;
    else
      return ptr->sz;
  }
  Node* merge(Node *l, Node *r) {
    if (l == nullptr)
      return r;
    if (r == nullptr)
      return l;
    assert(l && r);
    if (l->pq > r->pq) {
      l->r = merge(l->r, r);
      l->maintain();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->maintain();
      return r;
    }
  }
  pair<Node*, Node*> split(Node *rt, int v) {
    if (rt == nullptr)
      return make_pair(nullptr, nullptr);
    if (nSize(rt->l) < v - 1) {
      auto pi = split(rt->r, v - nSize(rt->l) - 1);
      rt->r = pi.first;
      rt->maintain();
      return make_pair(rt, pi.second);
    } else {
      auto pi = split(rt->l, v);
      rt->l = pi.second;
      rt->maintain();
      return make_pair(pi.first, rt);
    }
  }
  Node* rt;
  inline Node* insert(Node *ptr, int id) {
    const auto pi = split(rt, id);
    rt = merge(pi.first, merge(ptr, pi.second));
    return ptr;
  }
  inline Node* erase(int l) {
    const auto pi1 = split(rt, l), pi2 = split(pi1.second, 2);
    rt = merge(pi1.first, pi2.second);
    return pi2.first;
  }
  inline Data query(int l, int tot) {
    if (!tot)
      return 0;
    const auto pi1 = split(rt, l), pi2 = split(pi1.second, (tot + 1));
    Data t = pi2.first->dat;
    rt = merge(pi1.first, merge(pi2.first, pi2.second));
    return t;
  }
  inline void modify(int l, int v) {
    const auto pi1 = split(rt, l), pi2 = split(pi1.second, 2);
    pi2.first->v = v;
    pi2.first->maintain();
    rt = merge(pi1.first, merge(pi2.first, pi2.second));
  }
} tr;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  srand(1145141);
  pp[0] = 1;
  for (int i = 1; i < maxn; ++i)
    pp[i] = pp[i - 1] * base;
  string str;
  cin >> str;
  for (int i = 0; i < str.length(); ++i)
    tr.insert(tr.crtnd(str[i] - 'a' + 1), i + 1);
  int N;
  cin >> N;
  while (N--) {
    char op;
    int x;
    cin >> op >> x;
    if (op == 'Q') {
      int y;
      cin >> y;
      if (x > y)
        swap(x, y);
      // cerr << tr.rt->sz << endl;
      int L = 0, R = tr.rt->sz - y + 1, ans = 0;
      while (L <= R) {
        const int mid = (L + R) / 2;
        if (tr.query(x, mid) == tr.query(y, mid)) {
          L = mid + 1;
          ans = mid;
        } else {
          R = mid - 1;
        }
      }
      cout << ans << '\n';
    } else {
      char c;
      cin >> c;
      if (op == 'R')
        tr.modify(x, c - 'a' + 1);
      else
        tr.insert(tr.crtnd(c - 'a' + 1), x + 1);
    }
  }
  return 0;
}
