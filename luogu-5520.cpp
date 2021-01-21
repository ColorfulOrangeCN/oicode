#include <bits/stdc++.h>
typedef long long inte;
using namespace std;

inte ans = 1, type, n, m, p;

int main() {
  cin >> type >> n >> m >> p;
  for (int i = n - m + 1; i >= n - 2 * m + 2; i--)
    ans = (ans * i) % p;
  cout << ans << endl;
  return 0;
}
