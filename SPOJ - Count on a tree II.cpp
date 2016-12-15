/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Count on a tree II (COT2)
    	
    	Category: Data Structures
    	
    	Keys: Tree Flattening, Mo's Algorithm 
    	
*/

#include <bits/stdc++.h>

using namespace std;

int SQRT;
const int LG = 18;
const int N = 100010;

struct query {
    int id, l, r, lca;
    query () {}
    query (int a, int b, int c, int d) {
        id = a, l = b, r = c, lca = d;
    }
    bool operator < (const query &q) const {
        if (l/SQRT == q.l/SQRT) return r < q.r;
        return l/SQRT < q.l/SQRT;
    }
};

query q[N];
vector <int> g[N];
map <int, int> to;
int n, m, tot, w[N], ans;
int flat[N + N], p[N][LG];
int l[N], r[N], depth[N];
int res[N], cnt[N], mark[N];

void dfs (int u, int par, int deep) {
    p[u][0] = par, depth[u] = deep;
    flat[++tot] = u, l[u] = tot;
    for (int i = 0; i < (int) g[u].size(); ++i) {
        int v = g[u][i];
        if (v == par) continue;
        dfs(v, u, deep + 1);
    }
    flat[++tot] = u, r[u] = tot;
}

void init (void) {
    for (int j = 1; 1 << j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (p[i][j - 1] != -1) {
                p[i][j] = p[p[i][j - 1]][j - 1];
            }
        }
    }
}

int lca (int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LG - 1; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = p[u][j];
        }
    }
    if (u == v) return u;
    for (int j = LG - 1; j >= 0; --j) {
        if (p[u][j] != -1 and p[u][j] != p[v][j]) {
            u = p[u][j], v = p[v][j];
        }
    }
    return p[u][0];
}

void update (int x) {
    int u = flat[x];
    if (mark[u]) {
        --cnt[w[u]];
        if (cnt[w[u]] == 0) --ans;
    } else {
        if (cnt[w[u]] == 0) ++ans;
        ++cnt[w[u]];
    }
    mark[u] ^= 1;
}

int main (int argc, char const *argv[]) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", w + i);
        if (!to.count(w[i])) to[w[i]] = ++tot;
        w[i] = to[w[i]];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    memset(p, -1, sizeof p);
    tot = 0, dfs(1, 1, 0), init();
    
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        int z = lca(u, v);
        if (depth[u] > depth[v]) swap(u, v);
        if (z == u) q[i] = query(i, l[u], l[v], 0);
        else q[i] = query(i, r[u], l[v], z);
    }
    
    SQRT = sqrt(n);
    sort(q + 1, q + m + 1);
    
    int x = 1, y = 0;
    for (int i = 1; i <= m; ++i) {
        while (x > q[i].l) update(--x);
        while (y < q[i].r) update(++y);
        while (x < q[i].l) update(x++);
        while (y > q[i].r) update(y--);
        
        if (q[i].lca) update(l[q[i].lca]);
        res[q[i].id] = ans;
        if (q[i].lca) update(l[q[i].lca]);
    }
    
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", res[i]);
    }
    return 0;
}

