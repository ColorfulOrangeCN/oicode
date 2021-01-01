#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 2, disable = -1e6;
struct FHQTreap {
  struct Node {
    int v, pq;
    Node *l, *r;
    int sum, ls, rs, ms, modi, sz;
    bool rev;
    inline void pushdown() {
      if (rev) {
        rev = false;
        swap(l, r);
        swap(ls, rs);
      }
      if (modi != disable) {
        sum = modi * sz;
        ls = rs = ms = max(modi, sum);
      }
    }
    inline void maintain() {
      sum = ls = rs = ms = v;
      if (l) {
        sum += l->sum;
        ls = max(l->ls, l->sum + v);
        rs += max(l->rs, 0);
        ms = max(l->ms, v + max(l->rs, 0))
      }
    }
    Node() : l(nullptr), r(nullptr), sum(0), ls(0), rs(0), modi(disable), rev(0)  {}
  } nodes[maxn];
  vector<int> cache;
  FHQTreap() {
    cache.resize(maxn - 2);
    for (int i = 1; i < maxn; ++i)
      cache[i - 1] = i;
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
      
    }
  }
};

int main() {
  
  return 0;
}
