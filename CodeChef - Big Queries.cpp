#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 10;
 
struct node {
	int two, five, l, r, lazy2, lazy5;
	node () {two = five = l = r = lazy2 = lazy5 = 0;}
};
 
node tree[3 * N];
int t, n, m, a[N], leg2[N], leg5[N];
 
int expo (int x, int p) {
	int tot = 0;
	while (x % p == 0) ++tot, x /= p;
	return tot;
}
 
int legendre (int x, int p) {
	int tot = 0, power = p;
	while (x >= power) tot += x/power, power *= p;
	return tot;
}
 
node merge (node a, node b) {
	node c;
	c.two = a.two + b.two;
	c.five = a.five + b.five;
	return c;
}
 
void build (int u, int b, int e) {
	if (b == e) {
		tree[u].two = expo(a[b], 2);
		tree[u].five = expo(a[b], 5);
		return;
	}
 
	int l = u << 1, r = l | 1, m = b + e >> 1;
	build(l, b, m), build(r, m + 1, e);
	tree[u] = merge(tree[l], tree[r]);	
}
 
void propagate (int u, int b, int e) {
	int l = tree[u].l, r = tree[u].r;
	
	if (l + r) {
		tree[u].two = leg2[r] - leg2[l - 1];
		tree[u].five = leg5[r] - leg5[l - 1];	
	}
 
	tree[u].two += tree[u].lazy2 * (e - b + 1);
	tree[u].five += tree[u].lazy5 * (e - b + 1);
 
	if (b != e) {
		int lchild = u << 1, rchild = lchild | 1;
 
		if (l + r) {
			tree[lchild].l = l, tree[lchild].r = l + r >> 1;
			tree[rchild].l = 1 + (l + r >> 1), tree[rchild].r = r;
			tree[lchild].lazy2 = tree[lchild].lazy5 = 0;
			tree[rchild].lazy2 = tree[rchild].lazy5 = 0;
		}
 
		tree[lchild].lazy2 += tree[u].lazy2;
		tree[rchild].lazy2 += tree[u].lazy2;
		tree[lchild].lazy5 += tree[u].lazy5;
		tree[rchild].lazy5 += tree[u].lazy5;
	}
 
	tree[u].l = tree[u].r = tree[u].lazy2 = tree[u].lazy5 = 0;
}
 
void update1 (int u, int b, int e, int p, int q, int x, int y) {
	if (tree[u].l + tree[u].r + tree[u].lazy2 + tree[u].lazy5) propagate(u, b, e);
	if (b > q or e < p) return;
	if (b >= p and e <= q) {
		tree[u].lazy2 += x, tree[u].lazy5 += y;
		propagate(u, b, e);
		return;
	}
 
	int l = u << 1, r = l | 1, m = b + e >> 1;
	update1(l, b, m, p, q, x, y);
	update1(r, m + 1, e, p, q, x, y);
	tree[u] = merge(tree[l], tree[r]);
}
 
void update2 (int u, int b, int e, int p, int q) {
	if (tree[u].l + tree[u].r + tree[u].lazy2 + tree[u].lazy5) propagate(u, b, e);
	if (b > q or e < p) return;
	if (b >= p and e <= q) {
		tree[u].lazy2 = tree[u].lazy5 = 0;
		tree[u].l = b - p + 1, tree[u].r = e - p + 1;
		propagate(u, b, e);
		return;
	}
 
	int l = u << 1, r = l | 1, m = b + e >> 1;
	update2(l, b, m, p, q), update2(r, m + 1, e, p, q);
	tree[u] = merge(tree[l], tree[r]);
}
 
pair <int, int> query (int u, int b, int e, int p, int q) {
	if (b > q or e < p) return {0, 0};
	if (tree[u].l + tree[u].r + tree[u].lazy2 + tree[u].lazy5) propagate(u, b, e);
	if (b >= p and e <= q) return {tree[u].two, tree[u].five};
 
	int l = u << 1, r = l | 1, m = b + e >> 1;
	pair <int, int> lchild = query(l, b, m, p, q);
	pair <int, int> rchild = query(r, m + 1, e, p, q);
	
	return {lchild.first + rchild.first, lchild.second + rchild.second};
}
 
int main (int argc, char const *argv[]) {
	for (int i = 1; i < N; ++i) 
		leg2[i] = legendre(i, 2), leg5[i] = legendre(i, 5);
 
	scanf("%d", &t); while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		build(1, 1, n);
 
		long long sum = 0;
 
		while (m--) {
			int cmd, l, r;
			scanf("%d %d %d", &cmd, &l, &r);
 
			if (cmd == 1) {
				int x; scanf("%d", &x);
				update1(1, 1, n, l, r, expo(x, 2), expo(x, 5));
			} else if (cmd == 2) {
				int x; scanf("%d", &x);
				update2(1, 1, n, l, r);
				update1(1, 1, n, l, r, expo(x, 2), expo(x, 5));
			} else {
				pair <int, int> res = query(1, 1, n, l, r);
				sum += (long long) min(res.first, res.second);
				// printf("%d\n", min(res.first, res.second));
			}
		}
 
		printf("%lld\n", sum);
		memset(tree, 0, sizeof tree);
	}
	return 0;
}
 
