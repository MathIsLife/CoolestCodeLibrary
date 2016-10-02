/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        Codeforces 343D - Water Tree

        Category: Data Structures

        Keys: DFS, Tree Flattening, Segment Tree

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

bitset <N> vis;
vector <int> g[N];
int n, q, pointer = 0;
int preOrder[N], p[N], l[N], r[N];
int tree[3 * N], lazy[3 * N]; 

void dfs (int u) {
	vis[u] = 1;
	preOrder[++pointer] = u;
	l[u] = pointer;
	for (int v : g[u]) if (!vis[v]) p[v] = u, dfs(v);
	r[u] = pointer; 
}

void propagate (int u, int b, int e) {
	tree[u] = e - b + 1;
	if (b != e) lazy[u << 1] = lazy[u << 1 | 1] = 1;
	lazy[u] = 0;
}

void build (int u, int b, int e) {
	if (b == e) {
		tree[u] = 2;
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	build(l, b, m), build(r, m + 1, e);
	tree[u] = tree[l] + tree[r];
}

void rangeFill (int u, int b, int e, int p, int q) {
	if (lazy[u]) propagate(u, b, e);
	if (b > q or e < p) return;
	if (b >= p and e <= q) {
		lazy[u] = 1, propagate(u, b, e);
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	rangeFill(l, b, m, p, q), rangeFill(r, m + 1, e, p, q);
	tree[u] = tree[l] + tree[r];
}

void pointColor (int u, int b, int e, int p) {
	if (lazy[u]) propagate(u, b, e);
	if (b > p or e < p) return;
	if (b == e) {
		tree[u] = 2;
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	pointColor(l, b, m, p), pointColor(r, m + 1, e, p);
	tree[u] = tree[l] + tree[r];
}

int query (int u, int b, int e, int p, int q) {
	if (b > q or e < p) return 0;
	if (lazy[u]) propagate(u, b, e);
	if (b >= p and e <= q) return tree[u];

	int l = u << 1, r = l | 1, m = b + e >> 1;
	return query(l, b, m, p, q) + query(r, m + 1, e, p, q);
}

int main (int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(1), build(1, 1, n);

	scanf("%d", &q); while (q--) {
		int cmd, u;
		scanf("%d %d", &cmd, &u);

		if (cmd == 1) {
			int subtreeSum = query(1, 1, n, l[u], r[u]);
			if (subtreeSum > r[u] - l[u] + 1) pointColor(1, 1, n, l[p[u]]);
			rangeFill(1, 1, n, l[u], r[u]); 
		} else if (cmd == 2) {
			pointColor(1, 1, n, l[u]);
		} else {
			int subtreeSum = query(1, 1, n, l[u], r[u]);
			if (subtreeSum > r[u] - l[u] + 1) puts("0");
			else puts("1");
		}
	}
	return 0;
}

