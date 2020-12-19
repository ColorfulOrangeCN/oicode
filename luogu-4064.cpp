#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
int N, M, K, da, A[maxn];
struct BIT {
  int c[maxn];
  inline int lowbit(int x) {return x & -x;}
  void clear() {
    fill(c, c + N + 1, 0);
  }
  void add(int x, int v) {
    while (x <= N) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  int query(int x) {
    int res = 0;
    while (x) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;
  }
  void addR(int l, int r, int v) {
    add(l, v);
    add(r + 1, -v);
  }
} bt;
typedef pair<int, int> Meta;
struct Comp {
  bool operator() (Meta a, Meta b) {
    return a.second < b.second;
  }
};
Meta asks[maxn];
bool check(int bound) {
  bt.clear();
  for (int i = 1; i <= N; ++i)
    if (A[i] < bound)
      bt.addR(i, i, (bound - A[i] + da - 1) / da);
  priority_queue<Meta, vector<Meta>, Comp> q;
  int L = 1;
  int cnt = K;
  for (int i = 1; i <= N; ++i) {
    while (L <= M && asks[L].first <= i)
      q.push(asks[L++]);
    while (bt.query(i) > 0) {
      if (q.empty() || !cnt)
        return false;
      Meta t = q.top();
      --cnt;
      bt.addR(t.first, t.second, -1);
      q.pop();
    }
  }
  return true;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> N >> M >> K >> da;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    for (int i = 1; i <= M; ++i)
      cin >> asks[i].first >> asks[i].second;
    sort(asks + 1, asks + M + 1);
    int L = 1, R = 2e8, ans = 0;
    while (L <= R) {
      const int mid = (L + R) / 2;
      if (check(mid)) {
        L = mid + 1;
        ans = mid;
      } else {
        R = mid - 1;
      }
    }
    cout << ans << endl; 
  }
  return 0;
}
