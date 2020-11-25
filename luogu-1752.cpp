
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Dish;
constexpr int maxn = 2e5;
int N, M, P, Q;
Dish dishes[maxn];
int rich[maxn], poor[maxn];
bool check(int weeks) {
  Dish rest[maxn];
  int tot = 0;
  for (int i = 0; i < P; ++i)
    for (int j = 0; j < weeks && tot < M && dishes[tot].first >= rich[i]; ++j)
      ++tot;
  copy(dishes + tot, dishes + M, rest);
  const int restot = M - tot;
  if (!restot)
    return true;
  sort(rest,rest + restot, [](Dish a, Dish b){ return a.second < b.second; });
  int k = 0;
  for (int i = 0; i < Q; ++i)
    for (int j = 0; j < weeks && k < restot && rest[k].second <= poor[i]; ++j)
      ++k;
  return (restot - k + weeks - 1) / weeks <= N - P - Q;
}
int main(int argc, char *argv[]){
  cin >> N >> M >> P >> Q;
  for (int i = 0; i < M; ++i)
    cin >> dishes[i].first >> dishes[i].second;
  sort(dishes, dishes + M, greater<Dish>());
  copy_n(istream_iterator<int>(cin), P, rich);
  sort(rich, rich + P, greater<int>());
  copy_n(istream_iterator<int>(cin), Q, poor);
  sort(poor, poor + Q);
  int L = 1, R = M, ans = M + 1;
  while (L <= R) {
    const int mid = (L + R) / 2;
    if (check(mid)) {
      R = mid - 1;
      ans = mid;
    } else {
      L = mid + 1;
    }
  }
  if (ans <= M)
    cout << ans << endl;
  else
    cout << -1 << endl;
  return 0;
}

