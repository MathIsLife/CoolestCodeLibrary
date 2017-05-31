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

const int N = 123456;

int n, c[N];
vector <int> g[N];
long long ans[N];

void dfs (int u, int from, map <int, int> &f) {
  for (int v : g[u]) {
    if (v == from) continue;
    map <int, int> h;
    dfs(v, u, h);
    if (h.size() > f.size()) f.swap(h);
    for (auto it : h) {
      f[it.first] += it.second;
    }
  }
  ++f[c[u]];
  int best = 0;
  for (auto it : f) {
    best = max(best, it.second);
  }
  ans[u] = 0;
  for (auto it : f) {
    if (it.second == best) {
      ans[u] += 1LL * it.first;
    }
  }
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
  map <int, int> f;
  dfs(1, 1, f);
  for (int i = 1; i <= n; ++i) {
    printf("%d ", ans[i]);
  }
  puts("");
  return 0;
}

