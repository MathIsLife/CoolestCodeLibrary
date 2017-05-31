/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 246E - Blood Cousins Return
        
        Category: Graph Theory
        
        Keys: DSU on Tree
        
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> data;

#define x first
#define y second

const int N = 100010;

string s[N];
int n, m, h[N];
vector <int> g[N];
vector <int> roots;
vector <data> q[N];
int root, ans[N];

void go (int u, int deep = 1) {
  h[u] = deep;
  for (int v : g[u]) {
    go(v, deep + 1);
  }
}

void dfs (int u, map <int, set <string>> &f) {
  for (int v : g[u]) {
    map <int, set <string>> t;
    dfs(v, t);
    if (t.size() > f.size()) {
      f.swap(t);
    }
    for (auto it : t) {
      for (string z : it.y) {
        f[it.x].insert(z);
      }
    }
  }
  f[h[u]].insert(s[u]);
  for (data it : q[u]) {
    ans[it.y] = f[it.x].size(); 
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int par;
    cin >> s[i];
    scanf("%d", &par);
    if (par) {
      g[par].push_back(i);
    } else {
      roots.push_back(i);
    }
  }
  for (int root : roots) {
    go(root);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int u, k;
    scanf("%d %d", &u, &k);
    k += h[u];
    q[u].emplace_back(k, i);
  }
  for (int root : roots) {
    map <int, set <string>> f;
    dfs(root, f);
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}

