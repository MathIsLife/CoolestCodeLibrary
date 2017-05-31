/*
     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        HackerEarth - The Grass Type
        
        Category: Graph Theory
        
        Keys: DSU on Tree
        
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, w[N];
vector <int> g[N];
long long ans;

void dfs (int u, int from, map <int, int> &f) {
  ++f[w[u]];
  for (int v : g[u]) {
    if (v == from) continue;
    map <int, int> t;
    dfs(v, u, t);
    if (t.size() > f.size()) {
      f.swap(t);
    }
    for (auto it : t) {
      if (w[u] % it.first == 0 and f.find(w[u] / it.first) != f.end()) {
        ans += it.second * 1LL * f[w[u] / it.first];
      }
    }
    for (auto it : t) {
      f[it.first] += it.second;
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", w + i);
  }
  map <int, int> f;
  dfs(1, 1, f);
  printf("%lld\n", ans);
  return 0;
}

