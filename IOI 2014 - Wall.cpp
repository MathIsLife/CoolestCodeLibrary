/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2014 - Wall
        
        Category: Data Structures
        
        Keys: Segment Tree, Lazy Propagation
        
*/

#include <bits/stdc++.h>
#include "wall.h"

using namespace std;

typedef pair <int, int> node;

#define Min first
#define Max second

const int N = 2000010;
const int INF = 1e9 + 10;

node tree[4 * N];

void push (int u, int b, int e) {
  if (b == e) return;
  int l = u << 1, r = l | 1;
  tree[l].Min = min(tree[l].Min, tree[u].Min);
  tree[l].Min = max(tree[l].Min, tree[u].Max);
  tree[l].Max = min(tree[l].Max, tree[u].Min);
  tree[l].Max = max(tree[l].Max, tree[u].Max);
  tree[r].Min = min(tree[r].Min, tree[u].Min);
  tree[r].Min = max(tree[r].Min, tree[u].Max);
  tree[r].Max = min(tree[r].Max, tree[u].Min);
  tree[r].Max = max(tree[r].Max, tree[u].Max);
}

void update (int u, int b, int e, int from, int to, int v, int type) {
  push(u, b, e);
  if (b > to or e < from) return;
  if (b >= from and e <= to) {
    if (type) {
      tree[u].Min = min(tree[u].Min, v);
      tree[u].Max = min(tree[u].Max, v);
    } else {
      tree[u].Min = max(tree[u].Min, v);
      tree[u].Max = max(tree[u].Max, v);
    }
    return;
  }
  tree[u].Min = INF, tree[u].Max = -INF;
  int l = u << 1, r = l | 1, m = b + e >> 1;
  update(l, b, m, from, to, v, type);
  update(r, m + 1, e, from, to, v, type);
}

void traverse (int u, int b, int e, int res[]) {
  if (b == e) {
    res[b - 1] = tree[u].Min;
    return;
  }
  push(u, b, e);
  int l = u << 1, r = l | 1, m = b + e >> 1;
  traverse(l, b, m, res), traverse(r, m + 1, e, res);
}

void buildWall (int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
  for (int i = 0; i < k; ++i) {
    update(1, 1, n, left[i] + 1, right[i] + 1, height[i], op[i] - 1);
  }
  traverse(1, 1, n, finalHeight);
  return;
}

