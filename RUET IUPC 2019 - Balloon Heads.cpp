#include <bits/stdc++.h>

using namespace std;

const int H = 5;
const int N = 200010;
const int M = 400010;

tuple <int, int, int> events[M];
vector <int> indices[H], y_coord[H];
tuple <int, int, int, int> queries[H][N];
int tests, cs, n, q, h, t, x[N], y[N], ans[N], where[N], f[M], sz[H];

void update (int p, int v) {
  while (p < M) f[p] += v, p += p & -p;
}

void range (int l, int r, int v) {
  update(l, v); update(r + 1, -v);
}

int get (int p) {
  int ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}

void solve (int rem, int l, int r) {
  if (l >= r) return;
  int mid = l + r >> 1, tot = 0;
  for (int i = l; i <= mid; ++i) {
    auto [l, r, y_l, y_r] = queries[rem][i];
    if (y_l == -1) continue;
    events[tot++] = make_tuple(l, -1, i);
    events[tot++] = make_tuple(r, +1, i);
  }
  for (int i = mid + 1; i <= r; ++i) {
    auto [pos, id, y_l, y_r] = queries[rem][i]; 
    if (y_l != -1) continue;
    events[tot++] = make_tuple(where[pos], 0, i);
  }
  sort(events, events + tot);
  for (int i = 0; i < tot; ++i) {
    auto [x_at, type, idx] = events[i];
    if (type == -1) {
      auto [l, r, y_l, y_r] = queries[rem][idx];
      range(y_l, y_r, +1);
    } else if (type == +1) {
      auto [l, r, y_l, y_r] = queries[rem][idx];
      range(y_l, y_r, -1); 
    } else {
      auto [pos, id, y_l, y_r] = queries[rem][idx]; 
      ans[id] += get(y[pos]);
    }
  }
  solve(rem, l, mid); solve(rem, mid + 1, r);
}

int main() {
  cin >> tests;
  while (tests--) {
    cin >> n >> q >> h >> t;
    int s_x, s_y, t_x, t_y, lim;
    cin >> s_x >> s_y >> t_x >> t_y >> lim;
    int at = 1, seed = s_x;
    auto advance = [] (int &seed) {
      seed = (seed * 1103515245LL + 1234) % 100000001;
    };
    while (at <= n) {
      x[at] = s_x + seed % (t_x - s_x + 1), advance(seed);
      y[at] = s_y + seed % (t_y - s_y + 1), advance(seed);
      if (y[at] % h) ++at;
    }
    for (int rem = 1; rem < h; ++rem) indices[rem].clear(), y_coord[rem].clear(), sz[rem] = 0;
    for (int i = 1; i <= n; ++i) indices[y[i] % h].emplace_back(i);
    for (int rem = 1; rem < h; ++rem) {
      if (indices[rem].empty()) continue;
      sort(indices[rem].begin(), indices[rem].end(), [] (int i, int j) {
        return x[i] < x[j];
      });
      for (int i = 0; i < indices[rem].size(); ++i) where[indices[rem][i]] = i;
    }
    int ptr = 0; 
    while (q--) {
      int cmd, val;
      scanf("%d %d", &cmd, &val);
      if (cmd == 1) {
        int x_l, y_l, x_r, y_r, seed = val;
        advance(seed), x_l = 1 + seed % lim;
        advance(seed), y_l = 1 + seed % lim;
        advance(seed), x_r = 100000000 - seed % lim;
        advance(seed), y_r = 100000000 - seed % lim;
        x_r += x_l, y_r += y_l;
        for (int rem = 1; rem < h; ++rem) {
          if (indices[rem].empty()) continue;
          int l = lower_bound(indices[rem].begin(), indices[rem].end(), x_l, [] (int i, int j) {
            return x[i] < j;
          }) - indices[rem].begin();
          int r = upper_bound(indices[rem].begin(), indices[rem].end(), x_r, [] (int i, int j) {
            return i < x[j];
          }) - indices[rem].begin() - 1;
          if (l > r) continue;
          int passed = val + rem + t, added = passed / (t + h) * h;
          passed %= t + h; if (passed > t) added += passed - t;
          y_l += rem - added, y_r += rem - added;
          queries[rem][sz[rem]++] = make_tuple(l, r, y_l, y_r);
          y_coord[rem].emplace_back(y_l), y_coord[rem].emplace_back(y_r);
          y_l -= rem - added, y_r -= rem - added;
        }
      } else {
        int rem = y[val] % h; ans[ptr] = 0;
        queries[rem][sz[rem]++] = make_tuple(val, ptr++, -1, -1);
        y_coord[rem].emplace_back(y[val]);
      }
    }
    for (int rem = 1; rem < h; ++rem) {
      if (y_coord[rem].empty()) continue;
      sort(y_coord[rem].begin(), y_coord[rem].end());
      y_coord[rem].erase(unique(y_coord[rem].begin(), y_coord[rem].end()), y_coord[rem].end());
      for (int i = 0; i < sz[rem]; ++i) {
        auto &[l, r, y_l, y_r] = queries[rem][i];
        if (y_l == -1) continue;
        y_l = lower_bound(y_coord[rem].begin(), y_coord[rem].end(), y_l) - y_coord[rem].begin() + 1;
        y_r = lower_bound(y_coord[rem].begin(), y_coord[rem].end(), y_r) - y_coord[rem].begin() + 1;
      }
    }
    for (int i = 1; i <= n; ++i) {
      int rem = y[i] % h;
      y[i] = lower_bound(y_coord[rem].begin(), y_coord[rem].end(), y[i]) - y_coord[rem].begin() + 1;
    }
    for (int rem = 1; rem < h; ++rem) {
      if (sz[rem]) solve(rem, 0, sz[rem] - 1);
    }
    printf("Case %d:\n", ++cs);
    for (int i = 0; i < ptr; ++i) printf("%d\n", ans[i]);
  }
  return 0;
}

