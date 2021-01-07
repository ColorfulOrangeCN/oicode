#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e4 + 2;
typedef long long inte;

inline inte fpow(inte x, int p, inte mods) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= x) %= mods;
    (x *= x) %= mods;
    p >>= 1;
  }
}
