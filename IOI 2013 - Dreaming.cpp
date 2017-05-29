/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2013 - Dreaming
        
        Category: Graph Theory
        
        Keys: DFS, Observation
        
*/

#include <bits/stdc++.h>
#include "dreaming.h"

using namespace std;

typedef pair <int, int> edge;

#define to first
#define cost second

const int MAX = 123456;

bitset <MAX> vis;
vector <edge> g[MAX];
int maxDist, at;
edge par[MAX];

void dfs (int u, int from, int far, int flag) {
  if (flag) {
    vis[u] = 1;
  }
  if (far > maxDist) {
    maxDist = far;
    at = u;
  }
  for (edge e : g[u]) {
    if (e.to == from) continue;
    if (flag) {
      par[e.to] = edge(u, e.cost);
    }
    dfs(e.to, u, far + e.cost, flag);
	}
}

int travelTime (int N, int M, int L, int A[], int B[], int T[]) {
	for (int i = 0; i < M; ++i) {
		g[A[i]].emplace_back(B[i], T[i]);
		g[B[i]].emplace_back(A[i], T[i]);
	}

	vector <int> R;
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		if (vis[i]) continue;
		maxDist = -1;
		dfs(i, i, 0, 0);
		int one = at;
		maxDist = -1;
		dfs(one, one, 0, 1);
		int two = at;
		
		ret = max(ret, maxDist);
		
		int half = maxDist >> 1;
		int radius = 0;
		for (int v = two; v != one; v = par[v].to) {
			if (radius + par[v].cost > half) {
				radius = min(radius + par[v].cost, maxDist - radius);
				break;
			}
			radius += par[v].cost;
		}
		R.push_back(radius);
	}

	sort(R.rbegin(), R.rend());
	if (R.size() > 1) ret = max(ret, R[0] + R[1] + L);
	if (R.size() > 2) ret = max(ret, R[1] + R[2] + L + L);
	return ret;
}

