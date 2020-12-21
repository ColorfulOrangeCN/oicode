#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
struct BInt {
  long long a, b;
};
BInt all {0, 1}, ans[maxn];
#define int long long 
constexpr long long base = 1e15;
inline BInt operator + (BInt a, BInt b) {
  return BInt{a.a + b.a + (a.b + b.b) / base, (a.b + b.b) % base};
}
inline BInt operator * (BInt a, int b) {
  return BInt{a.a * b + (a.b * b) / base, (a.b * b) % base};
}
inline BInt operator / (BInt a, int b) {
  return BInt{a.a / b, (a.a % b * base + a.b) / b};
}
inline int operator % (BInt a, int b) {
  return (a.a % b * base + a.b) % b;
}
inline ostream& operator << (ostream& out, BInt v) {
  if (v.a)
    return out << setfill('0') << v.a << setw(15) << v.b;
  else
    return out << v.b;
}
int N, M;
vector<int> verts[maxn];
int in[maxn];
signed main(signed argc, char *argv[])
{
  for (int i = 1; i <= 11; ++i)
    all = all * 60;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int c;
    cin >> c;
    for (int j = 1; j <= c; ++j) {
      int v;
      cin >> v;
      verts[i].push_back(v);
      ++in[v];
    }
  }
  queue<int> q;
  for (int i = 1; i <= M; ++i)
    q.push(i), ans[i] = all;
  while (!q.empty()) {
    const int u = q.front();
    q.pop();
    for (int v : verts[u]) {
      ans[v] = ans[v] + ans[u] / verts[u].size();
      if (!--in[v])
        q.push(v);
    }
  }
  for (int i = 1; i <= N; ++i) {
    if (verts[i].size())
      continue;
    BInt deno = all;
    while (deno % 2 == 0 && ans[i] % 2 == 0)
      deno = deno / 2, ans[i] = ans[i] / 2;
    while (deno % 3 == 0 && ans[i] % 3 == 0)
      deno = deno / 3, ans[i] = ans[i] / 3;
    while (deno % 5 == 0 && ans[i] % 5 == 0)
      deno = deno / 5, ans[i] = ans[i] / 5;
    cout << ans[i] << ' ' << deno << '\n';
  }
  return 0;
}
