#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 4;
int A[maxn];
vector<int> v[maxn];
int main() {
  srand(time(NULL));
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    v[A[i]].push_back(i);
  }
  for (int i = 0; i < M; ++i) {
    int l, r, k = 0;
    cin >> l >> r;
    for (int j = 0; j < 10; ++j) {
      const int t = l + rand() % (r - l + 1);
      const int s = upper_bound(v[A[t]].begin(), v[A[t]].end(), r) - lower_bound(v[A[t]].begin(), v[A[t]].end(), l);
      // cerr << A[t] << ' ' << s << endl;
      if (s * 2 > r - l + 1) {
        k = A[t];
        break;
      }
    }
    cout << k << endl;
  }
  return 0;
}
