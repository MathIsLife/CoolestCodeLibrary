/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 453B - Little Pony and Harmony Chest
        
        Category: Dynamic Programming
        
        Keys: Bitmasks, Bounding, Optimization
        
*/

#include <bits/stdc++.h> 

using namespace std;

struct data {
  int x, y, z;
  data () {}
  data (int _x, int _y, int _z) {
    x = _x, y = _y, z = _z;
  }
};

const int N = 105;
const int LIM = 60;
const int INF = 1e9 + 5;
const int MASK = (1 << 17) + 5;

vector <int> p;
data state[N][MASK];
int n, m, a[N];
int f[N][MASK];
int mask[N];

bool is_prime (int x) {
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  for (int i = 2; i <= LIM; ++i) {
    if (is_prime(i)) {
      p.push_back(i);
    }
  }
  m = p.size();
  for (int i = 1; i <= LIM; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i % p[j] == 0) {
        mask[i] |= 1 << j;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 1 << m; ++j) {
      f[i][j] = INF;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < 1 << m; ++j) {
      for (int k = 1; k <= LIM; ++k) {
        if (j & mask[k]) continue;
        int s = j | mask[k];
        int val = abs(a[i] - k) + f[i + 1][s];
        if (val < f[i][j]) {
          f[i][j] = val;
          state[i][j] = data(i + 1, s, k);
        }
      }
    }
  }
  int i = 0, j = 0;
  for (int k = 0; k < n; ++k) {
    printf("%d ", state[i][j].z);
    int next_i = state[i][j].x;
    int next_j = state[i][j].y;
    i = next_i, j = next_j;
  }
  puts("");
  return 0;
}

