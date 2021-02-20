#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
int main() {
  inte n;
  cin >> n;
  inte tmp = 0;
  vector<int> vec;
  inte ans = 0;
  if (n & 1)
    vec.push_back(0);
  for (int i = 1; i <= 50; ++i) {
    tmp *= 2;
    tmp += (1ll << (i - 1));
    if (n & (1ll << (i))) {
      vec.push_back(i);
      ans += tmp;
    }
  }
  reverse(vec.begin(), vec.end());
  // cout << ans << endl;
  for (int i = 0; i < vec.size() - 1; ++i)
    ans += (1ll << vec[i]);
  cout << ans << endl;
  return 0;
}
