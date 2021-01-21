#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
bool vis[maxn];
int prm[maxn], phi[maxn], pcnt = 0;
inline void predo() {
  phi[1] = 1;
  for (int i = 2; i < maxn; ++i) {
    if (!vis[i]) {
      prm[++pcnt] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= pcnt && i * prm[j] < maxn; ++j) {
      vis[i * prm[j]] = true;
      if (i % prm[j] == 0) {
        phi[i * prm[j]] = phi[i] * prm[j];
        break;
      }
      phi[i * prm[j]] = phi[i] * (prm[j] - 1);
    }
  }
}

typedef long long inte;
inline int fpow(inte a, int p, int m) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= m;
    (a *= a) %= m;
    p >>= 1;
  }
  return res;
}
inline bool exist(int n) {
  if (n == 2 || n == 4)
    return true;
  if (n % 2 == 0)
    n /= 2;
  for (int i = 1; i <= pcnt; ++i) {
    if (n % prm[i] == 0) {
      while (n % prm[i] == 0)
        n /= prm[i];
      return n == 1;
    }
  }
  return false;
}

inline vector<int> getdiv(int n) {
  vector<int> divor;
  for (int i = 1; prm[i] <= n && i <= pcnt; ++i) {
    // cerr << n << ' ' << i << endl;
    if (n % prm[i] == 0) {
      divor.push_back(prm[i]);
      // cerr << prm[i] << endl;
      do {
        n /= prm[i];
      } while (n % prm[i] == 0);
    }
  }
  return divor;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  predo();
  int T;
  cin >> T;
  while (T--) {
    int n, d;
    cin >> n >> d;
    if (!exist(n)) {
      cout << "0\n\n";
      continue;
    }
    auto divor = getdiv(phi[n]);
    // cerr << phi[n] << endl;
    int g;
    for (g = 1;; ++g) {
      bool isok = true;
      if (__gcd(g, n) != 1)
        continue;
      for (int j : divor)
        isok &= (fpow(g, phi[n] / j, n) != 1);
      if (isok)
        break;
    }
    vector<int> ans;
    inte cg = g;
    cout << phi[phi[n]] << '\n';
    for (int s = 1; ans.size() < phi[phi[n]]; ++s) {
      if (__gcd(s, phi[n]) == 1)
        ans.push_back(cg);
      (cg *= g) %= n;
    }
    sort(ans.begin(), ans.end());
    for (int k = d; k <= ans.size(); k += d)
      cout << ans[k - 1] << ' ';
    cout << '\n';
  }
  return 0;
}
