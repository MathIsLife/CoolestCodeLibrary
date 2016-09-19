/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Can you answer these queries I (GSS1)
    	
    	Category: Data Structures
    	
    	Keys: Segment Tree
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;
const int INF = 1e9 + 10;

struct node {
    int pre, suf, sum, best;
    node () {}
    node (int a, int b, int c, int d) : pre(a), suf(b), sum(c), best(d) {}
};

node t[4 * N];
int n, m, a[N];

node merge (node a, node b) {
    node c;
    c.sum = a.sum + b.sum;
    c.pre = max(a.pre, a.sum + b.pre);
    c.suf = max(b.suf, b.sum + a.suf);
    c.best = max(max(a.best, b.best), a.suf + b.pre);
    return c;
}

void build (int u, int b, int e) {
    if (b == e) {
	t[u] = node(a[b], a[b], a[b], a[b]); 
	return;
    }

    int l = u << 1, r = l + 1, m = b + e >> 1;
    build(l, b, m), build(r, m + 1, e);
    t[u] = merge(t[l], t[r]);
}

node query (int u, int b, int e, int p, int q) {
    if (b > q or e < p) return node(-INF, -INF, 0, -INF);
    if (b >= p and e <= q) return t[u];

    int l = u << 1, r = l + 1, m = b + e >> 1;
    node qleft = query(l, b, m, p, q), qright = query(r, m + 1, e, p, q);
    return merge(qleft, qright);
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    build(1, 1, n);

    scanf("%d", &m); while (m--) {
	int x, y;
	scanf("%d %d", &x, &y);
	printf("%d\n", query(1, 1, n, x, y).best);
    }

    return 0;
}

