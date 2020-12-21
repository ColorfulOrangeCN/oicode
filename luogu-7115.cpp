#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 51;
typedef pair<int, int> Ball;
typedef vector<Ball> Pillar;
Pillar bob[maxn];
typedef pair<int, int> Option;
vector<Option> ops;
inline void pp(int a, int b, int c = 1) {
  for (int i = 1; i <= c; ++i) {
    ops.push_back(Option(a, b));
    bob[b].push_back(bob[a].back());
    bob[a].pop_back();
  }
}
void filter(int a, int t0, int t1) {
  while (!bob[a].empty()) {
    if (!bob[a].back().second)
      pp(a, t0);
    else
      pp(a, t1);
  }
}
int N, M;
void solve(int l, int r, int ca) {
  if (l == r)
    return;
  const int mid = (l + r) / 2;
  int p = l;
  int q = mid + 1;
  while (p <= mid && q <= r) {
    int c0 = 0, c1 = 0;
    auto turned =
      [&](int p) {
        for (auto& p : bob[p]) {
          if (p.first <= mid) {
            if (c0 < M)
              p.second = 0, ++c0;
            else
              p.second = 1;
          } else {
            if (c1 < M)
              p.second = 1, ++c1;
            else
              p.second = 0;
          }
        }
      };
    turned(p), turned(q);
    int s = 0;
    for (auto& t : bob[p])
      s += (t.second == 0);
    pp(q, ca, s);
    filter(p, q, ca);
    pp(q, p, s);
    pp(ca, p, M - s);
    pp(q, ca, M - s);
    pp(p, q, M - s);
    filter(ca, p, q);
    if (c0 == M)
      ++p;
    if (c1 == M)
      ++q;
  }
  solve(l, mid, ca);
  solve(mid + 1, r, ca);
}
int main() {
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int p;
      cin >> p;
      bob[i].push_back(Ball(p, 0));
    }
  }
  solve(1, N, N + 1);
  cout << ops.size() << '\n';
  for (auto &p : ops)
    cout << p.first << ' ' << p.second << '\n';
  return 0;
}
