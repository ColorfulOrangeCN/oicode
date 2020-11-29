#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 0x3f3f3f3f, maxn = 1e5 + 1, lga = 30;
struct Node {
  int ch[2];
  int vis;
} nodes[maxn * lga];
int a[maxn];
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> a[i];
  
  return 0;
}
