/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        SGU 507 - Treediff
        
        Category: Graph Theory
        
        Keys: DSU on Tree
        
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50010;
const int INF = int((1LL << 31) - 1LL);

vector <int> g[N];
int n, m, w[N], ans[N];

void dfs (int u, set <int> &f) {
  ans[u] = INF;
  if (u > n - m) {
    f.insert(w[u]);
    return;
  }
  for (int v : g[u]) {
    set <int> t;
    dfs(v, t);
    ans[u] = min(ans[u], ans[v]);
    if (t.size() > f.size()) f.swap(t);
    for (int x : t) {
      if (ans[u] > 0) {
        if (f.count(x)) {
          ans[u] = 0;
        }
      }
      f.insert(x);
      if (ans[u] == 0) {
        continue;
      }
      auto it = f.find(x);
      if (it != f.begin()) {
        auto other = it;
        --other;
        ans[u] = min(ans[u], abs(*it - *other));
      }
      if (it != --f.end()) {
        auto other = it;
        ++other;
        ans[u] = min(ans[u], abs(*it - *other));
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 2; i <= n; ++i) {
    int par;
    scanf("%d", &par);
    g[par].push_back(i);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", w + n - m + i);
  }
  set <int> f;
  dfs(1, f);
  for (int i = 1; i <= n - m; ++i) {
    printf("%d ", ans[i]);
  }
  puts("");
  return 0;
}

