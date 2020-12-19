#include <bits/stdc++.h>
using namespace std;
constexpr int maxv = 1e6 + 1, maxn = 10001;
int cnt[maxv];
int md[maxn];
int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int a;
    cin >> a;
    ++cnt[a];
  }
  for (int i = 1; i < maxv; ++i) {
    int c = 0;
    for (int j = i; j < maxv; j += i)
      c += cnt[j];
    md[c] = max(md[c], i);
  }
  for (int j = N - 1; j; --j)
    md[j] = max(md[j], md[j + 1]);
  for (int i = 1; i <= N; ++i)
    cout << md[i] << '\n';
}
