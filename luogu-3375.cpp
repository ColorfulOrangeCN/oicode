#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
char pat[maxn], txt[maxn];
int jmp[maxn];
int main() {
  cin >> txt >> pat;
  const int pn = strlen(pat), tn = strlen(txt);
  for (int i = 1, k = 0; i <= pn; ++i) {
    while (k && pat[k] != pat[i])
      k = jmp[k - 1];
    if (pat[k] == pat[i]) {
      jmp[i] = ++k;
    }
  }
  for (int i = 0; i <= pn; ++i)
    cerr << jmp[i] << '\n';
  for (int i = 0, k = 0; i < tn; ++i) {
    while (k && pat[k] != txt[i])
      k = jmp[k - 1];
    if (pat[k] == txt[i])
      ++k;
    // cerr << k << '\n';
    if (k >= pn)
      cout << i - pn + 2 << '\n';
  }
  for (int i = 0;)
  return 0;
}
