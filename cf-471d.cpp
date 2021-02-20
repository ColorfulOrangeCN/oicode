#include <bits/stdc++.h>
using namespace std;

inline vector<int> genZ(const vector<int>& s) {
  vector<int> z(s.size());
  z[0] = 0;
  int mp = 0;
  for (int i = 1; i < s.size(); ++i) {
    z[i] = max(0, min(mp + z[mp] - i - 1, z[i - mp]));
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] > mp + z[mp])
      mp = i;
    // cerr << i << ' ' << z[i] << endl;
  }
  return z;
}

int main() {
  int N, W;
  cin >> N >> W;
  vector<int> A, B;
  copy_n(istream_iterator<int>(cin), N, back_inserter(A));
  copy_n(istream_iterator<int>(cin), W, back_inserter(B));
  if (W == 1) {
    cout << N << endl;
    return 0;
  }
  for (int i = 1; i < A.size(); ++i)
    A[i - 1] -= A[i];
  A.pop_back();
  for (int i = 1; i < B.size(); ++i)
    B[i - 1] -= B[i];
  B.pop_back();
  // copy(A.begin(), A.end(), ostream_iterator<int>(cerr, " "));
  // cerr << endl;
  // copy(B.begin(), B.end(), ostream_iterator<int>(cerr, " "));
  // cerr << endl;
  vector<int> s(B);
  s.push_back(1e9 + 1);
  const int v = s.size();
  s.insert(s.end(), A.begin(), A.end());
  auto z = genZ(s);
  int ans = 0;
  // cerr << B.size() << endl;
  for (int i = 0; i < A.size(); ++i)
    if (z[v + i] >= B.size())
      ++ans;
  cout << ans << endl;
  return 0;
}
