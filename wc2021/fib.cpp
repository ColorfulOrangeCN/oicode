#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Sta;
typedef long long inte;
map<Sta, inte> mp;
int N, M;
inte dfs(Sta s) {
  map<Sta, inte>::iterator it = mp.find(s);
  if (s.second == 0)
    return 1;
  else if (s.first == 0)
    return 0;
  if (it != mp.end()) {
    if (it->second == -1)
      throw exception();
    else
      return it->second;
  }
  mp.insert(make_pair(s, -1ll));
  it = mp.find(s);
  it->second = dfs(Sta(s.second, (s.first + s.second) % M)) + 1;
  return it->second;
}
int main() {
  ifstream fin("fib.in");
  ofstream fout("fib.out");
#define cin fin
#define cout fout
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    try {
      int a, b;
      cin >> a >> b;
      cout << dfs(Sta(a, b)) << endl;
    } catch(...) {
      cout << "-1\n";
    }
  }
  return 0;
}
