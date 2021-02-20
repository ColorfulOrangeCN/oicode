#include <bits/stdc++.h>
using namespace std;
constexpr int num = 26, mcc = (1 << (num - 2));
int f[mcc];
inline int lowbit(int x) {return x & -x;}
int main() {
  int n;
  cin >> n;
  constexpr int fil = mcc - 1;
  for (int i = 0; i < n; ++i) {
    int a = 0;
    string str;
    cin >> str;
    for (char c : str)
      if (c <= 'x')
        a |= (1 << (c - 'a'));
    ++f[fil ^ a];
  }
  for (int i = fil; i > 0; --i)
    f[i ^ lowbit(i)] += f[i];
  int ans = 0;
  for (int i = 0; i < mcc; ++i)
    ans ^= (n - f[i]) * (n - f[i]);
  cout << ans << endl;
  return 0;
}
