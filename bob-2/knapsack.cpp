#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
int cnt[maxn];
bitset<maxn> f;
int main() {
  ifstream fin("knapsack.in");
  ofstream fout("knapsack.out");
#define cin fin
#define cout fout
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    int w;
    cin >> w;
    ++cnt[w];
  }
  f[0] = true;
  for (int i = 1; i <= 100; ++i) {
    int k = 1;
    while (k <= cnt[i]) {
      f |= (f << (i * k));
      cnt[i] -= k;
      k <<= 1;
    }
    f |= (f << (i * cnt[i]));
  }
  int ans = 0;
  for (int j = M; j >= 0; --j) {
    if (f[j]) {
      ans = j;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}
