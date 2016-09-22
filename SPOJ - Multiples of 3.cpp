/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Multiples of 3 (MULTQ3)
    	
    	Category: Data Structures
    	
    	Keys: Segment Tree, Lazy Propagation
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct node {
	int zero, one, two, lazy;
	node () {}
	node (int a, int b, int c, int d) : zero(a), one(b), two(c), lazy(d) {}
};

int n, m;
node t[4 * N];

node merge (node a, node b) {
	return node(a.zero + b.zero, a.one + b.one, a.two + b.two, 0);
}

void propagate (int u, int b, int e) {
	if (t[u].lazy == 1) {
		int tmp = t[u].two;
		t[u].two = t[u].one, t[u].one = t[u].zero, t[u].zero = tmp;
	} else {
		int tmp = t[u].zero;
		t[u].zero = t[u].one, t[u].one = t[u].two, t[u].two = tmp;
	}

	if (b != e) {
		t[u << 1].lazy += t[u].lazy, t[u << 1].lazy %= 3;
		t[u << 1 | 1].lazy += t[u].lazy, t[u << 1 | 1].lazy %= 3;
	}

	t[u].lazy = 0;
}

void build (int u, int b, int e) {
	if (b == e) {
		t[u] = node(1, 0, 0, 0);
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	build(l, b, m), build(r, m + 1, e);
	t[u] = merge(t[l], t[r]);
}

void update (int u, int b, int e, int p, int q) {
	if (t[u].lazy) propagate(u, b, e);
	if (b > q or e < p) return;
	if (b >= p and e <= q) {
		++t[u].lazy, t[u].lazy %= 3;
		propagate(u, b, e);
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	update(l, b, m, p, q), update(r, m + 1, e, p, q);
	t[u] = merge(t[l], t[r]);
}

int query (int u, int b, int e, int p, int q) {
	if (b > q or e < p) return 0;
	if (t[u].lazy) propagate(u, b, e);
	if (b >= p and e <= q) return t[u].zero;

	int l = u << 1, r = l | 1, m = b + e >> 1;
	return query(l, b, m, p, q) + query(r, m + 1, e, p, q);
}

int main (int argc, char const *argv[]) {
	scanf("%d %d", &n, &m);
	build(1, 1, n);

	while (m--) {
		int cmd, l, r;
		scanf("%d %d %d", &cmd, &l, &r);
		++l, ++r;

		if (cmd) printf("%d\n", query(1, 1, n, l, r));
		else update(1, 1, n, l, r);
	}	
	return 0;
}

