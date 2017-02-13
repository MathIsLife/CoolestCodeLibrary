/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
      SPOJ - Query on a tree (QTREE)
    	
    	Category: Data Structures
    	
    	Keys: Heavy-Light Decomposition, Segment Tree
    	
*/

#include <bits/stdc++.h> 

using namespace std;

const int LG = 15;
const int N = 1e4 + 10;

char cmd[10];
int t, cs = 0, n;
vector <int> g[N], id[N], cost[N];
int tr[N + N], p[N][LG], depth[N];
int size[N], cur, pointer, pos[N];
int head[N], below[N], chain[N];

void dfs (int u, int par, int deep) {
	depth[u] = deep;
	p[u][0] = par;
	size[u] = 1;
	for (int i = 0; i < (int) g[u].size(); ++i) {
		int v = g[u][i], idx = id[u][i];
		if (v == par) continue;
		below[idx] = v;
		dfs(v, u, deep + 1);
		size[u] += size[v];
	}
}

void hld (int u, int curCost, int par) {
	if (head[cur] == -1) {
		head[cur] = u; 
	}
	chain[u] = cur;
	pos[u] = pointer;
	tr[n + pointer] = curCost;
	++pointer;
	int special = -1, nCost;
	for (int i = 0; i < (int) g[u].size(); ++i) {
		int v = g[u][i];
		if (v == par) continue;
		if (special == -1 or size[special] < size[v]) {
			special = v;
			nCost = cost[u][i];
		}
	}
	if (special != -1) {
		hld(special, nCost, u);
	}
	for (int i = 0; i < (int) g[u].size(); ++i) {
		int v = g[u][i];
		if (v == par or v == special) continue;
		++cur;
		hld(v, cost[u][i], u);
	}
}

void init (void) {
	for (int i = n - 1; i; --i) {
		tr[i] = max(tr[i << 1], tr[i << 1 | 1]);
	}
}

void tree_u (int p, int v) {
	for (tr[p += n] = v; p > 1; p >>= 1) {
		tr[p >> 1] = max(tr[p], tr[p ^ 1]);
	}
}

int tree_q (int l, int r) {
	int res = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = max(res, tr[l++]);
		if (r & 1) res = max(res, tr[--r]);
	}
	return res;
}

int lca (int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (int i = LG - 1; i >= 0; --i) {
		if (depth[u] - (1 << i) >= depth[v]) {
			u = p[u][i];
		}
	}
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i) {
		if (p[u][i] != -1 and p[u][i] != p[v][i]) {
			u = p[u][i], v = p[v][i];
		}
	}
	return p[u][0];
}

int subq (int u, int v) {
	if (u == v) return 0;
	int uchain, vchain = chain[v], res = -1;
	while (true) {
		uchain = chain[u];
		if (uchain == vchain) {
			if (u == v) break;
			res = max(res, tree_q(1 + pos[v], 1 + pos[u]));
			break;
		}
		res = max(res, tree_q(pos[head[uchain]], 1 + pos[u]));
		u = p[head[uchain]][0];
	}
	return res;
}

int query (int u, int v) {
	int w = lca(u, v);
	return max(subq(u, w), subq(v, w));
}

void update (int p, int v) {
	int u = below[p];
	tree_u(pos[u], v);
}

int main (int argc, char const *argv[]) {
	scanf("%d", &t); while (t--) {
		scanf("%d", &n);
		for (int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].push_back(v);
			g[v].push_back(u);
			cost[u].push_back(w);
			cost[v].push_back(w);
			id[u].push_back(i);
			id[v].push_back(i);
		}
		memset(p, -1, sizeof p);
		memset(head, -1, sizeof head);
		dfs(1, 1, 0);
		pointer = cur = 0;
		hld(1, 0, 1);
		for (int i = 1; 1 << i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j][i - 1] != -1) {
					p[j][i] = p[p[j][i - 1]][i - 1];
				}
			}
		}
		init();
		while (scanf("%s", cmd) and cmd[0] != 'D') {
			int a, b;
			scanf("%d %d", &a, &b);
			if (cmd[0] == 'Q') {
				printf("%d\n", query(a, b));
			} else {
				update(a, b);
			}
		}
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
			cost[i].clear();
			id[i].clear();
		}
		memset(tr, 0, sizeof tr);
	}
    return 0;
}

