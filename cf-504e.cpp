#include <bits/stdc++.h>
using namespace std;
constexpr int lgn = 21, maxn = 3e5 + 4, inf = 0x3f3f3f3f;
int logger[maxn] = {};
struct SA {
  vector<int> sa, rk, ht;
  typedef tuple<int, int, int> Key;
  vector<int> st[lgn];
  void init(const string& s) {
    sa.resize(s.size());
    rk.resize(s.size());
    ht.resize(s.size());
    const int lgs = logger[s.size()] + 1;
    vector<Key> t(s.size());
    vector<int> trk(s.size());
    for (int i = 0; i < s.size(); ++i)
      t[i] = Key(s[i], 0, i);
    for (int k = 0; k < lgs; ++k) {
      // cerr << "ST" << endl;
      sort(t.begin(), t.end());
      const int stp = (1 << k);
      for (int i = 0, scnt = -1; i < t.size(); ++i) {
        if (i == 0 || get<0>(t[i]) != get<0>(t[i - 1]) || get<1>(t[i]) != get<1>(t[i - 1]))
          trk[i] = ++scnt;
        else
          trk[i] = scnt;
        sa[i] = get<2>(t[i]);
        rk[get<2>(t[i])] = i;
        // cerr << trk[i] << endl;
        // cerr << string(s.begin() + sa[i], s.end()) << endl;
      }
      for (int i = 0; i < trk.size(); ++i)
        get<0>(t[i]) = trk[i];
      for (auto &[v1, v2, id] : t)
        v2 = ((id + stp < s.size()) ? trk[rk[id + stp]] : -1);
    }
    // cerr << "GU " << get<0>(t[0]) << ' ' << get<1>(t[0]) << ' ' << get<0>(t[1]) << ' ' << get<1>(t[1]) << endl;
    ht[0] = 0;
    for (int i = 0, k = 0; i < s.size(); ++i) {
      if (rk[i] == 0)
        continue;
      if (k)
        --k;
      while (i + k < s.size() && sa[rk[i] - 1] + k < s.size() && s[i + k] == s[sa[rk[i] - 1] + k])
        ++k;
      ht[rk[i]] = k;
    }
  }
  void prepare() {
    st[0].resize(ht.size());
    for (int i = 0; i < ht.size(); ++i)
      st[0][i] = ht[i];
    const int lgk = ceil(log2(ht.size()));
    assert(lgn <= lgn);
    for (int k = 1; k < lgk; ++k) {
      st[k].resize(ht.size(), inf);
      for (int i = 0; i < ht.size(); ++i) {
        if (i + (1 << k) < ht.size())
          st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        else
          st[k][i] = st[k - 1][i];
      }
    }
  }
  int getlcp(int x, int y) {
    if (x == y)
      return inf;
    // cerr << "gg "<< x << ' ' << y << endl;
    x = rk[x];
    y = rk[y];
    // cerr << "gu " << x << ' ' << y << endl;
    if (x > y)
      swap(x, y);
    ++x;
    const int len = logger[y - x + 1];
    // cerr << y << ' '<< st[len][y - (1 << len) + 1] << endl;
    // cerr << x << ' ' << st[len][x] << endl;
    return min(st[len][x], st[len][y - (1 << len) + 1]);
  }
} sa;
inline void prepare() {
  for (int i = 2; i < maxn; ++i)
    logger[i] = logger[i / 2] + 1;
}

struct Node {
  int par, dep, dfn, hson, top, sz;
  char c;
} nodes[maxn];
vector<int> verts[maxn];
void predfs(int u) {
  nodes[u].sz = 1;
  for (int v : verts[u]) {
    if (v == nodes[u].par)
      continue;
    nodes[v].dep = nodes[u].dep + 1;
    nodes[v].par = u;
    predfs(v);
    nodes[u].sz += nodes[v].sz;
    if (nodes[v].sz > nodes[nodes[u].hson].sz)
      nodes[u].hson = v;
  }
}
int clkc = 0;
void dfs(int u) {
  nodes[u].dfn = clkc++;
  cerr << u << ' ' << nodes[u].dfn << endl;
  if (nodes[u].hson) {
    nodes[nodes[u].hson].top = nodes[u].top;
    dfs(nodes[u].hson);
  }
  for (int v : verts[u]) {
    if (v == nodes[u].par || v == nodes[u].hson)
      continue;
    nodes[v].top = v;
    dfs(v);
  }
}

int N;
typedef pair<int, int> SubStr;
#define mirror(x) (2 * N - (x) - 1)
void gtop(int x, int y, vector<SubStr>& v) {
  vector<SubStr> vt;
  while (nodes[x].top != nodes[y].top) {
    if (nodes[nodes[x].top].dep > nodes[nodes[y].top].dep) {
      v.push_back(SubStr(mirror(nodes[x].dfn), mirror(nodes[nodes[x].top].dfn)));
      x = nodes[nodes[x].top].par;
    } else {
      vt.push_back(SubStr(nodes[nodes[y].top].dfn, nodes[y].dfn));
      y = nodes[nodes[y].top].par;
    }
  }
  if (nodes[x].dep > nodes[y].dep)
    v.push_back(SubStr(mirror(nodes[x].dfn), mirror(nodes[y].dfn)));
  else
    vt.push_back(SubStr(nodes[x].dfn, nodes[y].dfn));
  v.insert(v.end(), vt.begin(), vt.end());
  
}
#define len(s) ((s).second - (s).first + 1)
int match(const vector<SubStr>& a, const vector<SubStr>& b) {
  int p = 0, q = 0, cp = 0, cq = 0;
  int sum = 0;
  for (;p < a.size() && q < b.size();) {
    // cerr << "g" << ' ' << b[q].first << ' ' << b[q].second << "ff" << endl;
    const int l = min({sa.getlcp(a[p].first + cp, b[q].first + cq), len(a[p]) - cp, len(b[q]) - cq});
    // cerr << len(a[p]) - cp << ' ' << len(b[q]) << ' ' << l << endl;
    cp += l;
    cq += l;
    sum += l;
    if (cp == len(a[p]))
      ++p, cp = 0;
    else if (cq == len(b[q]))
      ++q, cq = 0;
    else
      break;
  }
  return sum;
}

inline void pack() {
  string str;
  str.resize(N);
  nodes[1].dep = nodes[1].top = 1;
  predfs(1);
  dfs(1);
  for (int i = 1; i <= N; ++i)
    str[nodes[i].dfn] = nodes[i].c;
  str += string(str.rbegin(), str.rend());
  sa.init(str);
  sa.prepare();
  // cerr << "FAKE" << endl;
}

int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> nodes[i].c;
  for (int i = 1; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  prepare();
  pack();
  int M;
  cin >> M;
  for (int i = 0; i < M; ++i) {
    int xi, yi, xii, yii;
    cin >> xi >> yi >> xii >> yii;
    vector<SubStr> a, b;
    gtop(xi, yi, a);
    // cerr << "PAY" << endl;
    gtop(xii, yii, b);
    cout << match(a, b) << '\n';
  }
  return 0;
}
