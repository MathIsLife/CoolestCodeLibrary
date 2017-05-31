/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 600E - Lomsat Gelral
        
        Category: Graph Theory
        
        Keys: DSU on Tree
        
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 123456;
const int INF = 1e9 + 10;

ll ans[N];
int n, c[N];
vector <int> g[N];

void dfs (int u, int from, map <int, ll> &f) {
  for (int v : g[u]) {
    if (v == from) continue;
    map <int, ll> h;
    dfs(v, u, h);
    if (h.size() > f.size()) f.swap(h);
    for (auto it : h) {
      if (it.first >= INF) {
        continue;
      }
      f[it.first] += it.second;
      if (f[it.first] > f[INF]) {
        f[INF] = f[it.first];
        f[INF + 1] = it.first;
      } else if (f[it.first] == f[INF]) {
        f[INF + 1] += it.first;
      }
    }
  }
  ++f[c[u]];
  if (f[c[u]] > f[INF]) {
    f[INF] = f[c[u]];
    f[INF + 1] = c[u];
  } else if (f[c[u]] == f[INF]) {
    f[INF + 1] += c[u];
  }
  ans[u] = f[INF + 1];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", c + i);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  map <int, ll> f;
  dfs(1, 1, f);
  for (int i = 1; i <= n; ++i) {
    printf("%lld ", ans[i]);
  }
  puts("");
  return 0;
}

