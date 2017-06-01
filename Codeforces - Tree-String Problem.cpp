/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 291E - Tree-String Problem
        
        Category: Graph Theory
        
        Keys: DFS, Hashing, Binary Jump
        
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int, int> edge;

const int P = 29;
const int LG = 20;
const int N = 1234567;
const int MOD = 1e9 + 7;
int INV;

string s;
ll hashVal[N];
vector <edge> g[N];
int n, m, k, ans; 
int h[N], par[N][LG];

ll bigMod (ll a, int e) {
  if (e == -1) e = MOD - 2;
  ll r = 1; while (e) {
    if (e & 1) r = (r * a) % MOD;
    a = (a * a) % MOD;
    e >>= 1;
  }
  return r;
}

void dfs (int u, int deep = 0) {
  h[u] = deep;
  for (edge e : g[u]) {
    int v = e.first, w = e.second;
    par[v][0] = u;
    hashVal[v] = (hashVal[u] + w * bigMod(P, deep)) % MOD;
    dfs(v, deep + 1);
  }
}

int ancestor (int u, int k) {
  if (h[u] < k) return -1;
  for (int i = LG - 1; i >= 0; --i) {
    if (k >= (1 << i)) {
      k -= (1 << i);
      u = par[u][i];
    }
  }
  return u;
}

void go (int u) {
  int v = ancestor(u, k);
  if (v != -1) {
    ll cur = (hashVal[u] - hashVal[v]) * bigMod(INV, h[v]);
    cur %= MOD, cur += MOD, cur %= MOD;
    if (cur == hashVal[0]) {
      ++ans;
    }
  }
  for (edge e : g[u]) {
    int v = e.first;
    go(v);
  }
}

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  INV = bigMod(P, -1);
  cin >> n;
  m = n;
  for (int i = 2; i <= n; ++i) {
    string x;
    int par, sz;
    cin >> par >> x;
    sz = x.size(); 
    for (int i = 0; i < sz - 1; ++i) {
      g[par].emplace_back(++m, x[i] - 'a' + 1);
      par = m;
    }
    g[par].emplace_back(i, x[sz - 1] - 'a' + 1);
  }
  cin >> s;
  k = s.size();
  hashVal[0] = 0;
  for (int i = 0; i < k; ++i) {
    hashVal[0] += (s[i] - 'a' + 1) * bigMod(P, i);
    hashVal[0] %= MOD;
  }
  memset(par, -1, sizeof par);
  dfs(1);
  for (int i = 1; i < LG; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (par[j][i - 1] != -1) {
        par[j][i] = par[par[j][i - 1]][i - 1];
      }
    }
  }
  go(1);
  printf("%d\n", ans);
  return 0;
}

