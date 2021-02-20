#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 25000;
bool vis[maxn];
int primes[maxn], pc = 0;
int main() {
  for (int i = 2; i < maxn; ++i) {
    if (!vis[i]) {
      primes[pc++] = i;
      for (int j = 2; i * j < maxn; ++j)
        vis[i * j] = true;
    } 
  }
  int T;
  cin >> T;
  while (T--) {
    int d;
    cin >> d;
    int it = upper_bound(primes, primes + pc, d) - primes, it2 = lower_bound(primes, primes + pc, primes[it] + d) - primes;
    cout << (long long)(primes[it]) * primes[it2] << endl;
  }
  return 0;
}
