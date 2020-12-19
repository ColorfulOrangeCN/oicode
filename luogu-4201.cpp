#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 1, maxans = 10;
typedef long long inte;
inte mods;
int N, M;
vector<int> verts[maxn];
struct DP {
  inte v;
  bool able;
} f[maxn][maxans][3], sd[maxn][maxans], all[maxn][maxans];
DP operator * (DP a, DP b) {return DP{a.v * b.v % mods, a.able && b.able};}
DP operator + (DP a, DP b) {return DP{(a.v + b.v) % mods, a.able || b.able};}
void dp(int u, int la) {
  for (int i = 0; i < maxans; ++i)
    f[u][i][0] = DP{1, 1};
  for (int v : verts[u]) {
    if (v == la)
      continue;
    dp(v, u);
    f[u][0][2] = f[u][0][1] * sd[v][0];
    f[u][0][1] = f[u][0][0] * sd[v][0];
    f[u][0][0] = DP{0, 0};
    for (int k = 1; k < maxans; ++k) {
      f[u][k][2] = (f[u][k][1] * sd[v][k] + f[u][k][2] * all[v][k - 1]);
      f[u][k][1] = (f[u][k][0] * sd[v][k] + f[u][k][1] * all[v][k - 1]);
      f[u][k][0] = f[u][k][0] * all[v][k - 1];
    }
  }
  for (int k = 0; k < maxans; ++k) {
    sd[u][k] = (f[u][k][0] + f[u][k][1]);
    all[u][k] = (sd[u][k] + f[u][k][2]);
  } 
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M >> mods;
  if (M < N - 1) {
    cout << "-1\n-1";
    return 0;
  }
  for (int i = 1; i <= M; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  dp(1, 0);
  // cerr << f[1][1][0] << endl;
  for (int k = 0; k < maxans; ++k) {
    if (all[1][k].able) {
      cout << k << '\n' << all[1][k].v;
      break;
    }
  }
  return 0;
}
