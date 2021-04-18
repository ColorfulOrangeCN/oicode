#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
constexpr int maxn = 1e5 + 4;
constexpr int maxm = 204;
pair<int, int> times[maxn];
typedef long long inte;
inte f[maxn][maxm];
inline inte& letmin(inte& l, inte r) {
  return (l > r) ? l = r : l;
}
template<typename T>
inline T& letmax(T& l, T r) {
  return (l < r) ? l = r : l;
}
vector<pair<int, int>> ins[maxn], ers[maxn];
int main() {
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 1; i <= K; ++i) {
    int s, t, d, w;
    cin >> s >> t >> d >> w;
    ins[s].push_back(make_pair(w, min(d, N)));
    ers[t + 1].push_back(make_pair(w, min(d, N)));
  }
  multiset<pair<int, int>> upd;
  for (int i = 1; i <= N; ++i) {
    for (auto u : ins[i])
      upd.insert(u);
    for (auto u : ers[i])
      upd.erase(upd.find(u));
    if (upd.empty())
      times[i] = make_pair(0, i);
    else
      times[i] = *--upd.end();
  }
  memset(f, 0x3f, sizeof(f));
  f[1][0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j <= M; ++j) {
      if (j < M)
        letmin(f[i + 1][j + 1], f[i][j]);
      letmin(f[times[i].second + 1][j], f[i][j] + times[i].first);
    }
  }
  inte ans = 0x3f3f3f3f3f3f3f3f;
  for (int j = 0; j <= M; ++j)
    letmin(ans, f[N + 1][j]);
  cout << ans << endl;
  return 0;
}
