// #define NDEBUG
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 2, disable = -1e6;
struct FHQTreap {
  struct Data {
    int sum, ls, rs, ms;
  };
  inline static Data vdata(int v) {
    return Data{v, v, v, v};
  }
  inline static Data connect(const Data& l, const Data& r) {
    return Data{l.sum + r.sum, max(l.ls, l.sum + r.ls), max(r.rs, r.sum + l.rs), max(l.rs + r.ls, max(l.ms, r.ms))};
  }
  struct Node {
    int v, pq;
    Node *l, *r;
    int modi, sz;
    Data dat;
    bool rev;
    inline void pushdown() {
      if (rev) {
        rev = false;
        if (l)
          l->rev = !l->rev;
        if (r)
          r->rev = !r->rev;
        swap(l, r);
        swap(dat.ls, dat.rs);
      }
      if (modi != disable) {
        v = modi;
        dat.sum = modi * sz;
        dat.ls = dat.rs = dat.ms = max(modi, dat.sum);
        if (l)
          l->modi = modi;
        if (r)
          r->modi = modi;
        modi = disable;
      }
    }
    inline void maintain() {
      dat = vdata(v);
      sz = 1;
      assert(modi == disable);
      if (l) {
        l->pushdown();
        dat = connect(l->dat, dat);
        sz += l->sz;
      }
      if (r) {
        r->pushdown();
        dat = connect(dat, r->dat);
        sz += r->sz;
      }
    }
    Node() : l(nullptr), r(nullptr), modi(disable), rev(0){}
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
    ptr->dat = vdata(v);
    ptr->sz = 1;
    ptr->pq = rand();
    ptr->v = v;
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
      l->pushdown();
      l->r = merge(l->r, r);
      l->maintain();
      return l;
    } else {
      r->pushdown();
      r->l = merge(l, r->l);
      r->maintain();
      return r;
    }
  }
  pair<Node*, Node*> split(Node *rt, int v) {
    if (rt == nullptr)
      return make_pair(nullptr, nullptr);
    rt->pushdown();
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
  Node* build(const int* a, int l, int r) {
    if (l == r) {
      return crtnd(a[l]);
    }
    else {
      const int mid = (l + r) / 2;
      return merge(build(a, l, mid), build(a, mid + 1, r));
    }
  }
  inline Node* insert(Node *ptr, int id) {
    const auto pi = split(rt, id);
    rt = merge(pi.first, merge(ptr, pi.second));
    return ptr;
  }
  inline Node* erase(int l, int tot) {
    const auto pi1 = split(rt, l), pi2 = split(pi1.second, tot + 1);
    rt = merge(pi1.first, pi2.second);
    return pi2.first;
  }
  template<typename Func>
  inline void perform(int l, int tot, const Func& f) {
    if (!tot)
      return;
    const auto pi1 = split(rt, l), pi2 = split(pi1.second, (tot + 1));
    f(pi2.first);
    rt = merge(pi1.first, merge(pi2.first, pi2.second));
  }
} tr;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  srand(1145141);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int a;
    cin >> a;
    tr.insert(tr.crtnd(a), i);
  }
  for (int i = 0; i < M; ++i) {
    static char str[10];
    cin >> str;
    if (str[0] == 'I') {
      int p, tot;
      cin >> p >> tot;
      static int a[maxn];
      copy_n(istream_iterator<int>(cin), tot, a + 1);
      tr.insert(tr.build(a, 1, tot), p + 1);
    } else if (str[0] == 'D') {
      int p, t;
      cin >> p >> t;
      tr.del(tr.erase(p, t));
    } else if (str[0] == 'M' && str[2] == 'K') {
      int l, tot, v;
      cin >> l >> tot >> v;
      tr.perform(l, tot, [v](FHQTreap::Node* ptr){ptr->modi = v;});
    } else if (str[0] == 'M' && str[2] == 'X') {
      int l, tot;
      cin >> l >> tot;
      if (tot == 0)
        cout << "0\n";
      tr.perform(l, tot, [](FHQTreap::Node* ptr){cout << ptr->dat.ms << '\n';});
    } else if (str[0] == 'R') {
      int l, tot;
      cin >> l >> tot;
      tr.perform(l, tot, [](FHQTreap::Node* ptr){ptr->rev = true;});
    } else if (str[0] == 'G' && str[3] == '-') {
      int l, tot;
      cin >> l >> tot;
      if (tot == 0)
        cout << "0\n";
      tr.perform(l, tot, [](FHQTreap::Node* ptr){cout << ptr->dat.sum << '\n';});
    } else if (str[0] == 'G') {
      int x;
      cin >> x;
      tr.perform(x, 1, [](FHQTreap::Node* ptr){cout << ptr->dat.sum << '\n';});
    }
  }
  cerr << clock() << endl;
  return 0;
}
