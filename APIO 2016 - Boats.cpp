/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        APIO 2016 - Boats
        
        Category: Dynamic Programming
        
        Keys: Clustering, Optimization
        
*/

#include <bits/stdc++.h> 

using namespace std;

typedef pair <int, int> pii;

const int N = 505;
const int M = 1005;
const int MOD = 1e9 + 7;

vector <pii> v;
vector <int> z[M];

int x[M], y[M]; 
int n, m, a[N], b[N];

long long dp[N][M];
int sz[M], wide[M];

int counter = 1;
int comb[M][N], inverse[N];

int bigMod (int a, int e) {
  if (e == -1) e = MOD - 2;
  int r = 1; while (e) {
    if (e & 1) r = (r * 1ll * a) % MOD;
    a = (a * 1ll * a) % MOD;
    e >>= 1;
  }
  return r;
}

int nCr (int n, int r) {
  if (n < r) return 0;
  long long res = 1ll;
  for (int i = n, j = 1; j <= r; --i, ++j) {
    res *= 1ll * i, res %= MOD;
    res *= inverse[j], res %= MOD;
  }
  return res;
}

int main (int argc, char const *argv[]) {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", a + i, b + i);
    v.push_back({a[i], 0});
    v.push_back({b[i], 1});
  }
  sort(v.begin(), v.end());
  
  for (int i = 1; i < n + n; ++i) {
    int one = v[i - 1].second, two = v[i].second;
    int l = v[i - 1].first, r = v[i].first;

    if (!one and !two) {
      --r, ++counter;
      if (l <= r) x[++m] = l, y[m] = r;
    } else if (!one and two) {
      --counter;
      if (l <= r) x[++m] = l, y[m] = r;
    } else if (one and two) {
      ++l, --counter;
      if (l <= r) x[++m] = l, y[m] = r; 
    } else {
      ++l, --r;
      if (counter and l <= r) x[++m] = l, y[m] = r;
      ++counter;
    }
  }
  
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (a[j] <= x[i] and y[i] <= b[j]) {
        z[i].push_back(j);
        ++sz[i];
      }
    }
    wide[i] = y[i] - x[i] + 1;
  } 

  for (int i = 1; i < N; ++i) {
    inverse[i] = bigMod(i, -1);
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j <= sz[i]; ++j) {
      comb[i][j] = nCr(wide[i] + j, j + 1);
    }
  }

  for (int i = 0; i <= n + 1; ++i) {
    dp[i][m + 1] = 1;
  }
  for (int i = 0; i <= m + 1; ++i) {
    dp[n + 1][i] = 1;
  }
  for (int at = n; at; --at) {
    for (int range = m; range; --range) {
      dp[at][range] = dp[at][range + 1];
      int start = 0;
      while (start < sz[range] and z[range][start] < at) ++start;
      for (int i = start; i < sz[range]; ++i) {
        dp[at][range] += comb[range][i - start] * dp[z[range][i] + 1][range + 1];
        dp[at][range] %= MOD;
      }
    }
  }

  dp[1][1] += MOD - 1, dp[1][1] %= MOD;
  printf("%lld\n", dp[1][1]);
  return 0;
}

