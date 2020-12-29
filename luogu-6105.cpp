#include <bits/stdc++.h>
using namespace std;

multiset<int, greater<int>> num, cho;
int C;
inline int findBest(int x) {
  auto t = num.upper_bound(C - x);
  if (t == num.end())
    return -1;
  else
    return *t;
}
inline int findInBest(int x) {
  auto t = num.upper_bound(C - x);
  if (t == num.end())
    return -1;
  if (*t == x)
    ++t;
  if (t == num.end())
    return -1;
  return *t;
}

inline void updateInsert(int x) {
  const int mat = findBest(x);
  if (mat == -1)
    return;
  const int mmat = findInBest(mat);
  if (mmat < x) {
    if (mmat != -1 && mmat < x && findInBest(mmat) == mat)
      cho.erase(cho.find(mat + mmat));
    cho.insert(x + mat);
  }
}

inline void updateErase(int x) {
  num.erase(num.find(x));
  const int mat = findBest(x);
  if (mat == -1)
    return;
  const int mmat = findInBest(mat);
  if (mmat < x) {
    if (mmat != -1 && mmat < x && findInBest(mmat) == mat)
      cho.insert(mat + mmat);
    cho.erase(cho.find(x + mat));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N >> C;
  int lans = 0;
  while(N--) {
    int opt, x;
    cin >> opt >> x;
    x ^= lans;
    x %= C;
    // cerr << x << endl;
    if (opt == 1) {
      updateInsert(x);
      num.insert(x);
    } else {
      updateErase(x);
    }
    if (num.size() > 1) {
      int ans = (*num.begin() +  *(++num.begin())) % C;
      // cerr << x << ' ' <<  ans << endl;
      if (!cho.empty())
        ans = max(ans, *cho.begin());
      cout << ans << '\n';
      lans = ans;
    } else {
      cout << "EE\n";
      lans = 0;
    }
  }
  return 0;
}
