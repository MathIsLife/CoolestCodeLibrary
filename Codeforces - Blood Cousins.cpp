/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 208E - Blood Cousins
        
        Category: Graph Theory
        
        Keys: DSU on Tree, Binary Jump
        
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> data;

#define x first
#define y second

const int LG = 20;
const int N = 100010;

int par[N][LG];
int n, m, h[N];
vector <int> g[N];
vector <int> roots;
vector <data> q[N];
int root, ans[N];

void go (int u, int deep = 1) {
  h[u] = deep;
  for (int v : g[u]) {
    par[v][0] = u;
    go(v, deep + 1);
  }
}

void dfs (int u, map <int, int> &f) {
  for (int v : g[u]) {
    map <int, int> t;
    dfs(v, t);
    if (t.size() > f.size()) {
      f.swap(t);
    }
    for (auto it : t) {
      f[it.x] += it.y;
    }
  }
  ++f[h[u]];
  for (auto it : q[u]) {
    ans[it.y] = f[it.x] - 1;
  }
}

int ancestor (int u, int k) {
  for (int i = LG - 1; i >= 0; --i) {
    if (k >= (1 << i)) {
      k -= (1 << i);
      u = par[u][i];
    }
  }
  return u;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int par;
    scanf("%d", &par);
    if (par) {
      g[par].push_back(i);
    } else {
      roots.push_back(i);
    }
  }
  memset(par, -1, sizeof par);
  for (int root : roots) {
    go(root);
  }
  for (int i = 1; i < LG; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (par[j][i - 1] != -1) {
        par[j][i] = par[par[j][i - 1]][i - 1];
      }
    }
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int u, k;
    scanf("%d %d", &u, &k);
    if (h[u] <= k) {
      continue;
    }
    int v = ancestor(u, k); 
    q[v].emplace_back(h[u], i);
  }
  for (int root : roots) {
    map <int, int> f;
    dfs(root, f);
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d ", ans[i]);
  }
  puts("");
  return 0;
}

