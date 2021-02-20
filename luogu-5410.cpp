#include <bits/stdc++.h>
using namespace std;

vector<int> genZ(const string& s) {
  vector<int> z(s.length());
  z[0] = 0;
  int mr = 0, mp = 0;
  for (int i = 1; i < s.length(); ++i) {
    z[i] = max(0, min(z[i - mp], mr - i + 1));
    while (i + z[i] < s.length() && s[i + z[i]] == s[z[i]])
      ++z[i];
    if (i + z[i] - 1 > mr) {
      mp = i;
      mr = i + z[i] - 1;
    }
  }
  z[0] = s.length();
  return z;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string a, b;
  cin >> a >> b;
  vector<int> bz = genZ(b);
  long long ans = 0;
  for (int i = 0; i < bz.size(); ++i)
    ans ^= (long long)(i + 1) * (bz[i] + 1);
  cout << ans << endl;
  ans = 0;
  bz = genZ(b + '*' + a);
  for (int i = b.length() + 1; i < bz.size(); ++i)
    ans ^= (long long)(i - b.length()) * (bz[i] + 1);
  cout << ans << endl;
  return 0;
}
