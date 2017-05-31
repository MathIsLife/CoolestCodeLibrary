/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 570D - Tree Requests
        
        Category: Graph Theory
        
        Keys: DSU on Tree
        
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> data;

#define x first
#define y second

const int N = 500010;

char s[N];
int n, m, h[N];
vector <int> g[N];
vector <data> q[N];
bitset <N> ans;

void go (int u, int deep = 1) {
  h[u] = deep;
  for (int v : g[u]) {
    go(v, deep + 1);
  }
}

void dfs (int u, map <int, int> &f) {
  for (int v : g[u]) {
    map <int, int> t;
    dfs(v, t);
    if (t.size() > f.size()) f.swap(t);
    for (auto it : t) {
      f[it.x] ^= it.y;
    }
  }
  f[h[u]] ^= 1 << (s[u] - 'a');
  for (data it : q[u]) {
    if (f.find(it.x) == f.end()) {
      ans[it.y] = 1;
    }
    if ((f[it.x] & (f[it.x] - 1)) == 0) {
      ans[it.y] = 1;
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
  go(1);
  scanf("%s", s + 1);
  for (int i = 1; i <= m; ++i) {
    int u, h;
    scanf("%d %d", &u, &h);
    q[u].emplace_back(h, i);
  }
  map <int, int> f;
  dfs(1, f);
  for (int i = 1; i <= m; ++i) {
    puts(ans[i] ? "Yes" : "No");
  }
  return 0;
}

