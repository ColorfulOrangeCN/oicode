#include <bits/stdc++.h>
using namespace std;
int cnt[26];
constexpr int mods = 1e9 + 7;
typedef long long inte;
inte qpow(inte x, int p) {
  inte res =  1;
  while (p) {
    if (p & 1)
      (res *= x) %= mods;
    (x *= x) %= mods;
    p >>= 1;
  }
  return res;
}
int main() {
  string str;
  cin >> str;
  for (char c : str)
    ++cnt[c - 'A'];
  int ans = 0, ansc = 0;
  for (int i = 0; i < 26; ++i) {
    if (cnt[i] > ans) {
      ans = cnt[i];
      ansc = 1;
    } else if (cnt[i] == ans) {
      ++ansc;
    }
  }
  cout << qpow(ansc, str.length()) << endl;
  return 0;
}
